# ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <fstream>
#include <iostream>
#include <iterator>
#include "../iterator_traits.hpp"

// Ressource:
//  https://en.cppreference.com/w/cpp/iterator/iterator

/*
    This means that our custom iterator should inheritate from std::iterator<std::random_access_iterator_tag, T>
    It contains, member types definition.
    Iterator types definition in can be needed by another algo, and so iterator_traits needs too.
*/

namespace ft {

    template <class T>
    class Iterator : std::iterator<std::random_access_iterator_tag, T> {
    public:
        //typedef T value_type;
    // Member types [aka typedefs]    
        typedef typename std::iterator<std::random_access_iterator_tag, T> ::difference_type difference_type; // we need that in a-b
        typedef typename std::iterator<std::random_access_iterator_tag, T> ::value_type value_type;
        typedef typename std::iterator<std::random_access_iterator_tag, T> ::pointer pointer; // operator ->()
        typedef typename std::iterator<std::random_access_iterator_tag, T> ::reference reference; // operator []() && operator*() && operator=(int)
        typedef typename std::iterator<std::random_access_iterator_tag, T> ::iterator_category iterator_category; //v??????

    private:
        pointer _m_ptr; // <== value_type* _m_ptr;    
    
    public:

    // Step 1: Constructors
        Iterator() { // Default constructor
            //std::cout << "Default Iterator Constructor\n";
            _m_ptr = NULL;
        }
        Iterator(value_type* ptr) { //Initalization constructor
            //std::cout << "Parameterized Iterator Constructor\n";
            _m_ptr = ptr;
        }
        // template <class IT>
        Iterator(const Iterator& inst) { // Copy constructor
            //std::cout << "Copy Constructor of Iterator\n";
            *this = inst;
        }
        // template <class IT>
        Iterator& operator=(const Iterator& inst) { // Assignement operator
            //std::cout << "Assignement Constructor of Iterator\n";          
            this->_m_ptr = inst._m_ptr;
            
            return *this;
        }
        ~Iterator() { // Destructor
            //std::cout << "Destructor of Iterator\n";
        }

    // Step 2: Implementing an iterator something like from STL
    // iterator is a nested class in your container.

//  ------------------ Accessors operator =, * and -> ---------------------------   

    operator Iterator<const T>() {
        return _m_ptr;
    }

    reference operator=(pointer ptr) {_m_ptr = ptr; return (*this); }

    reference operator*() const {return *_m_ptr; }
    reference operator[] (difference_type n) const { return *(_m_ptr + n);}

    pointer operator->() {return _m_ptr; }

//  --------------------  [iter + n] [iter - n]  ---------------------------------

    // 1- operator+(difference_type n) : 
        /* std::Iterator::operator+
            Iterator operator+(difference_type n) const;
        */
    Iterator<value_type> operator+(difference_type n) const {
        Iterator<value_type>  iter_addition(*this);
        iter_addition._m_ptr += n;
        return iter_addition;
    }
    // 2- operator-(difference_type n) :
        /* std::Iterator::operator-
            Iterator operator-(difference_type n) const;
        */
    Iterator<value_type> operator-(difference_type n) const {
        Iterator<value_type>  iter_soustraction(*this);
        iter_soustraction._m_ptr -= n;
        return iter_soustraction;
    }
    // 3- operator+=(difference_type n) : 
        /* std::Iterator::operator+=
            Iterator operator+=(difference_type n) const;
        */
    Iterator<value_type> operator+=(difference_type n) {
        _m_ptr += n;
        return *this;
    }
    // 4- operator-=(difference_type n) : 
        /* std::Iterator::operator-=
            Iterator operator-=(difference_type n) const;
        */
    Iterator<value_type> operator-=(difference_type n) {
        _m_ptr -= n;
        return *this;
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
    Iterator& operator++() {
        _m_ptr++;
        return *this;
    }
    // 2- Prefix decrement:
    Iterator& operator--() {
        _m_ptr--;
        return *this;
    }
    // 3- Postfix increment
    Iterator operator++(int) {
        //std::cout << "\n ------------ Post increment ----------------- \n";
        Iterator tmp = *this; // create a copy
        _m_ptr++; // ==> ++(*this)
        return tmp;
    }
    // 4- Postfix decrement
    Iterator operator--(int) {
        Iterator tmp(*this); // create a copy
        _m_ptr--; // ==>   --(*this); 
        return tmp;
    }

//  ---------------------- Non-member (friend methods) -----------------------------------

    // Step 4: Member friends : The operators [n + a]
    /*  Template friend : [n + a]
        template <value_type>
        friend Iterator<value_type> operator+(difference_type n, const Iterator<value_type>& iter);
    */
    friend Iterator<value_type> operator+(difference_type n, const Iterator<value_type>& iter) {
        return (iter + n);
    }
    // -------------------------------------------

    // Step 5: Member friends : The operators [== != ]  > < >= <= ]
    friend bool operator==(const Iterator& a, const Iterator& b) {
        return a._m_ptr == b._m_ptr;
    }

    friend bool operator!=(const Iterator& a, const Iterator& b) {
        return a._m_ptr != b._m_ptr;
    }

    // Step 6: Member friends : The operators [iter1 - iter2]
    
    /* Template friend : [a - b]
        template <value_type>
        friend difference_type operator-(const Iterator<value_type>& lhs, const Iterator<value_type>& rhs);
    */
    friend difference_type operator-(const Iterator<value_type>& lhs, const Iterator<value_type>& rhs) {
        //std::cout << "operator - \n";
        return std::distance(rhs._m_ptr, lhs._m_ptr);  // distance(first, last) = last - first; ==> (rhs, lhs) = lhs - rhs;
    }
    // ---------------------------------------------

    // Step 7: Member friends : The operators [ > < >= <= ]
    friend bool operator>(const Iterator& a, const Iterator& b) {
        if ((a - b) > 0)
            return true;
        return false;
    }
        
    friend bool operator>=(const Iterator& a, const Iterator& b) {
        //return !(a < b);
        if (a == b || a > b)
            return true;
        return false;
    }

    friend bool operator<(const Iterator& a, const Iterator& b) {
        //return !(a >= b);
        if (a >= b)
            return false;
        return true;
    }

    friend bool operator<=(const Iterator& a, const Iterator& b) {
        //return !(a < b);
        if (a > b)
            return false;
        return true;
    }
};

}

#endif
