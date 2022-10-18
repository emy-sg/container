# ifndef VECTOR_HPP
#define VECTOR_HPP

/* Vectors are just like arrays, 
 * 	cuz vectors use contiguous storage locations for their elements
 * 	but unlike arrays, their size can change dynamically, their storage being handled automatically by the container.
*
*  This array may need to be reallocated in order to grow in size when new elements are inserted, which implies allocating a new array and moving all elements to it.
*/
#include "iterator.hpp"
#include "const_iterator.hpp"
#include <cstddef>
#include <iostream>
#include <memory.h>
#include <stdexcept>


//  Why use of "explicit" keyword in C++ ? [ used with constructors ]
//==> It is used to mark "constructors" to not implicitly convert types in C++.


namespace ft {
    template < class T, class Alloc = std::allocator<T> >
    class Vector {
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
        //typedef typename ft::my_RandomAccessIterator<const value_type> const_iterator;
        //typedef typename ft::my_ReverseRandomAccessIterator<value_type> reverse_iterator;
        //typedef typename ft::my_ReverseRandomAccessIterator<const value_type> const_reverse_iterator;
        // difference_type and size_type
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

    private:
        pointer _array; // value_type *_array;
        size_t _size;
        size_t _capacity;

    public:

// 1- Iterator
        typedef typename ft::my_Iterator<value_type> iterator;
        typedef typename ft::my_Iterator<const value_type>  const_iterator;

        // iterator begin();  
        iterator begin() {
            return _array; // why not ? return iterator(_array);
        }
        // const_iterator begin()
        // const_iterator begin() const {
        //     return const_iterator(_array);
        // }

    // The past-the-end element is the theoretical element that would follow the last element in the vector. It does not point to any element, and thus shall not be dereferenced.

        // iterator end();
        iterator end() {
            return _array + size(); // WHY NOT? return iterator(_array + size());
        }
        // const_iterator end() const;
        // const_iterator end() const {
        //     return const_iterator(_array + size());
        // }

        //reverse_iterator rbegin();
        //const_reverse_iterator rbegin() const;
        //reverse_iterator rend();
        //const_reverse_iterator rend() const;

// 2- get_allocator(): returns a copy of the allocator object associated with the vector
        allocator_type get_allocator() const
        {
            return allocator_type();
        }
        
// 3- default constructor
        Vector() {
            std::cout << "Default vector constructor\n";
            _size = 0;
            _capacity = 0;
            std::cout << _array << "\n";
            //std::cout << "size " << i.size() << std::endl;  // size = 0
	        //std::cout << "max_size " << i.max_size() << std::endl; // max_size = 4611686018427387903
	        //std::cout << "capacity " << i.capacity() << std::endl; // capacity = 0
        }
        // 2- fill vector size n, with the same value
        explicit Vector (size_type n, value_type var) {
            //std::cout << "Constructor fill vector size :" << n << "\n";
            _size = n;
            _capacity = n;

            // Step 1: Allocate for n value:
            // P.S: Calls to "Allocator::allocate" may throw (bad_allocator)
            // ==> throw an exception of type std::bad_alloc or a class derived from std::bad_alloc
            _array = get_allocator().allocate(n);
            // Step 2: Construct for value_type var
            for (size_type i=0; i<n; i++)
                get_allocator().construct(_array + i, var);
        }
        // 3- range Constructor
        // template < class InputIterator >
        // explicit Vector (InputIterator first, InputIterator last) {
        //     std::cout << "Range Constructor of vector\n";
                
        //     // Step 1: create an array of value_type;
        //     value_type* array;
                
        //     size_type i = 0;
        //     for(iterator it = first; it < last; ++it)
        //     {
        //         array[i] = *it;
        //         ++i;
        //     }
        //     // Step 2: Allocate for i element in the vector
        //     _array = get_allocator().allocate(i);
        //     // Step 3: Construct for value_type var
        //     /*
        //       Not this(won't work like that):
        //         for (size_type j=0; j<i; j++)
        //             _array[j] = array[i];
        //     */
        //     for (size_type j=0; j<i; j++)
        //         get_allocator().construct(_array + j, array[j]);
        // }
        // 4- Copy Constructor
        Vector(const Vector& inst) {
            std::cout << "Copy Constructor of vector\n";
            *this = inst;
        }

        Vector& operator=(const Vector& inst) {
            std::cout << "Assignement copy Constructor of vector\n";

            _array = get_allocator().allocate(inst._capacity);
            for (size_type j=0; j < inst._size; j++)
                get_allocator().construct(_array + j, _array[j]);
            return *this;
        }
        // 5- Destructor
        ~Vector() {
            std::cout << "Destructor of vector\n";
            //if (_capacity > 0)
            
            // 3- deallocate the _size element of _array
            for (size_type i = 0; i < _size; i++)
                get_allocator().destroy(_array + i);
            // 4- deallocate space for _capacity of _array
            get_allocator().deallocate(_array, _capacity);

        }

// 4- empty(), size(),capacity(), max_size()
        bool empty() const {
            if (_size == 0)
                return true;
            return false;
        }
        size_type size() const {
            return _size;
        }
        size_type capacity() const {
            return _capacity;
        }
        //  What is max_size() ?
        // ==> It's the theoretical maximum number of items that could be put in your vector.
        //          (2^64 / 1024) / (size_of_datatype in bytes)
        size_type max_size() const {
            return (9223372036854775807 / sizeof(value_type)); // suppose (2^64 -1) / sizeof()        }
        }

// 5- Accessors: at, operator[], front(), back(), data()

