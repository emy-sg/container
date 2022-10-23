# ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "../iterator_traits.hpp"
// #include "node.hpp"

namespace ft {

template <class Iter>
class my_ReverseIterator {

public:

    typedef typename ft::iterator_traits<Iter>::difference_type difference_type; // we need that in a-b
    typedef typename ft::iterator_traits<Iter>::value_type value_type;
    typedef typename ft::iterator_traits<Iter>::pointer pointer; // operator ->()
    typedef typename ft::iterator_traits<Iter>::reference reference; // operator []() && operator*() && operator=(int)
    typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category; 

private:
    Iter _iterator;

public:
        // Step 1: Constructors
    my_ReverseIterator() : _iterator() { // Default constructor
        //std::cout << "Default Iterator Constructor\n";
    }
    my_ReverseIterator(Iter iter) : _iterator(iter) { //Initalization constructor
        //std::cout << "Parameterized Iterator Constructor\n";
    }

    my_ReverseIterator(const my_ReverseIterator& inst) { // Copy constructor
        //std::cout << "Copy Constructor of Iterator\n";
        *this = inst;
    }

    my_ReverseIterator& operator=(const my_ReverseIterator& inst) { // Assignement operator
        //std::cout << "Assignement Constructor of Iterator\n";
        this->_iterator = inst.base();
        return *this;
    }
    ~my_ReverseIterator() { // Destructor
        //std::cout << "Destructor of Iterator\n";
    }

    // Step 2: Implementing an iterator something like from STL
    // iterator is a nested class in your container.

//  ------------------ Accessors operator =, * and -> --------------------------- 

    Iter base() const {
        return _iterator;
    }

    // 1- operator->() return pointer to value_type aka pointer to std::pair
    pointer operator->() {
        return (_iterator).operator->();  /// T5arbi9a zatha
            // bcuz I don't know if value or *value in NOde class
    }

    // 2- operator*() return reference to value_type aka reference to std::pair
    reference operator*() const {
        return *(_iterator);
    }

// --------------------- Pre / Post crementation  --------------------------------

   // What is the diff between pre and post (increment/decrement) operator ??

    /*
        pre: [++it] ==> operator++()
            increment/decrement the variable, before assigning the value to the variable.
        post: [it++] ==> operator++(int)
            increment/decrement the variable, after assigning the value to the variable.
    */

    // 1- Prefix increment:
    my_ReverseIterator& operator++() {
        _iterator--;
        return *this;
    }
    // 2- Prefix decrement:
    my_ReverseIterator& operator--() {
        _iterator++;
        return *this;
    }
    // 3- Postfix increment
    my_ReverseIterator operator++(int) {
        //std::cout << "\n ------------ Post increment ----------------- \n";
        my_ReverseIterator tmp = *this; // create a copy
        _iterator--; // ==> ++(*this)
        return tmp;
    }
    // 4- Postfix decrement
    my_ReverseIterator operator--(int) {
        my_ReverseIterator tmp(*this); // create a copy
        _iterator++; // ==>   --(*this); 
        return tmp;
    }

//  ---------------------- Non-member (friend methods) -----------------------------------
    
    friend bool operator==(const my_ReverseIterator& a, const my_ReverseIterator& b) {
        return a._iterator == b._iterator;
    }

    friend bool operator!=(const my_ReverseIterator& a, const my_ReverseIterator& b) {
        return a._iterator != b._iterator;
    }

};

}

#endif