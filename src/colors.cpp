#include "colors.h"
#include <string>


std::unordered_map<Color,int> color_controls::order{
        {Color::red, 0},
        {Color::green, 1},
        {Color::blue, 2}
    };

std::unordered_map<Color,std::string> color_controls::color_names{
        {Color::red, "red"},
        {Color::green, "green"},
        {Color::blue, "blue"}
    };

void init_order(){
    const std::string hello =   "Hello! I am program with few functions! I can:"
                                " running, stopping and continuing execution of two threads\n"
                                "These threads are:"
                                "\n1) generator  - can generate random consequences" 
                                "of objects marked with one of three colors: red, green or blue\n"
                                "2) sorter - sorts objects created by generator\n"
                                "At first you should specify order of colors typing characters 'r' 'g' and 'b'"
                                " in ascending(0123...) order. For example 'rgb' or 'gbr'\n"
                                "Every character must appear strictly once"
                                "This order will be used to sort generated objects\n";
    std::cout << hello << std::endl;
    std::string command;
    std::cout << "Now please specify color order: ";
    while(true){
        std::getline(std::cin,command);
        if(command.size() == 3){
            if(command.find(Color::red) != -1 && command.find(Color::green) != -1 && command.find(Color::blue) != -1){
                break;
            }
        }
        std::cout << "Please specify correct order of colors - three different characters(rgb) without whitespaces: ";
    }
    for(int i = 0; i < 3; i++){
        color_controls::order[static_cast<Color>(command[i])] = i;
    }
}

std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << color_controls::color_names[color] <<"(" << color_controls::order[color] << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Object& obj){
    os << obj.mark;
    return os;
}
