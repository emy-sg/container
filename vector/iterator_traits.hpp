# ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

// Ressource:
//  https://en.cppreference.com/w/cpp/iterator/iterator_traits

namespace ft {
    template <class Iter>
    struct iterator_traits;

    template <class T>
    struct iterator_traits<T*>;

    template <class T>
    struct iterator_traits<const T*>;
}

/*
    std::iterator_traits : is the type trait class that provides uniform interface to the properties of 
        iterator types.
*/

// Iter : is the "iterator type" to retrieve properties for;
template <class Iter>
struct iterator_traits {
    // public:
    typedef Iter::difference_type difference_type;
    typedef Iter::value_type value_type;
    typedef Iter::pointer pointer;
    typedef Iter::reference reference;
    typedef Iter::iterator_category iterator_category;
};

// This type trait, may be specialized for user-provided types that may be used as iterators.
// The standard library provides partial specializations for pointer types "T*", which makes it possible to use all iterator-based algorithms with raw pointers.
template <class T>
struct iterator_traits<T*> {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_catory;
};

template <class T>
struct iterator_traits<const T*> {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_catory; 
};


#endif