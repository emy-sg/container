# ifndef VECTOR_HPP
#define VECTOR_HPP

/* Vectors are just like arrays, 
 * 	cuz vectors use contiguous storage locations for their elements
 * 	but unlike arrays, their size can change dynamically, their storage being handled automatically by the container.
*
*  This array may need to be reallocated in order to grow in size when new elements are inserted, which implies allocating a new array and moving all elements to it.
*/
#include "../reverse_iterator.hpp"
#include "iterator.hpp"
#include "../enable_if.hpp"
#include "../compare.hpp"
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory.h>
#include <new>
#include <stdexcept>


//  Why use of "explicit" keyword in C++ ? [ used with constructors ]
//==> It is used to mark "constructors" to not implicitly convert types in C++.


namespace ft {
    template <
        class T,
        class Alloc = std::allocator<T> >

class Vector {
    
    public:

        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

    private:

        pointer _array; // value_type *_array;
        size_t _size;
        size_t _capacity;
        allocator_type _alloc;

    public:   // Member Methods of Vector

// ---------------------- 1- Iterator -------------------------------------------

        // The first implementation of iterator that works fine, ma5adamch m3a const iterator
        // typedef my_Iterator<value_type> iterator;
        // typedef my_Iterator<const value_type>  const_iterator;

        // The second implementation of iterator that didn't work in the first time, but now all it's good
        typedef my_Iterator<pointer> iterator;
        typedef my_Iterator<const_pointer>  const_iterator;     

    //  -------------------------- [begin(), end()] ---------------------------------

        /*
            Returns an iterator pointing to the first element in the vector.
        */

        // iterator begin();  
        iterator begin() {
            return iterator(_array); // _array; // why not ? return iterator(_array);
        }
        // const_iterator begin()
        const_iterator begin() const {
            return const_iterator(_array);
        }

        /*
            Return:
                The past-the-end element is the theoretical element that would follow the last element in the vector. It does not point to any element, and thus shall not be dereferenced.
        */
        // iterator end();
        iterator end() {
            return iterator(_array + size()); // WHY NOT? return iterator(_array + size());
        }
        //const_iterator end() const;
        const_iterator end() const {
            return const_iterator(_array + size());
        }

// --------------------- 2- Reverse_iterator ------------------------------------

        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator; 

        //  -------------------------- [rbegin(), rend()] ---------------------------------

        //reverse_iterator rbegin();
        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }
        //const_reverse_iterator rbegin() const;
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        //reverse_iterator rbegin();
        reverse_iterator rend() {
            return reverse_iterator(begin());
        }
        //const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

// --------------------- 3- _alloc -------------------------------------

    /*
        Returns a copy of the allocator object associated with the vector
    */
 
    allocator_type get_allocator() const
    {
        //return allocator_type();
        return _alloc;
    }
        
// --------------------- 4- default constructor ---------------------------------
        //Vector() {
        explicit Vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
            //std::cout << "Default vector constructor\n";
            _size = 0;
            _capacity = 0;
            _array = NULL;

