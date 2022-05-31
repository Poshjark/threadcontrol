# threadcontrol
Little training project to handle with multithreading better.

There are two main classes:

1) ThreadsWrapper - gives you opportunity to manage few threads working with common data wrapping their functions and providing easy interface.
2) Storage - stores Objects marked with any color, has sort function that uses binary search algorithm for finding place for unsorted elements. 
Underlying container is std::list because it provides fast inserting without reallocating.
Requires overloaded compare operators for compairing.
