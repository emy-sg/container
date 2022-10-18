#include "Vector.hpp"
#include <iterator>
#include <vector>

int main() {

    //ft::vector<int> vec; // default constructor
    //ft::vector<int> vec(5, 6);

   //   --------------------------  std::vector<int>::iterator().base();  ----------------------------------
    
    // ft::Vector<int> v(3, 4);
    // ft::Vector<int>::iterator it, it1;

    // ft::Vector<int> v(3, 4);
    // ft::Vector<int>::iterator it, it1;

    // --------- at() && [] ----------------

    // std::cout << v[0] << "\n";
    // std::cout << v[2] << "\n";
    // std::cout << "size: " << v.size() << "\n";
    // v[3] = 9;
    // v[4] = 4;
    // v[5] = 6;
    // std::cout << "size: " << v.size() << "\n";
    // std::cout << v[9] << "\n";

    // it = v.begin();
    // it1 = v.begin() + 1;

    // std::cout << (it <= it1) << "\n";
    // /*----------------------------------*/
    // /*------------ ft::Vector ---------*/
    // ft::Vector<int> my_v(3, 4);
    // ft::Vector<int>::iterator my_it, my_it1, tmp;
    // my_it = my_v.begin();
    // my_it1 = my_v.begin() + 1;

    // std::cout << (my_it <= my_it1) << "\n";
    
//--------------------------------------------------------

 
//  -----------------------------------------

    /*ft::Vector<int> v(2, 5);
    std::vector<int> vec(2, 5);

    ft::Vector<int>::iterator iter;
    iter = v.begin();
    std::cout << "v size " << v.size() << " ==> " << v[0] << " | " << v[1] << " | " << v[2] << "\n";
    std::cout << *(iter) << " | " << iter[0] << " | " << iter[1] << "\n";
    std::cout << *(++iter) << " | " << iter[0] << " | " << iter[1] << "\n";

    std::vector<int>::iterator ite;
    ite = vec.begin();
    std::cout << "vec size " << vec.size()  << " ==> " << vec[0] << " | " << vec[1] << " | " << vec[2] << "\n";
    std::cout << *(ite) << " | " << ite[0] << " | " << ite[1] << "\n";
    std::cout << *(++ite) << " | " << ite[0] << " | " << ite[1] << "\n";*/
    //////////////////////////////////

    // std::cout << v.at(2) << "\n";
    // std::cout << v[5] << "\n";

    // std::cout << v.at(2) << "\n";
    // std::cout << v[5] << "\n";



    ////////////////////////////////////
    
    //ft::Vector<int>::iterator iter;
    
    //ft::vector<int>::iterator iter; 
    // for(iter = v.begin(); iter != v.end(); iter++)
    //     std::cout << *iter << " -- ";
    // std::cout << "\n";

    // std::cout << "size: " << v.size() << "\n";
    // std::cout << "capacity: " << v.capacity() << "\n";
    //std::cout << "max size: " << v.max_size() << "\n";

    //std::cout << v[1] << "\n"; 

    //      ----------------------------------------

    std::cout << "-------------- const Iterators -----------------------\n";

    ft::Vector<int> v(3, 4);
    ft::Vector<int>::iterator it, it1;
    
    std::cout << v[0] << "\n";
    std::cout << v[2] << "\n";
    std::cout << "size: " << v.size() << "\n";
    v[3] = 9;
    v[4] = 4;
    v[5] = 6;
    std::cout << "size: " << v.size() << "\n";
    std::cout << v[9] << "\n";
    ft::Vector<int> v2;

    v2 = v;
    ft::Vector<int>::const_iterator ci;

    ci = v2.begin(); // call const_iterator begin();

    
}