            //std::cout << _array << "\n";
            //std::cout << "size " << i.size() << std::endl;  // size = 0
	        //std::cout << "max_size " << i.max_size() << std::endl; // max_size = 4611686018427387903
	        //std::cout << "capacity " << i.capacity() << std::endl; // capacity = 0
        }

        // 2- fill vector size n, with the same value
        //explicit Vector (size_type n, value_type var) {
        explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc)
        {   
            //std::cout << "Constructor fill vector size :" << n << "\n";
            _size = n;
            _capacity = n;

            // Step 1: Allocate for n value:
            // P.S: Calls to "Allocator::allocate" may throw (bad_allocator)
            // ==> throw an exception of type std::bad_alloc or a class derived from std::bad_alloc
            _array = _alloc.allocate(n);
            // Step 2: Construct for value_type var
            for (size_type i=0; i<n; i++)
                _alloc.construct(_array + i, val);
        }

        // 3- range Constructor
        // ===> https://eli.thegreenplace.net/2014/sfinae-and-enable_if/
        template < class InputIterator >
        Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if <!ft::is_integral<InputIterator>::value, int>::type b = int()) : _alloc(alloc)
        {
            //std::cout << "Range Constructor of vector\n";
                
            // Step 1: Create an array of value_type;
            _size = 0;
            _capacity = 0;
            _array = NULL;
            
            // Step 2: Add new element in the vector[ Allocate && Construct ]
            while (first != last)
                push_back(*(first++));
        }

        // 4- Copy Constructor
        Vector(const Vector& inst) {
            //std::cout << "Copy Constructor of vector\n";
            _size = 0;
            _capacity = 0;
            _array = NULL;
            *this = inst;
        }

        Vector& operator=(const Vector& inst) {
            //std::cout << "Assignement copy Constructor of vector\n";

            //1- deallocate the _size element of _array
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_array + i);

            // 2- deallocate space for _capacity of _array
            if (_capacity > 0)
                _alloc.deallocate(_array, _capacity);

            // 3- Initialize capacity and size to default
            _capacity = inst._capacity;
            _size = inst._size;
            _alloc = inst._alloc;

            // 4- fill the array
            if (_capacity != 0)
            {
                _array = _alloc.allocate(_capacity);
                for (size_type j=0; j < inst._size; j++)
                    _alloc.construct(_array + j, inst._array[j]);
            }
            else
                _array = NULL;
            return *this;
        }

        // 5- Destructor
        ~Vector() {
            //std::cout << "Destructor of vector\n";
            
            //3- deallocate the _size element of _array
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_array + i);
            // 4- deallocate space for _capacity of _array
            if (_capacity > 0)
                _alloc.deallocate(_array, _capacity);
    
        }

// ------- 5- empty(), size(),capacity(), max_size() ----------------------------

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
            if (sizeof(value_type) == 1)
                return (9223372036854775807); // suppose (2^64 -1) / sizeof()        }
            else
                return (_alloc.max_size());
        }

// ----- 6- Accessors: at, operator[], front(), back(), data() ------------------

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
        return _array[_size - 1]; //
    }
    // const_reference back() const;
    const_reference back() const {
        return _array[_size - 1]; // 
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

// -------- 7- reserve(), resize(), push_back, and pop_back ---------------------
 
 // 6.1- void reserve(size_type n);
    /*
        Reserve, request a change in capacity.
        if (n > capacity())
            reallocate for n elements
    */
    void reserve(size_type n) try {
        // std::cout << "reserve fct \n";
        value_type* arr;

        if (n > capacity()) // reserve
        {
            //std::cout << "reserve()\n";
            // if (n > max_size())
            //     throw std::length_error("");
            //else
            {
                // 1- Allocate space:
                arr = _alloc.allocate(n);
                // 2- Construct:
                for (size_type i = 0; i < size(); i++)
                    _alloc.construct(arr+ i, _array[i]);

                // // 3- Destroy the other _array;
                for (size_type i = 0; i < size(); i++)
                    _alloc.destroy(_array + i);
                // 4- Deallocate the other _array;
                if (_capacity > 0)
                    _alloc.deallocate(_array, capacity());

                // 5- upgrade the capacity()
                _capacity = n;
                // 6- assign the new array to the _array
                _array = arr;
                
                //std::cout << "After reserve ==> size: " << size() <<  " | capacity " << capacity() << "\n";
            }
        }
    }
    catch (std::bad_alloc e)
    {
        std::cout << e.what() << std::endl;
    }

 // 6.2- void resize(size_type n, value_type val = value_type());

    /*
        Resizes the container so that it contains n elements.
        if (n < size()) // n is smaller than the current size
            reduce the container to its n first element (using pop_back aka destroy elemnents)
        else // n is greater than the current size, 
            expend the container to n size by adding new element at the end (using push_back)
    */
    void resize(size_type n, value_type val = value_type()) try{
        // std::cout << "resize() " << capacity() << " | " << size()  << "\n";

        // if (size() == n)
        //     return ;
        if (size() > n) // size > n value ==> pop_back()
        {
            //std::cout << "case 1\n";
            while (size() > n)
                pop_back();
        }
        else if (capacity() >= n) // capacity >= n value ==> construct new element
        {
            //std::cout << "case 2 " <<  size() << "\n";
            while (size() < n)
            {
                _alloc.construct(_array + size(), val);
                _size++;
            }
            // -------------- OR -----------------

            // while (size() > n)
            //     push_back(val);

        }
        else  // if capacity < n ==> reserve(upgrade capacity) then construct
        {
            //std::cout << "case 3\n";
            // if (capacity() % 2 == 0)
            //     reserve(capacity() * 2);
            // else
                reserve(n);
            //std::cout << "size: " << size() << "\n";
            while (size() < n)
            {
                _alloc.construct(_array + size(), val);
                _size++;
            }
        }
    }
    catch (std::bad_alloc e)
    {
        std::cout << e.what() << std::endl;
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
            if (capacity() == 0)
                reserve(capacity() + 1);
            else
                reserve(capacity() * 2);
        }

        // ==> Still idk if I can replace those two beautiful lines by resize()
        //  SHOULD test if resize duplicate the capacity in case it's even number case

        // 2- construct for the new element
        _alloc.construct(_array + _size, val);

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
        _alloc.destroy(_array + (_size - 1));

        // 2- increase the size of the container by one
        _size--;
    }

