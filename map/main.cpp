#include "map.hpp"

int main() {
    ft::map<int, int> me;

    if (me.empty())
        std::cout << "Map is empty\n";
    else
        std::cout << "size of map is " << me.size() << "\n";
}