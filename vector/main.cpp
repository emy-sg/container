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

    // std::cout << "-------------- const Iterators -----------------------\n";

    // ft::Vector<int> v(3, 4);
    // ft::Vector<int>::iterator it, it1;
    
    // std::cout << v[0] << "\n";
    // std::cout << v[2] << "\n";
    // std::cout << "size: " << v.size() << "\n";
    // v[3] = 9;
    // v[4] = 4;
    // v[5] = 6;
    // std::cout << "size: " << v.size() << "\n";
    // std::cout << v[9] << "\n";
    // ft::Vector<int> v2;

    // v2 = v;
    // ft::Vector<int>::const_iterator ci;

    // ci = v2.begin(); // call const_iterator begin();

    ////////////////////// reserve  ---------------------

    // ft::Vector<int> v;

    // v.reserve(5);

    // std::cout << v.size() << " | " << v.capacity() << "\n";


    ////////////////////// push_back -------------------

    //  ft::Vector<int> v;
    // //std::vector<int> v;

    // v.push_back(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // v.push_back(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // v.push_back(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // v.push_back(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //////////////////////// resize ----------------------

    // ft::Vector<int> v(3, 4);

    // v.resize(2);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //     v.resize(4);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //     v.resize(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //     v.resize(6);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    ///////////////////////// erase  --------------------------

    // ft::Vector<int> v;
    // std::vector<int> v;

    // v.push_back(5);
    // v.push_back(10);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // std::cout << *(v.erase(v.begin())) << "\n";
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // v.clear();
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //////////////////////// reserve ----------------------------

    // std::cout << "Reserve\n";
    // ft::Vector<int> v;
    // std::vector<int> v1;

    // v.push_back(1);
    // v.push_back(2);
    // v.push_back(3);
    // v.push_back(4);

    // v1.push_back(1);
    // v1.push_back(2);
    // v1.push_back(3);
    // v1.push_back(4);

    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";
    //  std::cout << "--------------------------\n";
    // v.reserve(5);
    // v1.reserve(5);
    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";
    // std::cout << "--------------------------\n";
    // v.clear();
    // v1.clear();
    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";

    /////////////////////// resize --------------------------

    // std::cout << "\nResize\n";
    // ft::Vector<int> f;
    // std::vector<int> f1;

    // f.push_back(1);
    // f.push_back(2);
    // f.push_back(3);
    // f.push_back(4);

    // f1.push_back(1);
    // f1.push_back(2);
    // f1.push_back(3);
    // f1.push_back(4);
    
    // std::cout << f.size() << " | " <<  f.capacity() << "\n";
    // std::cout << f1.size() << " | " <<  f1.capacity() << "\n";
    //  std::cout << "--------------------------\n";
    // f.resize(4, 1);
    // f1.resize(4, 1);
    // std::cout << f.size() << " | " <<  f.capacity() << "\n";
    // std::cout << f1.size() << " | " <<  f1.capacity() << "\n";
    // std::cout << "--------------------------\n";
    // f.clear();
    // f1.clear();
    // std::cout << f.size() << " | " <<  f.capacity() << "\n";
    // std::cout << f1.size() << " | " <<  f1.capacity() << "\n";

    /////////////////// max_size -----------------------------

    // std::vector<int> v;
    // std::vector<char> vc;

    // ft::Vector<int> v1;
    // ft::Vector<char> v1c;

    // std::cout << v.max_size() << " | " <<  vc.max_size() << "\n";
    // std::cout << v1.max_size() << " | " <<  v1c.max_size() << "\n";

    // std::cout << sizeof(int) << "\n";

    /////////////////// front && back -----------------------------

    // ft::Vector<int> f;
    // std::vector<int> f1;

    // f.push_back(1);
    // f.push_back(2);
    // f.push_back(3);
    // f.push_back(4);

    // f1.push_back(1);
    // f1.push_back(2);
    // f1.push_back(3);
    // f1.push_back(4);
    
    // std::cout << f.front() << " | " <<  f.back() << "\n";
    // std::cout << f1.front() << " | " <<  f1.back() << "\n";

    /////////////////// erase  --------------------------------

    // std::cout << "erase\n";
    // ft::Vector<int> v;
    // std::vector<int> v1;

    // v1.erase(v1.end());
    // v.push_back(1);
    // v.push_back(2);
    // v.push_back(3);
    // v.push_back(4);

    // v1.push_back(1);
    // v1.push_back(2);
    // v1.push_back(3);
    // v1.push_back(4);

    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";
    //  std::cout << "--------------------------\n";
    // v.reserve(5);
    // v1.reserve(5);
    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";
    // std::cout << "--------------------------\n";
    // v.clear();
    // v1.clear();
    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";


    /////////////////// assign ------------------------------

    // std::cout << "\nAssign\n";
    // ft::Vector<int> f;
    // std::vector<int> f1;

    // f.push_back(1);
    // f.push_back(2);
    // f.push_back(3);
    // f.push_back(4);

    // f1.push_back(1);
    // f1.push_back(2);
    // f1.push_back(3);
    // f1.push_back(4);
    
    // std::cout << f.size() << " | " <<  f.capacity() << "\n";
    // std::cout << f1.size() << " | " <<  f1.capacity() << "\n";
    //  std::cout << "--------------------------\n";
    // f.resize(5, 1);
    // f1.resize(5, 1);
    // std::cout << f.size() << " | " <<  f.capacity() << "\n";
    // std::cout << f1.size() << " | " <<  f1.capacity() << "\n";
    // std::cout << "--------------------------\n";
    // f.clear();
    // f1.clear();
    // std::cout << f.size() << " | " <<  f.capacity() << "\n";
    // std::cout << f1.size() << " | " <<  f1.capacity() << "\n";

    ////////////////////////// weird error ---------------------------
    std::vector<std::string> v1(10, "hi ");
    std::string s1;
    std::string ft_s1;
    ft::Vector<std::string> ft_v1(10, "hi ");

    for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1[i];

    for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s1 += *it;

    std::cout << (s1==ft_s1) << "\n";
}