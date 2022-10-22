# ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

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

    pointer base() const {
        return _iterator;
    }

    reference operator=(pointer ptr) {_iterator = ptr; return (*this); }

    reference operator*() const {return *_iterator; }
    reference operator[] (difference_type n) const { return *(_iterator + n);}

    pointer operator->() {return _iterator; }

//  --------------------  [iter + n] [iter - n]  ---------------------------------

    // 1- operator+(difference_type n) : 
        /* std::my_ReverseIterator::operator+
            my_ReverseIterator operator+(difference_type n) const;
        */
    my_ReverseIterator operator+(difference_type n) const {
        my_ReverseIterator  iter_addition(*this);
        iter_addition._iterator -= n;
        return iter_addition;
    }
    // 2- operator-(difference_type n) :
        /* std::my_ReverseIterator::operator-
            my_ReverseIterator operator-(difference_type n) const;
        */
    my_ReverseIterator operator-(difference_type n) const {
        my_ReverseIterator iter_soustraction(*this);
        iter_soustraction._iterator += n;
        return iter_soustraction;
    }
    // 3- operator+=(difference_type n) : 
        /* std::my_ReverseIterator::operator+=
            my_ReverseIterator operator+=(difference_type n) const;
        */
    my_ReverseIterator operator+=(difference_type n) {
        _iterator += n;
        return *this;
    }
    // 4- operator-=(difference_type n) : 
        /* std::my_ReverseIterator::operator-=
            my_ReverseIterator operator-=(difference_type n) const;
        */
    my_ReverseIterator operator-=(difference_type n) {
        _iterator -= n;
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

    // Step 4: Member friends : The operators [n + a]
    /*  Template friend : [n + a]
        template <value_type>
        friend my_ReverseIterator<value_type> operator+(difference_type n, const my_ReverseIterator<value_type>& iter);
    */
    friend my_ReverseIterator operator+(difference_type n, const my_ReverseIterator& iter) {
        return (iter - n);
    }
    // -------------------------------------------

    // Step 5: Member friends : The operators [== != ]  > < >= <= ]
    friend bool operator==(const my_ReverseIterator& a, const my_ReverseIterator& b) {
        return a._iterator == b._iterator;
    }

    friend bool operator!=(const my_ReverseIterator& a, const my_ReverseIterator& b) {
        return a._iterator != b._iterator;
    }

    // Step 6: Member friends : The operators [iter1 - iter2]
    
    /* Template friend : [a - b]
        template <value_type>
        friend difference_type operator-(const my_ReverseIterator<value_type>& lhs, const my_ReverseIterator<value_type>& rhs);
    */
    friend difference_type operator-(const my_ReverseIterator& lhs, const my_ReverseIterator& rhs) {
        //std::cout << "operator - \n";
        return std::distance(rhs._iterator, lhs._iterator);  // distance(first, last) = last - first; ==> (rhs, lhs) = lhs - rhs;
    }
    // ---------------------------------------------

    // Step 7: Member friends : The operators [ > < >= <= ]
    friend bool operator>(const my_ReverseIterator& a, const my_ReverseIterator& b) {
        if ((a - b) > 0)
            return true;
        return false;
    }
        
    friend bool operator>=(const my_ReverseIterator& a, const my_ReverseIterator& b) {
        //return !(a < b);
        if (a == b || a > b)
            return true;
        return false;
    }

    friend bool operator<(const my_ReverseIterator& a, const my_ReverseIterator& b) {
        //return !(a >= b);
        if (a >= b)
            return false;
        return true;
    }

    friend bool operator<=(const my_ReverseIterator& a, const my_ReverseIterator& b) {
        //return !(a < b);
        if (a > b)
            return false;
        return true;
    }
};

}

#endif