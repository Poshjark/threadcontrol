#pragma once
#include <iostream>
#include <unordered_map>


// Enum class for storing just color with its short one-character name
enum Color : char{
    red = 'r',
    green = 'g',
    blue = 'b'
};

namespace color_controls{
    // Hashmap for storing associated short one-character names of Colors 
    // with their full names and enum value
    extern std::unordered_map<Color,int> order;


    // Hashmap for associating Colors with their full names
    extern std::unordered_map<Color,std::string> color_names;



}


template<Color>
bool operator<(Color&& color1, Color&& color2 ){
    return color_controls::order[color1] < color_controls::order[color2];
};

// Object marked with some color
struct Object{
    Color mark;
    Object(Color _mark) : mark(_mark){};
    
    bool operator<(const Object& other){
        return color_controls::order[this->mark] < color_controls::order[other.mark];
    }
    
    bool operator==(const Object& other){
        return this->mark == other.mark;
    }
    
    bool operator>(const Object& other){
        return color_controls::order[this->mark] > color_controls::order[other.mark];
    }
};


std::ostream& operator<<(std::ostream& os, const Color& color);



std::ostream& operator<<(std::ostream& os, const Object& obj);



// Function for Initializing order of elements to sort in
// Must! be called once in the beginning
void init_order();

