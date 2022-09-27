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
		std::cout << " value: " << value.first << " | parent value: " << parent->value.first;
		if (!(this->l_child)->is_null())
			std::cout << " | l_child value: " << (this->l_child)->value.first;
		else
		 	std::cout << " | l_child value: is NIL";
		if (!(this->r_child)->is_null())
			std::cout << " | r_child value: " << (this->r_child)->value.first;
		else
		 	std::cout << " | r_child value: is NIL";
		std::cout << std::endl;
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
	    if ((this->l_child)->is_null() && (this->r_child)->is_null())
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
		if (right_child->is_null())
			return this;
	    return getMinimumKey(right_child);
    }

    Node* getMinimumKey(Node* curr) {
	    while (!(curr->l_child)->is_null())
		    curr = curr->l_child;
	    return curr;
    }

    Node* inOrderPredecessor() {
	    // What is node's Predecessor in a BST ?
	    // ==> It is the Greatest value in its left subtree.
	    Node* left_child = this->l_child;
	    // getMaximumkey of left child
		if (left_child->is_null())
			return this;
	    return getMaximumKey(left_child);
    }

    Node* getMaximumKey(Node* curr) {
	    while (!(curr->r_child)->is_null())
		    curr = curr->r_child;
	    return curr;
    }

        /////////////////////////////////
        //           Rotation          //
        /////////////////////////////////

    void left_Rotation() {
		//std::cout << "begin left_Rotation\n";
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
		//right_child->printNode();
		//std::cout << "end left_Rotation\n";
    }

    void right_Rotation() {
		//std::cout << "begin right_Rotation\n";
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
		//std::cout << "end right_Rotation\n";
    }

        ///////////////////////////////////
        //   Swap position of two nodes  //
        ///////////////////////////////////

    // void	swap_node(Node* replacement_node) {
	// 	std::cout << "begin swap_node\n";
	//     Node* pparent = replacement_node->parent;	
	//     replacement_node->parent = this->parent;
	//     this->parent = pparent;;
	// 	// Change right with right:
	//     Node* rr_child = replacement_node->r_child;
	//     replacement_node->r_child = this->r_child;
	//     this->r_child = rr_child;;
	// 	// Change left with left
    //     Node*  ll_child = replacement_node->l_child;
	//     replacement_node->l_child = this->l_child;
	//     this->l_child = ll_child;
	// 	std::cout << "end swap_node\n";
    // }

	void swap(Node* replace_node) {
		std::cout << "SWAP fct\n";
		this->printNode();
		replace_node->printNode();
		Node* this_parent = this->parent;
		Node* replace_parent = replace_node->parent;
		Node* left_child = replace_node->l_child;
		Node* right_child = replace_node->r_child;
		Color color = replace_node->color;

		// We discuss here some cases 
		if (this->isLeft())
			this_parent->l_child = replace_node;
		else
			this_parent->r_child = replace_node;
		if (replace_node->isLeft())
			replace_parent->l_child = this;
		else
		 	replace_parent->r_child = this;
		
		// 1- switch parent
		this->parent = replace_parent;
		replace_node->parent = this_parent;
		// 3- switch children 
		replace_node->l_child = this->l_child;
		replace_node->r_child = this->r_child;
		this->l_child = left_child;
		this->r_child = right_child;
		// 4- switch colors
		replace_node->color = this->color;
		this->color = color;
	}


	void swap1(Node* replace_node) {
			Node* pparent = this->parent;
			if (this->isLeft())
				pparent->l_child = replace_node;
			else
				pparent->r_child = replace_node;
			replace_node->parent = pparent;
			replace_node->r_child = node_to_delete;
			node_to_delete->parent = replace_node;
			node_to_delete->r_child = &_NIL;
			replace_node->printNode();
			node_to_delete->printNode();
			Color color = replace_node->color;
			replace_node->color = node_to_delete->color;
			node_to_delete->color = color;
	}

	void swap2(Node* replace_node) {
			Node* pparent = node_to_delete->parent;
			if (node_to_delete->isLeft())
				pparent->l_child = replace_node;
			else
				pparent->r_child = replace_node;
			replace_node->parent = pparent;
			replace_node->l_child = node_to_delete;
			node_to_delete->parent = replace_node;
			node_to_delete->l_child = &_NIL;
			replace_node->printNode();
			node_to_delete->printNode();
			Color color = replace_node->color;
			replace_node->color = node_to_delete->color;
			node_to_delete->color = color;
	}

};


#endif