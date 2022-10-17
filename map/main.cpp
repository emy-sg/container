#include "Map.hpp"
#include <map>
#include <type_traits>

int main() {
    // ft::Map<int, int> me;

    // if (me.empty())
    //     std::cout << "Map is empty\n";
    // else
    //     std::cout << "size of map is " << me.size() << "\n";

    // -------- Test Iterator ---------------
    // std::map<int, int> m;
    
    // m[0] = 1;
    // m[1] = 2;
    // m[2] = 3;

    // std::map<int, int>::iterator iter(m.begin());
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";

    ////////////////////////////////////////////

    // ft::Map<int, int> m;
    // ft::Map<int, int>::iterator iter;

    // std::map<int, int> m;
    // std::map<int, int>::iterator iter;

    // iter = m.begin();
    // //iter++;
    // std::cout << iter->second << "\n";
    // iter++;
    // std::cout << iter->second << "\n";
    // iter++;
    // std::cout << iter->second << "\n";

//  -------------- at() and operator[] ---------------
    ft::Map<int, int> my;
    my[1] =1;
    my[2] = 2;
    my[3] =3;
    my[100] = 100;

    ft::Map<int, int>::iterator it = my.begin();
    //while (it != my.end())
    {
        std::cout << my.size() << "\n";
        std::cout << "begin  " << my.begin()->first << "\n";
        my.erase(it);
        std::cout << my.size() << "\n";
        std::cout << "begin  " << my.begin()->first << "\n";
        it++;
    }
    //my.call_print();
    //my.erase(2);
    //my.call_print();
    // my.insert(std::make_pair("I", 0));
    // my.insert(std::make_pair("YOU", 1));
    // my.insert(std::make_pair("HE", 2));
    // std::cout << "         --------------------- TEST find() ------------------------           \n \n";
    // // std::cout <<  my.find("YOU")->first << " | " <<  my.find("YOU")->second << "\n";
    // std::cout <<  my.find("I")->first << " | " <<  my.find("I")->second << "\n";
    //my.call_print();



}