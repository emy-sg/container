# ifndef MAP_HPP
#define MAP_HPP

#include "RBTree.hpp"
//#include <cstddef>
//#include <memory.h>

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< std::pair<const Key, T> > >
class map {

// 1- Members Types
    public:
        typedef Key key_type;
        typedef T   mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;

        typedef Alloc allocator_type;

        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        /*typedef typename Alloc:: template rebind<Node> nodeAllocatorType;

        typedef iterator;
        typedef const_iterator;

        typedef reverse_iterator;
        typedef const_reverse_iterator;*/

// 2- Member Class [implement value_compare]
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
      };
    */

// 3- Private attributes
    private:
    // Idk why: when I use pointer to _Tree* ==> I get segmentation dump
        RBTree<key_type, value_type, allocator_type> _Tree;
 
 // 4- Member functions
    public:
      map() {
        std::cout << "Default constructor of map\n";
      }
      ~map() {
        std::cout << "Map destructor\n";
      }
      
      map(int i) : _Tree(i) {
        std::cout << "Parameterized constructor of map\n";
      }

    // 1- std::map::size [return the size (number of elements)]
    size_type size() const {
	    return _Tree.getSize();
    }

    // 2- std::map::empty  [bool empty() const;]
    bool empty() const {
        if (size() == 0)
            return true;
        return false;
    }

    // 3- std::map::find
    // iterator find(const key_type& k);
    // const_iterator find(const key_type& k) const;
    // iterator find(const key_type& k) {
    //     Node<value_type>* node;
    //     iterator it;

    //     node = searchByKey(node->value.first);
    //     if (!node)
    //         return (end());
    //     it = node;
    //     return it;
    // }

    // 4- std::map::erase
    // void erase(iterator position);
    // size_type erase(const key_type& k);
    // void erase(iterator first, iterator last);
};

}

#endif