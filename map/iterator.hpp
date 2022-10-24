# ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "../iterator_traits.hpp"
#include "node.hpp"
#include <iterator>
#include <utility>

namespace ft {

template <class T> // value_type is std::pair
class Iterator {
    public:
        // typedef ::Node<T> Node;

            typedef ptrdiff_t                                        difference_type;
            typedef T                                                value_type;
            typedef T*                                                pointer;
            typedef T&                                                reference;
            typedef std::bidirectional_iterator_tag                    iterator_category;
            typedef typename ::Node<value_type>                         Node;
            typedef typename ::Node<const typename iterator_traits<value_type*>::value_type>    const_node;

    private:
        Node* _end_node;
        Node* _Node;

    public:
        // Constructor
        Iterator() {
            //std::cout << "Default iterator\n";
            _end_node = NULL;
            _Node = NULL;
        }
        Iterator(Node* end_node, Node* curr) { //Initalization constructor
            //std::cout << "Parameterized Iterator Constructor\n";
            _end_node = end_node;
            _Node = curr;
            // else
            // {
            //     std::cout << "affichhi had node ali 3titek f iterator\n";
            //     _Node->printNode();
            // }
            // std::cout << "Normalement 5asou yaffichi node 9banma ya5roj\n";
        }
        template< class IT>
        Iterator(const Iterator<IT>& iter) {
            //std::cout << "Copy Constructor iterator\n";
            *this = iter;
            // _end_node = iter._end_node;
            // _Node = iter._Node;
        }
        template< class IT>
        Iterator& operator=(const Iterator<IT>& iter) {
            //std::cout << "Assignement Copy Constructor iterator\n";
            this->_end_node = (Node*) iter.base().first;
            this->_Node = (Node*) iter.base().second;
            //std::cout << _Node << " " << iter._Node << "\n";
            // if (_Node != _Tree->get_end())
            //     _Node->printNode();
            //std::cout << "walo\n";
            return *this;
        }
        ~Iterator() {
            //std::cout << "Destructor iterator\n";
        }

    // --------------------------------------------

    // operator Iterator() {
    //     return Iterator((Node*) base().first, (Node*) base().second);
    // }

    std::pair<Node*, Node*> base() const {
        return std::make_pair(_end_node, _Node);
    }

    // 1- operator->() return pointer to value_type aka pointer to std::pair

    //pointer operator->() const;
    pointer operator->() const {
        return &((Node*)_Node)->value;
            // bcuz I don't know if value or *value in NOde class
    }

    // 2- operator*() return reference to value_type aka reference to std::pair
    
    // reference operator*() const;
    reference operator*() const {
        return _Node->value;
    }

    // Step 3: Member Methods increment/decrement : operator++() && operator--()
    
    // 1- Prefix increment:
    Iterator& operator++() {
        //std::cout << "\n ------------ Pre increment ----------------- \n";
        _Node = _Node->next_node(_end_node);
        return *this;
    }
    // 2- Prefix decrement:
    Iterator& operator--() {
        //std::cout << "\n ------------ Pre idecrement ----------------- \n";
        _Node = _Node->previous_node(_end_node);
        return *this;
    }
    // 3- Postfix increment
    Iterator operator++(int) {
        //std::cout << "\n ------------ Post increment ----------------- \n";
        Iterator tmp = *this; // create a copy
        //std::cout << tmp->first << "\n";
        ++(*this); // ++(*this); // call pre increment for *this
        //std::cout << tmp->first << "\n";
        return tmp;
    }
    // 4- Postfix decrement
    Iterator operator--(int) {
        Iterator tmp(*this); // create a copy
        --(*this); // ==>   --(*this); 
        return tmp;
    }

    // Step 4: Member friends : The operators [== != ]
    friend bool operator==(const Iterator& a, const Iterator& b) {
        return a._Node->value == b._Node->value;
    }

    friend bool operator!=(const Iterator& a, const Iterator& b) {
        // compare end_node deleted;
        return a._Node->value != b._Node->value;
    }
};
}

#endif