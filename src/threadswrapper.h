#pragma once

#include <queue>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <sstream>
#include <ctime>
#include <functional>
#include <thread>



// Gets date and time from system clock and formats it for example to  "2022-05-30 07:19:00"
std::string getTimeStr();

/**
* Wrapper class for two threads - generator and sorter.
* 
* It has some interface for managing these threads.
* 
*/
class ThreadsWrapper{

    /*
    * Struct for storing utility variables like thread_mutex, cv and permission to work.
    * Private within context and has no direct interface with user.
    * Has no copy constructor because of std::mutex and std::condition_variable policy
    */
    struct Controls {
        std::mutex m;                   // Formal mutex for condition_variable
        std::condition_variable cv;
        bool permission_to_work = false;
    };
    bool abortion = false;
    std::queue<std::thread> threads;
    std::unordered_map<std::string, Controls> controls_map;
    std::mutex storage_mutex;

    void join_all();

    class Logger {
    public:
        std::stringstream ss;
        std::mutex m;
        std::stringstream& log() {
            ss << getTimeStr();
            return ss;
        }
    };

    Logger logger;// Initializing global logger object to have common logger for all threads


public:
    
    /*
    *  Function creating threads with their own name to control them execution
    *  Function _func passed here is being wrapped to thread execution control logic.
    *
    *  @param name - Name of thread, which will be used to run and stop its execution
    *  @param _func - callable object(function reference, lambda, object with implemented operator() or member function)
    *  @param args... - args to forward to _func. If non-static member function needs object to call from.
    */
      template<class Callable, class... Args>
  void create_thread(std::string name, Callable&& _func, Args&&... args){
    threads.push(
      std::thread([&,name](typename std::decay<Callable>::type &&f, typename std::decay<Args>::type &&... args) {
        std::mutex& m = controls_map[name].m;
        std::condition_variable& cv = controls_map[name].cv;
        bool& permission_to_work = controls_map[name].permission_to_work;
        {
            std::unique_lock<std::mutex> lock(m);
            {
                std::unique_lock<std::mutex> locker(logger.m);
                logger.log() << "\tThread <<<" << name << ">>> waiting for first start...\n";
            }
            cv.wait(lock, [&]() {return permission_to_work; });
        }
        {
            std::unique_lock<std::mutex> locker(logger.m);
            logger.log() << "\tThread <<<" << name << ">>> first started working...\n";
        }
        while (true) {
            if (permission_to_work) {
                if (abortion) {
                    {
                        std::unique_lock<std::mutex> locker(logger.m);
                        logger.log() << "\tThread <<<" << name << ">>> aborting with user command!\n";
                    }
                    break;
                }
                {
                    std::lock_guard<std::mutex> lock(storage_mutex);
                    auto foo = std::bind(f,args...);
                    foo(args...);
                }

            }
            else {
                {
                    {
                        std::unique_lock<std::mutex> locker(logger.m);
                        logger.log() << "\tThread <<<" << name << ">>> waiting for permission to start\n";
                    }
                    std::unique_lock<std::mutex> lock(m);
                    cv.wait(lock, [&]() {return permission_to_work; });
                    if (abortion) {
                        {
                            std::unique_lock<std::mutex> locker(logger.m);
                            logger.log() << "\tThread <<<" << name << ">>> aborting with user command!\n";
                        }
                        break;
                    }
                    {
                        std::unique_lock<std::mutex> locker(logger.m);
                        logger.log() << "\tThread <<<" << name << ">>> got permission after stopping, continue jobs...\n";
                    }
                }
            }

        }
        {
            std::unique_lock<std::mutex> locker(logger.m);
            logger.log() << "\tThread <<<" << name << ">>> finished\n";
        }
          
          

      }, std::forward<Callable>(_func), std::forward<Args>(args)...)
    );
  }

    // Runs or continues execution of thread with name "name"
    void run(std::string name);

    // Stops execution of thread with name "name"
    void stop(std::string name);
    
    // Aborts all thread's execution and joining them to master thread.
    void abort_all();
    
    // Returns string representation of written logs
    std::string get_logs();

    ~ThreadsWrapper();

    
};
