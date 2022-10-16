# ifndef MAP_HPP
#define MAP_HPP

#include "RBTree.hpp"
#include "iterator.hpp"
#include <stdexcept>
#include <utility>
//#include <cstddef>
//#include <memory.h>

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< std::pair<const Key, T> > >
class Map {

// --------------------------- 1- Members Types are public ------------------------------
	
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

// -------------------------- 2- Member Class [implement value_compare] -----------------
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

// --------------------------- 3- Private attributes ------------------------------------

	private:
    // Idk why: when I use pointer to _Tree* ==> I get segmentation dump
        RBTree<key_type, value_type, allocator_type> _Tree;
 

//	------------------------- 4- Public Member Functions of Map -------------------------

	public:

//	-------------------------- 5- Canonical Form of map ---------------------------------

    Map() {
        //std::cout << "Default constructor of map\n";
    }
    ~Map() {
        //std::cout << "Map destructor\n";
		// if (!empty())
    }

// --------------------------- 6- size() and max_size() ---------------------------------

    // 1- std::map::empty() ==> [bool empty() const;]
    bool empty() const {
        if (size() == 0)
            return true;
        return false;
    }
    // 2- std::map::size() ==> [return the size (number of elements)]
    size_type size() const {
	    return _Tree.getSize();
    }
    // 3- std::map::max_size() 

//  -------------------------- 7- Public Typedef of Iterator ----------------------------

	public:
		typedef typename ft::Iterator_map<RBTree<key_type, value_type, allocator_type>, value_type > iterator;

//	-------------------------- 8- begin() and end() -------------------------------------
	iterator begin() {
		//return _Tree.get_begin();
    	return iterator(&_Tree, _Tree.get_begin()->value);
	}

	iterator end() {
		//return _Tree.get_end();
    	return iterator(&_Tree, _Tree.get_end()->value);
	}


//	-------------------------- 9- Accessors at() && operator[] --------------------------

 // 1- std::map::at

	// 1.1- mapped_type& at(const key_type& key);	
	/*
    	Returns a reference to the mapped value of the element identified with key.
    	if(key) does not match the key of any element the function throws an
        	"out_of_range" exception.
  	*/

    mapped_type& at(const key_type& key) {
		iterator iter;
		
		/*
		    std::map<int, int> m;
    		m.at(9);
				//	-------- VS -----------------
			ft::Map<int, int> m;
    		m.at(9);
		*/

		iter = find(key);
		if (iter == end())
			throw std::out_of_range("map::at");
		return (*iter).second;
	}	
    
	// 1.2- const mapped_type& at(const key_type& key) const;
	//const mapped_type& at(const key_type& key) const {}

 // 2- std::map::[] aka [ mapped_type& operator[](const key_type& key); ]
  	/*
     	if (key) matches the key of an element in the container, the function returns
        	a reference to its mapped value.
     	else
	   		The function insert a new element with that key, with no default initializer of value_type 
			and returns a reference to its mapped_value.
  	*/
    mapped_type& operator[](const key_type& key) {
    	iterator iter;
		
		//std::cout << "operator[] with key: " << key << "\n\n\n\\n";
		iter = find(key);
		if (iter != end())
			return (*iter).second;
		else
		{
			//std::cout << "operator[] insert new key\n";
			iter = insert(std::make_pair(key, mapped_type())).first;
			//_Tree.printTree();
			//std::cout << "--------------\n";
			return (*iter).second;
		}
    }

//	------------------------ 10- find(), count(), lower/uperbound(), equal_range() ------
 
 // 4- std::map::find() 

    // 4.1- iterator find(const key_type& k);
    iterator find(const key_type& k) {
        Node<value_type>* node;
        iterator it;

		//std::cout <<  "--------------------------- Lets search for this Key ==> " << k << " --------------------------------------\n";
        node = _Tree.searchByKey(k);
		//std::cout << " --------------------------- search done -------------------------------------------------- \n";
        if (!node)
		{
			//std::cout << "=====> NOOO node find() WITH THAT KEY ==> " << k << "\n\n";
            return (this->end()); // return _end_node
		}
		//std::cout << "=====> Node find() WITH THAT KEY ==> " << k << " " << node << "\n\n";
		//node->printNode();
        it = iterator(&_Tree, node->value);//it = node; // Is this construct from node to Iterator and How ????????????
		//std::cout << "\n The content of the iterator in find() method " << it->first << " | " << it->second << "\n";
        return it;
    }
    // 4.2- const_iterator find(const key_type& k) const;

