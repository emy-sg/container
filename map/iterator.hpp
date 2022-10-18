# ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "../iterator_traits.hpp"
#include "node.hpp"
#include <utility>

namespace ft {

template <class Tree, class value_type> // value_type is std::pair
class Iterator_map {
    public:
        //typedef typename ft::iterator_traits<T*>::value_type value_type;
        typedef ::Node<value_type> Node;
        typedef typename ft::iterator_traits<value_type*>::pointer pointer; // operator ->()
        typedef typename ft::iterator_traits<value_type*>::reference reference; // operator*()

    public:
        Tree* _Tree;
        Node* _Node;

    public:
        // Constructor
        Iterator_map() {
            //std::cout << "Default iterator\n";
            _Tree = NULL;
            //_Node = NULL;
        }
        Iterator_map(Tree* tree, value_type val) { //Initalization constructor
            //std::cout << "Parameterized Iterator Constructor\n";
            _Tree = tree;
            //std::cout << "Wach had l iterator 5adam awla la rah darni f rassi\n";
            // if (val == _Tree->get_begin()->value)
            //     _Node = tree->get_begin();
            // else
            //     _Node = tree->get_end();

            _Node = _Tree->searchByKey(val.first); // optimization
            if (!_Node)
                _Node = tree->get_end();
            // else
            // {
            //     std::cout << "affichhi had node ali 3titek f iterator\n";
            //     _Node->printNode();
            // }
            // std::cout << "Normalement 5asou yaffichi node 9banma ya5roj\n";
        }
        Iterator_map(const Iterator_map& iter) {
            //std::cout << "Copy Constructor iterator\n";
            *this = iter;
        }
        Iterator_map& operator=(const Iterator_map& iter) {
            //std::cout << "Assignement Copy Constructor iterator\n";
            this->_Tree = iter._Tree;
            this->_Node = iter._Node;
            //std::cout << _Node << " " << iter._Node << "\n";
            // if (_Node != _Tree->get_end())
            //     _Node->printNode();
            //std::cout << "walo\n";
            return *this;
        }
        ~Iterator_map() {
            //std::cout << "Destructor iterator\n";
        }

    // --------------------------------------------

    // 1- operator->() return pointer to value_type aka pointer to std::pair
    pointer operator->() {
        //std::cout << "KIfach not found\n";
        return &_Node->value;  /// T5arbi9a zatha
            // bcuz I don't know if value or *value in NOde class
    }

    // 2- operator*() return reference to value_type aka reference to std::pair
    reference operator*() const {
        return _Node->value;
    }

    // Step 3: Member Methods increment/decrement : operator++() && operator--()
    
    // 1- Prefix increment:
    Iterator_map& operator++() {
        //std::cout << "\n ------------ Pre increment ----------------- \n";
        _Node = _Tree->next_node(_Node);
        return *this;
    }
    // 2- Prefix decrement:
    Iterator_map& operator--() {
        //std::cout << "\n ------------ Pre idecrement ----------------- \n";
        _Node = _Tree->previous_node(_Node);
        return *this;
    }
    // 3- Postfix increment
    Iterator_map operator++(int) {
        //std::cout << "\n ------------ Post increment ----------------- \n";
        Iterator_map tmp = *this; // create a copy
        //std::cout << tmp->first << "\n";
        ++(*this); // ++(*this); // call pre increment for *this
        //std::cout << tmp->first << "\n";
        return tmp;
    }
    // 4- Postfix decrement
    Iterator_map operator--(int) {
        Iterator_map tmp(*this); // create a copy
        --(*this); // ==>   --(*this); 
        return tmp;
    }

    // Step 4: Member friends : The operators [== != ]
    friend bool operator==(const Iterator_map& a, const Iterator_map& b) {
        return a._Node->value == b._Node->value;
    }

    friend bool operator!=(const Iterator_map& a, const Iterator_map& b) {
        return a._Node->value != b._Node->value;
    }
};
}

#endif