// --------------------- 8- erase (), clear() -----------------------------------
    /*
        Return an iterator pointing to the element that followed the element erased by the function.
        P.S:
            If position refers to the last element, then the end() iterator is returned.
            ...
            ...
    */
    iterator erase (iterator position) try {
        iterator iter;
        
        iter = position + 1;

        while (iter != end())
        {
            _alloc.destroy((iter - 1).base());
            _alloc.construct((iter - 1).base(), *iter);
            ++iter;
        }
        _alloc.destroy((iter - 1).base());
        --_size;
        //iter = end(); 
        return position;
    }
    catch (std::exception)
    {
        std::cout << "this erase" << std::endl;
        return iterator();
    }

    iterator erase (iterator first, iterator last) {
        //std::cout << "erase(range)\n";

        while (first != last--)
        {
            //std::cout << *first << std::endl;
            erase(first);
        }
        //std::cout << "done erase range\n";
        return first;
    }

    // void clear();
    /*
        Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
    */
    void clear() {
        erase(begin(), end());
    }

// --------------------- 9- Diff btw Assign() VS Insert() -----------------------

 // 9.1- assign()

    /*
        With assign vector content, 
            The container destroy all the content, and construct n new values.
        ==> The capacity of the container will not change only the size.

    */

    //void assign (size_type n, const value_type& val);
    void assign (size_type n, const value_type& val)
    {    
        //std::cout << "assign one element\n";   
        clear();
        //reserve(n * 2);  /// why ???????
        resize(n, val);
    }

    //template <class InputIterator>  void assign (InputIterator first, InputIterator last);
    template <class InputIterator>
    void assign (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if <!ft::is_integral<InputIterator>::value, int>::type b = int()) {
       //std::cout << "assign of range\n";
       clear();
       while (first != last)
            push_back(*(first++));
    }

 // 9.2- insert()

    /*
        With insert, no clearing of the container.
        ==> Inserting elements in positions other than the "vector end",
             causes the container to relocate all the elements after position.
             bcuz vectors use an array as their underlying storage.

        Return:
            An iterator that points to the first of the newly inserted elements.
    */

    //iterator insert (iterator position, const value_type& val);
    iterator insert (iterator position, const value_type& val) {
        //std::cout << "insert one element\n";

        if (position == end()) // case 1: position = end
        {
            //std::cout << "case 1\n";
            push_back(val);
        }
        else if (capacity() >= (size() + 1)) // case 2: enough capacity
        {
            //std::cout << "case 2\n";
            iterator iter;
        
            // 1- iter = end()
            iter = end();
            // 2- update the size 
            ++_size;
            // 3- 
            while (iter != position)
            {
                _alloc.construct(iter.base(), *(--iter));
                _alloc.destroy(iter.base()); 
            }
            _alloc.construct(iter.base(), val);
        }
        else    // case 3: capacity not enough
        {
            //std::cout << "case 3\n";
            pointer array;
            array = _alloc.allocate(size() + 1); // capacity

            iterator iter;
            iter = (end() - 1); // iter = element before end

            size_t new_size = _size;
            while (new_size > 0)
            {
                if (iter == position)
                {
                    _alloc.construct(array + new_size, val);
                    iter--;
                }
                else
                    _alloc.construct(array + new_size, *(iter--));
                new_size--;
            }
            //3- deallocate the _size element of _array
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_array + i);
            // 4- deallocate space for _capacity of _array
            if (_capacity > 0)
                _alloc.deallocate(_array, _capacity);
            // 5- update container attributes
            _array = array;
            _size = _size + 1;
            _capacity = _size + 1;
        }
        return position;
    }

    //void insert (iterator position, size_type n, const value_type& val);
    void insert (iterator position, size_type n, const value_type& val) {
        //std::cout << "insert n elements\n";
        if (position == end()) // case 1: position = end
        {
            std::cout << "case 1\n";
            while (n--)
                push_back(val);
        }
        else if (capacity() >= (size() + n)) // case 2: enough capacity
        {
            std::cout << "case 2\n";
            iterator iter;
        
            // 1- iter = end()
            iter = end() + n;
            // 2- update the size 
            _size += n;
            // 3- 
            while (iter != position)
            {
                _alloc.construct(iter.base(), *(--iter));
                _alloc.destroy(iter.base()); 
            }
            while (n--)
                _alloc.construct(iter.base(), val);
        }
        else    // case 3: capacity not enough
        {
            std::cout << "case 3\n";
            pointer array;
            array = _alloc.allocate(size() + n); // allocate for new capacity

            iterator iter;
            iter = (end() - 1); // iter = element before end

            size_t new_size = _size + n;
            while (new_size > 0)
            {
                if (iter == position)
                {
                    while (n--)
                    {
                        _alloc.construct(array + new_size, val);
                        new_size--;
                    }
                }
                else
                {
                    _alloc.construct(array + new_size, *(iter--));
                    new_size--;
                }
            }
            //3- deallocate the _size element of _array
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_array + i);
            // 4- deallocate space for _capacity of _array
            if (_capacity > 0)
                _alloc.deallocate(_array, _capacity);
            // 5- update container attributes
            _array = array;
            _size = _size + n;
            _capacity = _size + n;
        }
    }

    //template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last);
    // template <class InputIterator>
    // void insert (iterator position, InputIterator first, InputIterator last) {

    // }

