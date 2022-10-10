# ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <fstream>
#include <iostream>
#include "../iterator_traits.hpp"

// Ressource:
//  https://en.cppreference.com/w/cpp/iterator/iterator

namespace ft {

    template <class T>
    class my_iterator {
    public:
        //typedef T value_type;
    // Member types [aka typedefs]    
        typedef typename ft::iterator_traits<T*>::difference_type difference_type; // we need that in a-b
        typedef typename ft::iterator_traits<T*>::value_type value_type;
        typedef typename ft::iterator_traits<T*>::pointer pointer; // operator ->()
        typedef typename ft::iterator_traits<T*>::reference reference; // operator []() && operator*() && operator=(int)
        typedef typename ft::iterator_traits<T*>::iterator_category iterator_category; 

    private:
        pointer _m_ptr; // <== value_type* _m_ptr;    
    
    public:

    // Step 1: Constructors
        my_iterator() { // Default constructor
            //std::cout << "Default Iterator Constructor\n";
        }
        my_iterator(value_type* ptr) { //Initalization constructor
            //std::cout << "Parameterized Iterator Constructor\n";
            _m_ptr = ptr;
        }
        my_iterator(const my_iterator& inst) { // Copy constructor
            //std::cout << "Copy Constructor of Iterator\n";
            *this = inst;
        }
        my_iterator& operator=(const my_iterator& inst) { // Assignement operator
            //std::cout << "Assignement Constructor of Iterator\n";
            this->_m_ptr = inst._m_ptr;
            return *this;
        }
        ~my_iterator() { // Destructor
            //std::cout << "Destructor of Iterator\n";
        }

    // Step 2: Implementing an iterator something like from STL
    // iterator is a nested class in your container.
    // reference operator*() const {return *_m_ptr; }
    // pointer operator->() {return _m_ptr; }

    reference operator=(pointer ptr) {_m_ptr = ptr; return (*this); }
    reference operator*() const {return *_m_ptr; }
    pointer operator->() {return _m_ptr; }

    // Prefix increment
    my_iterator& operator++() {
        _m_ptr++;
        return *this;
    }
    // Postfix increment
    my_iterator& operator++(int) {
        my_iterator *tmp; // create a copy
        tmp = this;
        _m_ptr++; // ==>   ++(*this); 
        return *tmp;
    }

    // Prefix decrement
    my_iterator& operator--() {
        _m_ptr--;
        return *this;
    }
    // Postfix decrement
    my_iterator& operator--(int) {
        my_iterator *tmp; // create a copy
        tmp = this;
        _m_ptr--; // ==>   --(*this); 
        return *tmp;
    }

    // substracting an iterator from another
    difference_type operator-(const reference sub) {
        return std::distance(this->_m_ptr, sub._m_ptr);
    }

    // Step 4: Member friends : The operators [== !=  > < >= <= ]
    friend bool operator==(const my_iterator& a, const my_iterator& b) {
        return a._m_ptr == b._m_ptr;
    }

    friend bool operator!=(const my_iterator& a, const my_iterator& b) {
        return a._m_ptr != b._m_ptr;
    }
};

// Relational operators [ == != > < >= <= ]

/*template <class Iter>
bool my_RandomAccessIterator::operator==(const Iterator& lhs) {
    return true;
}*/

// Addition operator (operator+)
/*template <class Iter>
iterator<Iterator> operator+();*/

// Subtraction operator (operator-)
/*template <class Iter>
typename Iterator::difference_type operator-();*/

}

#endif
