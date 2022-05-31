#include "threadswrapper.h"

std::string getTimeStr(){
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return s;
}

void ThreadsWrapper::join_all() {
    while(threads.size()){
        threads.front().join();
        threads.pop();
    }
}

void ThreadsWrapper::run(std::string name){
    auto it = controls_map.find(name);
    if(it != controls_map.end()){
        (*it).second.permission_to_work = true;
        (*it).second.cv.notify_one();
    }
    else{
        std::cout << "There is no thread <<<" << name << ">>>\n";
    }
}

void ThreadsWrapper::stop(std::string name){
    auto it = controls_map.find(name); 
    if(it != controls_map.end()){
        (*it).second.permission_to_work = false;
    }
}

void ThreadsWrapper::abort_all(){
    for(auto& control : controls_map){
        control.second.permission_to_work = false;
    }
    for(auto& control : controls_map){
        control.second.permission_to_work = true;
    }
    abortion = true;

    for(auto& control : controls_map){
        control.second.cv.notify_one();
    }
    join_all();
}

ThreadsWrapper::~ThreadsWrapper(){
        if(!abortion){
            abort_all();
        }
    }

std::string ThreadsWrapper::get_logs(){
    return logger.ss.str();
}