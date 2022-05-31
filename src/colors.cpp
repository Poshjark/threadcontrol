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
    std::string command;
    std::cout << "Enter order of colors for example {rgb} or {grb} in ascending order without brackets: ";
    while(true){
        std::getline(std::cin,command);
        if(command.size() == 3){
            if(command.find(Color::red) != -1 && command.find(Color::green) != -1 && command.find(Color::blue) != -1){
                break;
            }
        }
        std::cout << "Please specify correct order of colors - three characters(rgb) without whitespaces: ";
        continue;
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
