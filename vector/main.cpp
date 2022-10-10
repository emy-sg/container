#include "vector.hpp"
#include <vector>

int main() {
    //ft::vector<int> vec; // default constructor
    //ft::vector<int> vec(5, 6);

    //  ---------------
    ft::vector<int> v(9, 5);
    ft::vector<int>::iterator iter;
    
    //ft::vector<int>::iterator iter; 
    for(iter = v.begin(); iter != v.end(); iter++)
        std::cout << *iter << " -- ";
    std::cout << "\n";

    std::cout << "size: " << v.size() << "\n";
    std::cout << "capacity: " << v.capacity() << "\n";
    //std::cout << "max size: " << v.max_size() << "\n";

    //std::cout << v[1] << "\n"; 

    //      ----------------------------------------

    std::cout << "-------------- Iterators -----------------------\n";


}