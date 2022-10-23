# ifndef MAP_HPP
#define MAP_HPP

#include "RBTree.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>
#include "../pair.hpp"
#include <cstddef>
#include <memory.h>

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< std::pair<const Key, T> > >
class Map {

// --------------------------- 1- Members Types are public ------------------------------
	
	public:

        typedef Key key_type;
        typedef T   mapped_type;
        typedef ft::pair<const key_type, mapped_type>  value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;

        typedef Alloc allocator_type;

        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;


// --------------------------- 2- Private attributes ------------------------------------

	private:
    // Idk why: when I use pointer to _Tree* ==> I get segmentation dump
        RBTree<key_type, value_type, allocator_type> _Tree;
		//allocator_type _alloc;
		//key_compare _compare; 

//	------------------------- 3- Public Member Functions of Map -------------------------

	public:

 // Returns a copy of the allocator object associated with the map.
	allocator_type get_allocator() const { return allocator_type(); }

// -------------------------- 4- Member Class [implement value_compare] -----------------

    //   template <class Key, class T, class Compare, class Alloc>
    //   class map<Key,T,Compare,Alloc>::value_compare

	class value_compare
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

//	-------------------------- 5- Canonical Form of map ---------------------------------

    explicit Map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
        //std::cout << "Default constructor of map\n";
    }
    ~Map() {
        //std::cout << "Map destructor\n";
		clear();
    }

	template <class InputIterator>
	Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	{
		while (first != last)
			insert(*(first++));
	}

	Map(const Map& inst) {
		//std::cout << "Copy constructor of map\n";

		// Problem deep copy and shallow copy
		insert(inst.begin(), inst.end());
	}

	Map& operator=(const Map& inst) {
		//std::cout << "Assignemenet copy constructor of map\n";
		// Problem deep copy and shallow copy
		//This path is very wrong[Za3ma calling the _Tree assignement operator] *_Tree = *(inst._Tree);
		// Which is in this case useless, we can call insert for use
		clear();
		insert(inst.begin(), inst.end());
		return *this;
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
		// typedef typename ft::Iterator_map<RBTree<key_type, value_type, allocator_type>, value_type > iterator;
		// typedef typename ft::Iterator<RBTree<key_type, value_type, allocator_type>, value_type > iterator;
		// typedef typename ft::Iterator<RBTree<key_type, value_type, allocator_type>, const value_type > const_iterator;

		typedef typename ft::Iterator<value_type> iterator;
		typedef typename ft::Iterator<const value_type> const_iterator;

//	-------------------------- 8- begin() and end() -------------------------------------
	iterator begin() {
		//return _Tree.get_begin();
    	return iterator(_Tree.get_end(), _Tree.get_begin());
		
	}
	// const_iterator begin() const {};
	const_iterator begin() const {
		return const_iterator((Node<const value_type>*)_Tree.get_end(), (Node<const value_type>*)_Tree.get_begin());
	}

	iterator end() {
		//return _Tree.get_end();
    	return iterator(_Tree.get_end(), _Tree.get_end());
	}
	// const_iterator end() const {};
	const_iterator end() const {
		//return _Tree.get_end();
    	return const_iterator((Node<const value_type>*)_Tree.get_end(), (Node<const value_type>*)_Tree.get_end());
	}

// 2- Reverse_iterator:

	typedef typename ft::my_ReverseIterator<iterator> reverse_iterator;
	typedef typename ft::my_ReverseIterator<const_iterator>  const_reverse_iterator; 

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
			iter = insert(ft::make_pair(key, mapped_type())).first;
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
        it = iterator(_Tree.get_end(), node);//it = node; // Is this construct from node to Iterator and How ????????????
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
			return iterator(_Tree.get_end(), _Tree.next_node(node));
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
			return iterator(_Tree.get_end(), node);
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
	ft::pair<iterator,iterator> equal_range (const key_type& k) {
		return ft::make_pair(lower_bound(), upper_bound());
	}
	//pair<const_iterator,const_iterator> equal_range (const key_type& k) const;

//	-------------------------- 11- Methods insert(), erase() ----------------------------
 // 11- std::map::insert
    
	// 11.1- std::pair<iterator, bool> insert(const value_type& val);
	ft::pair<iterator, bool> insert(const_reference val) {
		
		iterator iter_exist;

        //if (empty())
		//	std::cout << "--- Map is empty ----\n";

		iter_exist = find(val.first);
		if (iter_exist == this->end())
		{
		//	std::cout << "        --------Element not found -------                \n";
			iter_exist = iterator(_Tree.get_end(), _Tree.insertion_RBTree(val));
			//_Tree.printTree();
		//	std::cout << (*iter_exist).first << " | " << (*iter_exist).second << "\n";
		//	std::cout << "-----------------------------------------------------------\n";
			return ft::make_pair(iter_exist, true);
		}
		return ft::make_pair(iter_exist, false);
	}
	
	// 5.2- iterator insert(iterator position, const value_type& val);
	iterator insert(iterator position, const_reference val) {
		iterator iter;
		
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

	// 6.1- size_type erase(const key_type& k);
	size_type erase(const key_type& key)
	{
		return _Tree.erase(key);
	}
	
	// 6.2- void erase(iterator position);
	void erase(iterator position)
	{
		_Tree.erase(position->first);
	}
    
	// 6.3- void erase(iterator first, iterator last);
	void erase(iterator first, iterator end)
	{
		while (first != end)
		{
			//std::cout << first->first << " | " << first->second << "\n";
			erase(first++); // use of preincrementation and not postincrementation, thank U
		}
		// std::cout << _Tree._end_node << "\n";
		// _Tree._begin_node = &_Tree._end_node;
		//  --------------------- OR ------------------------------
		
			// iterator iter;
			// iter = first;
			// int i = 0;
			// while (iter != end)
			// {
			// 	std::cout << ++i << "\n";
			// 	erase(iter);
			// 	iter++;
			// }
			// std::cout << "AFTER deletion from begin to end\n";
			// _Tree.printTree();
	}

 // 7- clear
	void clear()
	{
		// if (empty())
		// {
		// 	//std::cout << "Can't clear anything the tree is empty\n";
		// }
		// else
			erase(begin(), end());
	}

// 	--------------------------------- 12- swap() ----------------------------------------
   	// void swap (vector& x);
	/*
		Exchanges the content of the container by the content of inst.
			which is another map of the same type.

		==> Notice that a non-member function exists with the same name,
		==> Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
	
		P.S:
			void swap( map& other );
Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.

	*/
	void swap(Map& inst) {

		//key_compare = inst.key_compare;

        //allocator_type = 
		
		// iterator it1;
		// iterator end_it1;
		// iterator it2;
		// iterator end_it2;

		// it1 = this->begin();
		// end_it1 = this->end();
		// it2 = inst.begin();
		// end_it2 = inst.end();

		// if (size() >= inst.size())
		// {
		// 	while (it2 != end_it2)
		// 		++it1 = ++it2;
		// 	while (it1 != end_it1)
		// 		++it2 = ++it1;
		// 	it1 = end_it2;
		// 	it2 = end_it1;

		// 	size_t _size = size();
		// 	_Tree->_size = inst.size();
		// 	inst->_Tree._size = _size;

		// }
		// else
		// {
		
		// }

	}
};

}

#endif