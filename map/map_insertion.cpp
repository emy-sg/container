#include <iostream>
#include "node.hpp"

// Member methods of RBTree
// All are a template methods

// pair<iterator, bool> insert (const value_type& val);

// iterator insert (iterator position, const value_type& val);

// template <class InputIterator>
// void insert (InputIterator first, InputIterator last);

//	----------------------------------

std::pair<iterator, bool> insert_RBT(const value_type& val) {
	iterator if_exist = find(val->first);
	if (if_exist != iter_end)
		return <if_exist, false>;
	else
	{
		Node* new_node;
		// Create (alloc and construct a new node)
		new_node = create_node(val); // 
		// update end and begin of Tree
		insert_BST(this->root, new_node);
		balancing_insertion(new_node);
		return pair<new_node, true>;
	}
}

void	insertion_BST(Node* parent, Node* curr, Node* new_node) {
	// Just answer the new Node, no need to do anything else
	if (!curr.is_null())
	{
		if (parent->value > new_node->value)
		{
			parent->l_child = new_node;
			new_node->parent = parent;
		}
		else
		{
			parent->r_child = new_node;
			new_node->parent = parent;
		}
	}
	else {
		if (curr->value > new_node->value)
			insert_BST(curr, node->left, new_node);
		else
			insert_BST(curr, node->right, new_node);
	}
}

void	balancing_insertion(Node* new_node) {
	Node* parent = new_node->parent;

	// Case 1:
	if (isRoot(new_node))
	{
		new_node.color = Black;
		return ;
	}	
	// Case 2:
	if (parent.color == Black)
		return ;
	// Case 3:
	else { // if(parent.color == Red)
		
		Node* uncle = sibling(parent);    // Maybe uncle could be NIL
		Node* grandParent = parent->parent;

		// Case 3.1:
		if (uncle.color == Red) // Parent && Uncle are Red
		{
			parent.color = Black;
			uncle.color = Black;
			grandParent.color = Red;
			balancing_insertion(grandParent);
		}
		// Case 3.2:
		else // Parent is Red && Uncle is Black and Maybe in this Case Uncle is NIL
		{
			if (parent.isRight() && new_node.isRight())
				case_1Insertion(grandParent);
			else if (parent.isRight() && new_node.isLeft()) {
				right_rotation(parent);
				// new_node become the parent of Parent
				// call case 3.2.1
				case_1Insertion(grandParent);
			}
			else if (parent.isLeft() && new_node.isLeft())
				case_2Insertion(grandParent);
			// if (parent.isLeft() && new_node.isRight())
			else {
				// So with rotation parent will go down and new_node will go up 
				left_rotation(parent);
				// new_node become the parent of Parent
				// call case 3.2.2
				case_2Insertion(grandParent);
			}
		}
	}
	
}

void case_1Insertion(Node* grandParent) {
	left_Rotation(grandParent);
	// grandParent is sibling now
	// Recoloring
	grandParent.color = Red;
	(grandParent.sibling()).color = Red;
	(grandParent->parent).color = Black;
}

void	case_2Insertion(Node* grandParent) {
	right_Rotation(grandParent);
	// grandparent is sibling now
	// Recoloring
	grandParent.color = Red;
	(grandParent.sibling()).color = Red;
	(grandParent->parent).color = Black;
}
	--------------------------------------------------