 // 5.1- std::vector::operator[]
    /*
        Returns a reference to the element at position n in the vector container.

        P.S:
            Calling front() on an empty container causes undefined behavior.
    */
    // reference operator[](size_type n);
    reference operator[](size_type n) {
        return _array[n];
    }
    // const_reference operator[](size_type n) const;
    const_reference operator[](size_type n) const {
        return _array[n];
    }

 // 5.2- std::vector::at()
    /*
        Returns a reference to the element at position n in the vector.
        
        The function automatically checks whether n is within the bounds of valid elements in the vector,
            if not, it throw an out_of_range exception.
    */
    // reference at(size_type n);
    reference at(size_type n) {
        if (n < _size)
            return _array[n];
        else
            throw std::out_of_range("vector::_M_range_check: __n >= this->size()");
    }
    // const_reference at(size_type n) const;
    const_reference at(size_type n) const {
        if (n < _size)
            return _array[n];
        else
            throw std::out_of_range("vector::_M_range_check: __n >= this->size()");
    }

 // 5.3- std::vector::front()
    /*
        This fct returns a reference to the First element in the vector.
        ==> Unlike vector::begin, which returns an iterator to this same element, 
            this returns a direct reference to it.
        P.S:
            Calling front() on an empty container causes undefined behavior.
    */
    // reference front();
    reference front() {
        return _array[0]; // First element has a position of O
    }
    // const_reference front() const;
    const_reference front() const {
        return _array[0]; // First element has a position of O
    }

 // 5.4- std::vector::back()
     /*
        This fct returns a reference to the past-the-end element in the vector.
        ==> Which is the theoretical element that would follow the last element in the vector.

        ==> Unlike vector::end, which returns an iterator to this same element, 
            this returns a direct reference to it.
        P.S:
            Calling back() on an empty container causes undefined behavior.
    */
    // reference back();
    reference back() {
        return _array[_size]; //
    }
    // const_reference back() const;
    const_reference back() const {
        return _array[_size]; // 
    }

 // 5.5- std::vector::data()
    /*
        Returns a direct pointer to the memory array used internally by the vector,
            to store its owned elements.
    */
    // pointer data();
    pointer data() {
        return _array;
    }
    // const_pointer data() const;
    const_pointer data() const {
        return _array;
    }

// 6- resize(), reserve(),
 //void reserve(size_type n);
    /*

    */
    void reserve(size_type n) {
        pointer arr;

        if (n > capacity())
        {
            // if (n > max_size())
            //     throw std::length_error("");
            //else
            {
                // Allocate space:
                arr = get_allocator().allocate(n);
                // Construct:
                for (size_type i = 0; i < size(); i++)
                    get_allocator().construct(arr+ i, _array[i]);
                //Destroy the other _array;
                for (size_type i = 0; i < size(); i++)
                    get_allocator().destroy(_array + i);
                // Deallocate the other _array;
                get_allocator().deallocate(_array, capacity());

                _array = arr;
            }
        }
    }

 //void resize(size_type n, value_type val = value_type());
    void resize(size_type n, value_type val = value_type()) {
        if (size() == n)
            return ;
        if (size() > n)
        {
            while (size() > n)
                pop_back();
        }
        else if (capacity() > n)
        {
            while (size() > n)
                push_back(val); 
        }
        else {
            reserve(n);
            while (size() > n)
                push_back(val); 
        }
    }

 //void push_back (const value_type& val);
    void push_back (const value_type& val) {
        if (size() == capacity())
        {
            if (size() % 2) // odd
                reserve(size() + 1);
            else
                reserve(size() * 2);
        }
        get_allocator().construct(_array + _size, val);
    }

 //void pop_back();
    void pop_back() {
        get_allocator().destroy(_array + (_size - 1));
    }

 //iterator erase (iterator position);
    /*
        Return an iterator pointing to the element that followed the element erased by the function.
        P.S:
            If position refers to the last element, then the end() iterator is returned.
            ...
            ...
    */
    iterator erase (iterator position) {
        iterator it;

        it = position++;
        get_allocator().destroy(*position);
        return it;
    }
 //iterator erase (iterator first, iterator last);
    iterator erase (iterator first, iterator last) {

    }
 //void assign (size_type n, const value_type& val);
    void assign (size_type n, const value_type& val) {

    }

 //template <class InputIterator>  void assign (InputIterator first, InputIterator last);
    template <class InputIterator>
    void assign (InputIterator first, InputIterator last) {

    }

 //void insert (iterator position, size_type n, const value_type& val);
    void insert (iterator position, size_type n, const value_type& val) {

 }
 //iterator insert (iterator position, const value_type& val);
    iterator insert (iterator position, const value_type& val) {

    }
 //template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last);
    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last) {

    }

};
}

#endif