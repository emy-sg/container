# ifndef VECTOR_HPP
#define VECTOR_HPP

/* Vectors are just like arrays, 
 * 	cuz vectors use contiguous storage locations for their elements
 * 	but unlike arrays, their size can change dynamically, their storage being handled automatically by the container.
*
*  This array may need to be reallocated in order to grow in size when new elements are inserted, which implies allocating a new array and moving all elements to it.
*/

#include <iostream>
#include <memory.h>
#include <vector>


//  Why use of "explicit" keyword in C++ ? [ used with constructors ]
//==> It is used to mark "constructors" to not implicitly convert types in C++.

//  What is max_size() ?
// ==> It's the theoretical maximum number of items that could be put in your vector.
//          (2^64 / 1024) / (size_of_datatype in bytes)

namespace ft {
    template < class T, class Alloc = std::allocator<T> >
    class vector;
}

template < class T, class Alloc = std::allocator<T> >
class vector {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef allocator_type::reference reference;
        typedef allocator_type::const_reference const_reference;
        typedef allocator_type::pointer pointer;
        typedef allocator_type::const_pointer const_pointer;

        // Iterator
        typedef my_RandomAccessIterator<std::random_access_iterator_tag, T> iterator;
        typedef my_RandomAccessIterator<std::random_access_iterator_tag, const T> const_iterator;
        typedef my_ReverseRandomAccessIterator<std::random_access_iterator_tag, T> reverse_iterator;
        typedef my_ReverseRandomAccessIterator<std::random_access_iterator_tag, const T> const_reverse_iterator;

        // difference_type and size_type
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

    private:
        size_t _size;
        size_t _capacity;


    public:
        // 1- default constructor
        explicit vector() {
            _size = 0;
            _capacity = 0;
            std::cout << "size " << i.size() << std::endl;  // size = 0
	        std::cout << "max_size " << i.max_size() << std::endl; // max_size = 4611686018427387903
	        std::cout << "capacity " << i.capacity() << std::endl; // capacity = 0
        }
        // 2- fill vector size n, with the same value
        explicit vector () {
            _size = n;
            _capacity = n;
            std::cout << "size " << i.size() << std::endl;  // size = 0
	        std::cout << "max_size " << i.max_size() << std::endl; // max_size = 4611686018427387903
	        std::cout << "capacity " << i.capacity() << std::endl; // capacity = 0
        }
        // 3- range Constructor
        template < class InputIterator >
        explicit vector (InputIterator first, InputIterator last, ) {
            
        }
        // 4- Copy Constructor
        vector (const vector& x) {

        }

        // size, max_size, resize
        size_type size() const {
            return _size;
        }

        size_type max_size() const {
            return ;
        }

        size_type capacity() const {
            return _capacity;
        }

        bool empty() const {
            if (_size == 0)
                return true;
            return false;
        }

        void reserve(size_type n) {

        }

        void shrink_to_fit() {

        }

        // get_allocator(): returns a copy of the allocator object associated with the vector
        allocator_type get_allocator() const {
            return std::allocator<value_type>;
        }


// implement iterator_traits class
// Then implement iterator, which calls the iterator


};

#endif