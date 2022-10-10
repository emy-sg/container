# ifndef VECTOR_HPP
#define VECTOR_HPP

/* Vectors are just like arrays, 
 * 	cuz vectors use contiguous storage locations for their elements
 * 	but unlike arrays, their size can change dynamically, their storage being handled automatically by the container.
*
*  This array may need to be reallocated in order to grow in size when new elements are inserted, which implies allocating a new array and moving all elements to it.
*/
#include "iterator.hpp"
#include <iostream>
#include <memory.h>


//  Why use of "explicit" keyword in C++ ? [ used with constructors ]
//==> It is used to mark "constructors" to not implicitly convert types in C++.

//  What is max_size() ?
// ==> It's the theoretical maximum number of items that could be put in your vector.
//          (2^64 / 1024) / (size_of_datatype in bytes)

namespace ft {
    template < class T, class Alloc = std::allocator<T> >
    class vector {
    public:
    // Member types
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        // Iterator
        //typedef typename ft::my_RandomAccessIterator<value_type> iterator;
        //typedef typename my_RandomAccessIterator<const T> const_iterator;
        //typedef typename my_ReverseRandomAccessIterator<T> reverse_iterator;
        //typedef typename my_ReverseRandomAccessIterator<const T> const_reverse_iterator;
        // difference_type and size_type
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

    private:
        value_type *_array;
        size_t _size;
        size_t _capacity;
        // iterator _begin;
        // iterator _end;

    public:
    // Iterator
        typedef typename ft::my_iterator<value_type> iterator;
        //typedef typename ft::my_iterator<pointer>  iterator;

    // Vector
        // 1- default constructor
        vector() {
            std::cout << "Default vector constructor\n";
            _size = 0;
            _capacity = 0;
            std::cout << _array << "\n";
            //std::cout << "size " << i.size() << std::endl;  // size = 0
	        //std::cout << "max_size " << i.max_size() << std::endl; // max_size = 4611686018427387903
	        //std::cout << "capacity " << i.capacity() << std::endl; // capacity = 0
        }
        // 2- fill vector size n, with the same value
        explicit vector (size_type n, value_type var) {
            std::cout << "fill vector size :" << n << "\n";
            _size = n;
            _capacity = n;
            // Step 1: Allocate for n value
            _array = get_allocator().allocate(5);
            for (size_type i=0; i<n; i++)
                _array[i] = var;
            // Step 2: begin and end 
        }
        // 3- range Constructor
        // template < class InputIterator >
        // explicit vector (InputIterator first, InputIterator last, ) {
            
        // }
        // 4- Copy Constructor
        // vector (const vector& x) {

        // }

        // 5- Destructor
        ~vector() {
            std::cout << "Destructor of vector\n";
            // deallocate the _array
        }

        // 1- size, max_size, resize
        size_type size() const {return _size; }
        // size_type max_size() const {return ; }
        size_type capacity() const {return _capacity; }

        bool empty() const {
            if (_size == 0)
                return true;
            return false;
        }
        //void reserve(size_type n) {}
        //void shrink_to_fit() {}
        
        // 2- get_allocator(): returns a copy of the allocator object associated with the vector
        allocator_type get_allocator() const
        {
            return allocator_type();
        }

        // 3- begin() and end()
        iterator begin() const {
            return _array;
        }

        iterator end() const {
            return _array + size();
        }
        // implement iterator_traits class
        // Then implement iterator, which calls the iterator
    };
}

#endif