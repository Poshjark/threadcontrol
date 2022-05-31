#pragma once
#include <iostream>
#include <list>
#include "colors.h"



template<class T>
void print_std_container(T& cont) {
    for (auto& v : cont) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}



/*
* Storage class to store Objects marked with any defined Color.
*/
class Storage {

    size_t unsorted = 0;
    std::list<Object> container;
public:
    // Sorts underlying container while there is unsorted elements using binary
    // search algorithm to find place for unsorted elements
    void sort();

    // Pushes value to underlying container
    void push(Color value);
    
    // Pushes random value to underlying container
    void push_random();

    // Just std::cout for every element
    void print();

    /*Checks if data in underlying container is sorted. Traversal iteration and compairing two elements.
    * @returns true if underlying container is sorted. False if underlying container is not sorted
    */
    bool test_data();
};
