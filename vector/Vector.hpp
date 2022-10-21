# ifndef VECTOR_HPP
#define VECTOR_HPP

/* Vectors are just like arrays, 
 * 	cuz vectors use contiguous storage locations for their elements
 * 	but unlike arrays, their size can change dynamically, their storage being handled automatically by the container.
*
*  This array may need to be reallocated in order to grow in size when new elements are inserted, which implies allocating a new array and moving all elements to it.
*/
// #include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "my_Iterator.hpp"
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
        // typedef typename ft::my_Iterator<value_type> iterator;
        // typedef typename ft::my_Iterator<const value_type>  const_iterator;
        typedef typename ft::my_Iterator<pointer> iterator;
        typedef typename ft::my_Iterator<const_pointer>  const_iterator;

        // iterator begin();  
        iterator begin() {
            return _array; // why not ? return iterator(_array);
        }
        // const_iterator begin()
        const_iterator begin() const {
            return const_iterator(_array);
        }

    // The past-the-end element is the theoretical element that would follow the last element in the vector. It does not point to any element, and thus shall not be dereferenced.

        // iterator end();
        iterator end() {
            return _array + size(); // WHY NOT? return iterator(_array + size());
        }
        //const_iterator end() const;
        const_iterator end() const {
            return const_iterator(_array + size());
        }

// 2- Reverse_iterator:

        // typedef typename ft::my_reverseIterator<iterator> reverse_iterator;
        // typedef typename ft::my_reverseIterator<const_iterator> const_reverse_iterator;

        // //reverse_iterator rbegin();
        // reverse_iterator rbegin() {
        //     return _array + size();
        // }
        // //const_reverse_iterator rbegin() const;
        // const_reverse_iterator rbegin() const {
        //     return const_reverse_iterator(_array + size());
        // }

        // //reverse_iterator rbegin();
        // reverse_iterator rend() {
        //     return _array;
        // }
        // //const_reverse_iterator rbegin() const;
        // const_reverse_iterator rend() const {
        //     return const_reverse_iterator(_array);
        // }

// 3- get_allocator(): returns a copy of the allocator object associated with the vector
        allocator_type get_allocator() const
        {
            return allocator_type();
        }
        
// 4- default constructor
        Vector() {
            //std::cout << "Default vector constructor\n";
            _size = 0;
            _capacity = 0;
            //std::cout << _array << "\n";
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
        //     /*for(iterator it = first; it != last; ++it)
        //     {
        //         array[i] = *it;
        //         ++i;
        //     }*/
        //     while (first != last)
        //     {
        //         array[i] = *(++first);
        //         i++;
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
            //std::cout << "Copy Constructor of vector\n";
            *this = inst;
        }

        Vector& operator=(const Vector& inst) {
            //std::cout << "Assignement copy Constructor of vector\n";

            _capacity = inst._capacity;
            _size = inst._size;
            _array = get_allocator().allocate(inst._capacity);
            for (size_type j=0; j < inst._size; j++)
                get_allocator().construct(_array + j, _array[j]);
            return *this;
        }
        // 5- Destructor
        ~Vector() {
            //std::cout << "Destructor of vector\n";
            
            //3- deallocate the _size element of _array
            for (size_type i = 0; i < _size; i++)
                get_allocator().destroy(_array + i);
            // 4- deallocate space for _capacity of _array
            if (_capacity > 0)
                get_allocator().deallocate(_array, _capacity);
    
        }

// 5- empty(), size(),capacity(), max_size()
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

// 6- Accessors: at, operator[], front(), back(), data()

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

