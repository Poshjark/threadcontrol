#include <iostream>
#include <unordered_map>
#include <list>
#include "threadswrapper.h"
#include "storage.h"

int main(){
    std::srand(std::time(nullptr));
    init_order();
    Storage s;
    ThreadsWrapper tw;
    std::string message_from_user = "";
    std::string sorter_name = "sorter";
    std::string generator_name = "generator";
    tw.create_thread(generator_name, &Storage::push_random, std::ref(s));
    tw.create_thread(sorter_name,  &Storage::sort, std::ref(s));
    
    std::cout << "Now you have two threads with names '" << sorter_name <<"' and '" << generator_name <<"'\n";
    while(true){
        std::cout << "Enter command(run <name> / stop <name> / abort): ";
        std::getline(std::cin, message_from_user);
        if(message_from_user.substr(0,message_from_user.find(' ')) == "run"){
            std::string name = message_from_user.substr(message_from_user.find(' ') + 1,message_from_user.size() - 1);
            tw.run(name);
        }
        else if(message_from_user.substr(0,message_from_user.find(' ')) == "stop"){
            std::string name = message_from_user.substr(message_from_user.find(' ') + 1,message_from_user.size() - 1);
            tw.stop(name);
        }
        else if(message_from_user == "abort"){
            tw.abort_all();
            break;
        }
    }
    std::cout << "Print logs? y/n\n";
    std::getline(std::cin, message_from_user);
    if(message_from_user == "y" || message_from_user == "Y"){
        std::cout << "LOGS:\n" << tw.get_logs();
        std::cout << "Data is ";
        s.print();
        std::cout << "Data is consistent - " << std::boolalpha << s.test_data() << std::endl;
    }
    
    system("pause");
    return 0;
}













