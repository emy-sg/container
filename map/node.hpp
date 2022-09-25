# ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

enum Color {
    Red,
    Black,
    DB
};

template <class value_type>
class Node {
    public:
        int _is_null;  // 0 is null and 1 is !null
        value_type value;
        Color color;

        Node* parent;
        Node* l_child;
        Node* r_child;

    public:
        // Constructor
        Node() {
        	_is_null = 0;  // 0 is null and 1 is !null
			color = Black;
		}
        Node(value_type value) : value(value) {
			_is_null = 1;
			//std::cout << "Parameterized Node Constructor\n";
		}
        Node(const Node& inst) {
			*this = inst;
		}
        Node& operator=(const Node& inst) {
			_is_null = inst._is_null;
			value = inst.value;
			color = inst.color;
			parent = inst->parent;
			l_child = inst->l_child;
			r_child = inst->r_child;
		}
        ~Node() {}

    // -------------  Methods  ------------ //

        /////////////////////////////////
        //      Check position of Node //
        /////////////////////////////////

	void printNode() {
		if (is_null())
			std::cout << "is_null: yes | ";
		else
			std::cout << "is_null: no | ";
		if (color == Red)
			std::cout << "color: Red | ";
		else
		 	std::cout << "color: Black | ";
		if (isLeft())
			std::cout << "is_Left: yes | ";
		else
		 	std::cout << "is_right: yes | ";
		std::cout <<  " value: " << value.first << " | parent value: " << parent->value.first << "\n";
	}

    bool is_null() {
	    if (this->_is_null == 0)
		    return true;
	    return false;
    }
    
    bool isRight() {
	    Node* parent = this->parent;
	    if (parent->r_child == this)
		    return true;
	    return false;
    }

    bool isLeft() {
	    Node* parent = this->parent;
	    if ((parent->l_child) == this)
		    return true;
	    return false;
    }

    bool is_leaf() {
	    if ((this->l_child).is_null && (this->r_child).is_null)
		    return true;
	    return false;
    }

    Node* sibling() {
	    Node* parent = this->parent;
	    if ((*this).isLeft())
		    return parent->r_child;
	    return parent->l_child;
    }

    Node* far_child_sibling() {
	    Node* node = this;
	    Node* sibling = node->sibling();
	    if (node->isLeft())
		    return sibling->r_child;
	    return sibling->l_child;
    }

    Node* near_child_sibling() {
	    Node* node = this;
	    Node* sibling = node->sibling();
	    if (node->isLeft())
		    return sibling->l_child;
	    return sibling->r_child;
    }

        ////////////////////////////////////
        //     Successor and Predecessor  //
        ////////////////////////////////////

    Node* inOrderSuccessor() {
	    // What is node's Successor in a BST ?
	    // ==> It is the Smallest value present in its right subtree.
	    Node* right_child = this->r_child;
	    // getMinimumkey of right child
	    return getMinimumKey(right_child);
    }

    Node* getMinimumKey(Node* curr) {
	    while (!(curr->l_child).is_null)
		    curr = curr->l_child;
	    return curr;
    }

    Node* inOrderPredecessor() {
	    // What is node's Predecessor in a BST ?
	    // ==> It is the Greatest value in its left subtree.
	    Node* left_child = this->l_child;
	    // getMaximumkey of left child
	    return getMaximumKey(left_child);
    }

    Node* getMaximumKey(Node* curr) {
	    while (!(curr->r_child).is_null)
		    curr = curr->r_child;
	    return curr;
    }

        /////////////////////////////////
        //           Rotation          //
        /////////////////////////////////

    void left_Rotation() {
		Node* node = this;
	    Node* parent = node->parent;
	    Node* right_child = node->r_child;

	    if (node->isRight())
		    parent->r_child = right_child;
	    else
		    parent->l_child = right_child;
		//parent->printNode();
	    node->parent = right_child;
	    node->r_child = right_child->l_child;
		if (!(node->r_child)->is_null()) // is not NIL
			(node->r_child)->parent = node;
	    right_child->l_child = node;
		right_child->parent = parent;
		right_child->printNode();
    }

    void right_Rotation() {
		Node* node = this;
	    Node* parent = node->parent;
	    Node* left_child = node->l_child;

	    if (node->isRight())
		    parent->r_child = left_child;
	    else
		    parent->l_child = left_child;
	    node->parent = left_child;
	    node->l_child = left_child->r_child;
		if (!(node->l_child)->is_null()) // is not NIL
			(node->l_child)->parent = node;
	    left_child->r_child = node;
		left_child->parent = parent;
    }

        ///////////////////////////////////
        //   Swap position of two nodes  //
        ///////////////////////////////////

    void	swap_node(Node* replacement_node) {
	    Node* pparent = replacement_node->parent;	
	    replacement_node->parent = this->parent;
	    this->parent = pparent;;
		// Change right with right:
	    Node* rr_child = replacement_node->r_child;
	    replacement_node->r_child = this->r_child;
	    this->r_child = rr_child;;
		// Change left with left
        Node*  ll_child = replacement_node->l_child;
	    replacement_node->l_child = this->l_child;
	    this->l_child = ll_child;
    }


};

#endif