 // 5- std::map::count()
	/*
		Searches in the container for the elements with a key equivalent to K.

		And because all elements in a map container have unique key, the fct can only
			return 1 (if the element is found) or zero (otherwise);
	*/
	// size_type count (const key_type& k) const;
	size_type count (const key_type& k) const {
		if (_Tree.searchByKey(k) == NULL)
			return (0);
		return 1;
	}

 // 6- std::map::upper_bound
	/*
		Returns an iterator pointing to the first element that is greater than key.
		==> If no such element is found, past-the-end (end() iterator) is returned.
	*/
	// iterator upper_bound( const Key& key );
	iterator upper_bound( const Key& key ) {
		Node<value_type>* node;

		node = _Tree.searchByKey(key);
		if (node)
			return iterator(_Tree, _Tree.next_node(node));
		return end();
	}
	// const_iterator upper_bound( const Key& key ) const;

 // 7- std::map::lower_bound
	/*
		Returns an iterator pointing to the first element that is not less than key
				aka greater or equal to key
		==> If no such element is found, past-the-end (end() iterator) is returned.
	*/
	//iterator lower_bound( const Key& key );
	iterator lower_bound( const Key& key ) {
		Node<value_type>* node;

		node = _Tree.searchByKey(key);
		if (node)
		{
			return iterator(_Tree, node);
		}
		return end();;
	}
	//const_iterator lower_bound( const Key& key ) const;

 // 8- std::map::equal_range
	/*
		Returns the bounds of a range includes the elements in the container.
			aka [lower_bound, upper_bound]
		
		==> If no matches are found, the range returned has a length of zero,
			with both iterators pointing to the first element thas has a key
	*/
	//pair<iterator,iterator> equal_range (const key_type& k);
	std::pair<iterator,iterator> equal_range (const key_type& k) {
		return std::make_pair(lower_bound(), upper_bound());
	}
	//pair<const_iterator,const_iterator> equal_range (const key_type& k) const;

//	-------------------------- 11- Methods insert(), erase() ----------------------------

 // Helper
	void call_print() {
		_Tree.printTree();
	}

 // 5- std::map::insert
    
	// 5.1- std::pair<iterator, bool> insert(const value_type& val);
	std::pair<iterator, bool> insert(const_reference val) {
		
		iterator iter_exist;

        //if (empty())
		//	std::cout << "--- Map is empty ----\n";

		iter_exist = find(val.first);
		if (iter_exist == this->end())
		{
		//	std::cout << "        --------Element not found -------                \n";
			iter_exist = iterator(&_Tree, _Tree.insertion_RBTree(val)->value);
			//_Tree.printTree();
		//	std::cout << (*iter_exist).first << " | " << (*iter_exist).second << "\n";
		//	std::cout << "-----------------------------------------------------------\n";
			return std::make_pair(iter_exist, true);
		}
		return std::make_pair(iter_exist, false);
	}
	
	// 5.2- iterator insert(iterator position, const value_type& val);
	iterator insert(iterator position, const_reference val) {
		iterator iter;

    std::cout << "------------ NOT TESTED : insert  -----------\n";
		iter = find(val.first);
		if (iter == position)
			return position;
		else
		 	return (insert(val).first);
	}
	
	// 5.3- template <class Iterator> void inset(InputIterator first, InputIterator last);
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		while (first != last)
		{
			insert(*first);
			first++;
		}
	}

 // 6- std::map::erase
    
	// 6.1- void erase(iterator position);
	void erase(iterator position)
	{
		//std::cout << "ERase 1\n";
		//_Tree.printTree();
		//std::cout << "KEY to erase: "<< position->first << "\n";
		if (find((*position).first) != end())
			_Tree.delete_RBTree((*position).first);
		//std::cout << "end ERase 1\n";
	}
    
	// 6.2- size_type erase(const key_type& k);
	size_type erase(const key_type& key)
	{
		//std::cout << "ERase 2\n";
		if (find(key) != end())
		{
			_Tree.delete_RBTree(key);
			//std::cout << "end ERase 2\n";
			return 1;
		}
		//std::cout << "end ERase 2\n";
		return 0;
	}
    
	// 6.3- void erase(iterator first, iterator last);
	void erase(iterator first, iterator end)
	{
		//std::cout << "ERase 3\n";
		// iterator iter;
		while (first != end)
			this->erase(first++);
		//std::cout << "end ERase 3\n";
	}

 // 7- clear
	void clear()
	{
		erase(begin(), end());
	}

};

}

#endif