// ---------------------- 10- swap ----------------------------------------------

    /*
    */

    // void swap (vector& x);
    void swap (Vector& x) {
        std::swap(_alloc, x._alloc);
        std::swap(_size, x._size);
        std::swap(_capacity, x._capacity);
        std::swap(_array, x._array);
    }

// ---------------------- 11- Non Members functions  -----------------------

    friend void swap (Vector& x, Vector& y) {
        x.swap(y);
    }

 // Relational operators

    /*
        The "equality comparison" aka (operator==) is performed by first comparing sizes,
            and if they match aka sizes, the elements are compared sequentially using 
            operator==, stopping at the first mismatch aka "equal"
    */

    friend bool operator== (const Vector& lhs, const Vector& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator!= (const Vector& lhs, const Vector& rhs) {
        if (lhs.size() != rhs.size())
            return true;
        return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    
    /*
        The "lexicographical less-than" comparison:
            Returns "true" if the range [first, last1) compares "lexicographically less" than the range [first2, last2).
    */

    friend bool operator<  (const Vector& lhs, const Vector& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    friend bool operator<= (const Vector& lhs, const Vector& rhs) {
        return !(lhs > rhs);
    }

    friend bool operator>  (const Vector& lhs, const Vector& rhs) {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    friend bool operator>= (const Vector& lhs, const Vector& rhs) {
        return !(lhs < rhs);
    }
};

// // ------- 11- Non Members functions aka friend -----------------------

//     template <class T, class Alloc>
//     void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {
//         x.swap(y);
//     }

//  // Relational operators

//     /*
//         The "equality comparison" aka (operator==) is performed by first comparing sizes,
//             and if they match aka sizes, the elements are compared sequentially using 
//             operator==, stopping at the first mismatch aka "equal"
//     */

//     template <class T, class Alloc>
//     bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
//         if (lhs.size() != rhs.size())
//             return false;
//         return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
//     }

//     template <class T, class Alloc>
//     bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
//         if (lhs.size() != rhs.size())
//             return true;
//         return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
//     }
    
//     /*
//         The "lexicographical less-than" comparison:
//             Returns "true" if the range [first, last1) compares "lexicographically less" than the range [first2, last2).
//     */

//     template <class T, class Alloc>
//     bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
//         return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
//     }

//     template <class T, class Alloc>
//     bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
//         return !(lhs > rhs);
//     }

//     template <class T, class Alloc>
//     bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
//         return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
//     }

//     template <class T, class Alloc>
//     bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
//         return !(lhs < rhs);
//     }

}

#endif