// 7- reserve(), resize(), push_back, and pop_back
 
 // 6.1- void reserve(size_type n);
    /*
        Reserve, request a change in capacity.
        if (n > capacity())
            reallocate for n elements
    */
    void reserve(size_type n) {
        // std::cout << "reserve fct \n";
        value_type* arr;

        if (n > capacity())
        {
            // if (n > max_size())
            //     throw std::length_error("");
            //else
            {
                // 1- Allocate space:
                arr = get_allocator().allocate(n);
                // 2- Construct:
                for (size_type i = 0; i < size(); i++)
                    get_allocator().construct(arr+ i, _array[i]);
                
                // // 3- Destroy the other _array;
                for (size_type i = 0; i < size(); i++)
                    get_allocator().destroy(_array + i);
                // 4- Deallocate the other _array;
                if (_capacity > 0)
                    get_allocator().deallocate(_array, capacity());

                // 5- upgrade the capacity()
                _capacity = n;
                // 6- assign the new array to the _array
                _array = arr;
            }
        }
    }

 // 6.2- void resize(size_type n, value_type val = value_type());

    /*
        Resizes the container so that it contains n elements.
        if (n < size())
            reduce the container to its n first element (using pop_back)
        else
            expend the container to n size by adding new element (using push_back)
    */
    void resize(size_type n, value_type val = value_type()) {
        // std::cout << "resize()\n";
        // if (size() == n)
        //     return ;
        if (size() > n) // size > n value ==> pop_back()
        {
            while (size() > n)
                pop_back();
        }
        else if (capacity() >= n) // capacity >= n value ==> construct new element
        {
            while (size() > n)
            {
                get_allocator().construct(_array + _size, val);
                _size++;
            }

            // -------------- OR -----------------
            // while (size() > n)
            //     push_back(val);

        }
        // if capacity < n ==> reserve(upgrade capacity) then construct
        else {
            reserve(n);
            while (size() > n)
            {
                get_allocator().construct(_array, val);
                _size++;
            }
        }
    }

 // 6.3- void push_back (const value_type& val);
    
    /*
        Adds a new element to the end of the vector.
        This effectively increases the container size by one,
            which causes an automatic reallocation if needed.
    */
    void push_back (const value_type& val) {
        //std::cout << "push_back " << size() << " | " << capacity()<< "\n";
        
        // 1- check if there is enough space to add new element
        if (size() == capacity())
        {
            if (capacity() == 0 || capacity() % 2 != 0) // odd
                reserve(capacity() + 1);
            else
                reserve(capacity() * 2);
        }

        // ==> Still idk if I can replace those two beautiful lines by resize()
        //  SHOULD test if resize duplicate the capacity in case it's even number case

        // 2- construct for the new element
        get_allocator().construct(_array + _size, val);

        // 3- upgrade the size of the container
        _size++;
    }

 // 6.4- void pop_back();

    /*
        Removes the last element in the vector.
    */
    void pop_back() {
        //std::cout << "pop_back\n";
        // 1- Destroy the last element
        get_allocator().destroy(_array + (_size - 1));

        // 2- increase the size of the container by one
        _size--;
    }

// 8- erase (), clear()
    /*
        Return an iterator pointing to the element that followed the element erased by the function.
        P.S:
            If position refers to the last element, then the end() iterator is returned.
            ...
            ...
    */
    iterator erase (iterator position) {
        // std::cout << "erase()\n";
        iterator it;

        // 1- store the next element in the container
        it = position++;
        // 2- destroy the element in the curr position
        get_allocator().destroy(_array + (it - begin() + 1));
        // 3- decrease the size of the container
        _size--;

        // 4- return the next position
        return position;
    }

    iterator erase (iterator first, iterator last) {
        // std::cout << "erase(range)\n";

        while (first != last)
            first = erase(first);
        return first;
    }

    // void clear();
    /*
        Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
    */
    void clear() {
        erase(begin(), end());
    }

// 9- Diff btw Assign() VS Insert()

    /*
        With assign vector content, 
            The container destroy all the content, and construct n new values.
        ==> The capacity of the container will not change only the size.

    */
 //void assign (size_type n, const value_type& val);
    void assign (size_type n, const value_type& val)
    {       
        clear();
        resize(n, val);
    }

 //template <class InputIterator>  void assign (InputIterator first, InputIterator last);
    template <class InputIterator>
    void assign (InputIterator first, InputIterator last) {
       clear();
       while (first++ != last)
            push_back(*first);
    }

    /*
        With insert, no clearing of the container.
        ==> Inserting elements in positions other than the "vector end",
             causes the container to relocate all the elements after position.
             bcuz vectors use an array as their underlying storage.  
    */

 //iterator insert (iterator position, const value_type& val);
    iterator insert (iterator position, const value_type& val) {
        if (position == end())
        {
            push_back(val);
            return iterator(_array + size());
        }
        int i;

        i = 0;
        
    }

 //void insert (iterator position, size_type n, const value_type& val);
    void insert (iterator position, size_type n, const value_type& val) {

    }

 //template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last);
    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last) {

    }

// 10- swap

    /*
    */

};
}

#endif