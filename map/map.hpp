# ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory.h>
//#include "pair.hpp"
#include <map>
#include "RBTree.hpp"

namespace ft {


template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< std::pair<const Key, T> > >
//template < class Key, class T>
class mapi {
    public:
        typedef Key key_type;
        typedef T mapped_type;

        typedef ft::pair<const Key, T> value_type;

        typedef Compare key_compare;  

        // implement value_compare
        /*
template <class Key, class T, class Compare, class Alloc>
class map<Key,T,Compare,Alloc>::value_compare
{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
  friend class map;
protected:
  Compare comp;
  value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
public:
  typedef bool result_type;
  typedef value_type first_argument_type;
  typedef value_type second_argument_type;
  bool operator() (const value_type& x, const value_type& y) const
  {
    return comp(x.first, y.first);
  }
}
        */
       
        typedef Alloc allocator_type;
        typedef typename Alloc::reference reference;
        typedef typename Alloc::const_reference const_reference;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_pointer;

        typedef typename Alloc:: template rebind<Node> nodeAllocatorType;

        typedef iterator;
        typedef const_iterator;

        typedef reverse_iterator;
        typedef const_reverse_iterator;



    private:
        RBTree <key_type, value_type, nodeAllocatorType> *tree;

    
};

}
#endif