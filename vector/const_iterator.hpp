# ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <fstream>
#include <iostream>
#include "../iterator_traits.hpp"

// First question why implementing this Fucker of constIterator, when we already have an iterator ??
/*
    Well, we gonna need this fucker, exactly in the copyConstructor of the vector.
    If we used the constructor of vector(begin(), end()) within the copyConstructor, who took an const reference to vector.
    well const_iterator begin() will be called automatically.
    And so we need to implement a const_iterator for those fuckers and thank u. 
*/

// Second question const_iterator is an iterator with small diff, what are those differences ?
/*
    Good question, But I don't have the answear, let's try to find one.
    But let's define what is const_iterator first:
        const_iterator it just don't allow you to change the values that they point to, when regular iterator does.
    That's good start.
    So our const_iterator are not suppose to return a reference or pointer to the value.
    Second thing to mention, if we have our iterator it->first ==> suppose that we cannot change anything here
    and same for (*it).
    We also have operator=() that returns reference and change the pointer, what Am i suppose to do with that too.
    ===> Well opeator=()will take as parameter const_iterator like (const_iterator begin() const;), and well return const_reference.
*/

namespace ft {

    template <class T>
    class my_constIterator {
    public:
        //typedef T value_type;
    // Member types [aka typedefs]    
        typedef typename ft::iterator_traits<T>::difference_type difference_type; // we need that in a-b
        typedef typename ft::iterator_traits<T>::value_type value_type;
        typedef typename ft::iterator_traits<T>::pointer pointer; // operator ->()
        typedef typename ft::iterator_traits<T>::reference reference; // operator []() && operator*() && operator=(int)
        typedef typename ft::iterator_traits<T>::iterator_category iterator_category; 

    private:
        pointer _m_ptr; // <== value_type* _m_ptr;    
    
    public:

    // Step 1: Constructors
        my_constIterator() { // Default constructor
            //std::cout << "Default Iterator Constructor\n";
            _m_ptr = NULL;
        }
        my_constIterator(value_type* ptr) { //Initalization constructor
            //std::cout << "Parameterized Iterator Constructor\n";
            _m_ptr = ptr;
        }
        template <class IT>
        my_constIterator(const IT& inst) { // Copy constructor
            //std::cout << "Copy Constructor of Iterator\n";
            *this = inst;
        }
        template <class IT>
        my_constIterator& operator=(const IT& inst) { // Assignement operator
            //std::cout << "Assignement Constructor of Iterator\n";
            _m_ptr = inst.base();
            return *this;
        }
        ~my_constIterator() { // Destructor
            //std::cout << "Destructor of Iterator\n";
        }

    // Step 2: Implementing an iterator something like from STL
    // iterator is a nested class in your container.

//  ------------------ Accessors operator =, * and -> ---------------------------   

        // ==> I just add const keyword to all the Accessors
    const my_constIterator& base() const {
        return _m_ptr;
    }

    const reference operator=(pointer ptr) {_m_ptr = ptr; return (*this); }

    const reference operator*() const {return *_m_ptr; }
    const reference operator[] (difference_type n) const { return *(_m_ptr + n);}

    const pointer operator->() {return _m_ptr; }

//  --------------------  [iter + n] [iter - n]  ---------------------------------

    // 1- operator+(difference_type n) : 
        /* std::my_constIterator::operator+
            my_constIterator operator+(difference_type n) const;
        */
    my_constIterator<value_type> operator+(difference_type n) const {
        my_constIterator<value_type>  iter_addition(*this);
        iter_addition._m_ptr += n;
        return iter_addition;
    }
    // 2- operator-(difference_type n) :
        /* std::my_constIterator::operator-
            my_constIterator operator-(difference_type n) const;
        */
    my_constIterator<value_type> operator-(difference_type n) const {
        my_constIterator<value_type>  iter_soustraction(*this);
        iter_soustraction._m_ptr -= n;
        return iter_soustraction;
    }
    // 3- operator+=(difference_type n) : 
        /* std::my_constIterator::operator+=
            my_constIterator operator+=(difference_type n) const;
        */
    my_constIterator<value_type> operator+=(difference_type n) {
        _m_ptr += n;
        return *this;
    }
    // 4- operator-=(difference_type n) : 
        /* std::my_constIterator::operator-=
            my_constIterator operator-=(difference_type n) const;
        */
    my_constIterator<value_type> operator-=(difference_type n) {
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
    my_constIterator& operator++() {
        _m_ptr++;
        return *this;
    }
    // 2- Prefix decrement:
    my_constIterator& operator--() {
        _m_ptr--;
        return *this;
    }
    // 3- Postfix increment
    my_constIterator operator++(int) {
        //std::cout << "\n ------------ Post increment ----------------- \n";
        my_constIterator tmp = *this; // create a copy
        _m_ptr++; // ==> ++(*this)
        return tmp;
    }
    // 4- Postfix decrement
    my_constIterator operator--(int) {
        my_constIterator tmp(*this); // create a copy
        _m_ptr--; // ==>   --(*this); 
        return tmp;
    }

//  ---------------------- Non-member (friend methods) -----------------------------------

    // Step 4: Member friends : The operators [n + a]
    /*  Template friend : [n + a]
        template <value_type>
        friend my_constIterator<value_type> operator+(difference_type n, const my_constIterator<value_type>& iter);
    */
    friend my_constIterator<value_type> operator+(difference_type n, const my_constIterator<value_type>& iter) {
        return (iter + n);
    }
    // -------------------------------------------

    // Step 5: Member friends : The operators [== != ]  > < >= <= ]
    friend bool operator==(const my_constIterator& a, const my_constIterator& b) {
        return a._m_ptr == b._m_ptr;
    }

    friend bool operator!=(const my_constIterator& a, const my_constIterator& b) {
        return a._m_ptr != b._m_ptr;
    }

    // Step 6: Member friends : The operators [iter1 - iter2]
    
    /* Template friend : [a - b]
        template <value_type>
        friend difference_type operator-(const my_constIterator<value_type>& lhs, const my_constIterator<value_type>& rhs);
    */
    friend difference_type operator-(const my_constIterator<value_type>& lhs, const my_constIterator<value_type>& rhs) {
        //std::cout << "operator - \n";
        return std::distance(rhs._m_ptr, lhs._m_ptr);  // distance(first, last) = last - first; ==> (rhs, lhs) = lhs - rhs;
    }
    // ---------------------------------------------

    // Step 7: Member friends : The operators [ > < >= <= ]
    friend bool operator>(const my_constIterator& a, const my_constIterator& b) {
        if ((a - b) > 0)
            return true;
        return false;
    }
        
    friend bool operator>=(const my_constIterator& a, const my_constIterator& b) {
        //return !(a < b);
        if (a == b || a > b)
            return true;
        return false;
    }

    friend bool operator<(const my_constIterator& a, const my_constIterator& b) {
        //return !(a >= b);
        if (a >= b)
            return false;
        return true;
    }

    friend bool operator<=(const my_constIterator& a, const my_constIterator& b) {
        //return !(a < b);
        if (a > b)
            return false;
        return true;
    }
};

}

#endif