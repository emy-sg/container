# ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

// Ressource:
//  https://en.cppreference.com/w/cpp/iterator/iterator

namespace ft {
    template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    class my_RandomAccessIterator;
}

class my_RandomAccessIterator {
    public:
        // Member types [aka typedefs]
        typedef typename ft::iterator_traits<T*> iterator_category;
        typedef typename ft::iterator_traits<T*> value_type;
        typedef typename ft::iterator_traits<T*> difference_type;
        typedef typename ft::iterator_traits<T*> pointer;
        typedef typename ft::iterator_traits<T*> reference;
        
        // Constructors

        // The operators [== !=  > < >= <= ]
        
};

#endif
