# ifndef RBTREE_HPP
#define RBTREE_HPP

#include "node.hpp"
//#in

/* Red-Black Tree is a self-balanced Binary Tree */
// Search and Insert and Remove this operation in O log(n) time complexity

template <class value_type>
class Tree {
    public:
        Node* root;
		Node end_node;
		size_t size;
    
    // Constructor
    Tree() : root() { 
		std::cout << "Default Tree constructor\n";
	}

	~Tree() {
		std::cout << "Tree Destructor\n";
	}

    // Methods

    bool isRoot(Node* node) {
	    if (node == root)
		    return true;
	        return false;
    }

    Node*	searchByKey(const key_type& key) {
	    Node* tmp = root;
	
	    while (!tmp.is_null())
	    {
		    if ((tmp.value_type)->first == key)
			    return tmp;
		    else
		    {
			    if ((tmp.value_type)->first < key)
				    tmp = tmp->r_child;
			    else
				    tmp = tmp->l_child;
		    }
	    }
	    return NULL;
    }

        ////////////////////////////////////
        //          Insertion             //
        ////////////////////////////////////

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

        ////////////////////////////////////
        //        Deletion                //
        ///////////////////////////////////

    Node* choose_the_replacement_node(Node* node)
{
	// Replace the node to be deleted With RED node if possible
	// 	 [ InOrderSuccessor OR InOrderPredecessor ]
	Node* InOrderSuccessor = node_to_delete.inOrderSuccessor();
	Node* InOrderPredecessor = node_to_delete.inOrderPredeccessor();

	if (InOrderSuccessor.is_null())
		return InOrderPredecessor;
	else if (InOrderPredecessor.is_null())
		return InOrderSuccessor;
	else if (InOrderPredecessor.color == Red)
		return InOrderPredecessor;
	return InOrderSuccessor;
}

// Case 1: sibling is Black and Both of this children are black
void case_1Deletion(Node* DB_node) {
	Node* sibling = DB_node.sibling();

	DB_node.color = Black;
	sibling.color = Red;
	if ((DB_node->parent).color == Black)
	{
		(DB_node->parent).color = DB;
		fix_DB(DB_node->parent);
	}
	else
		(DB_node->parent).color = Black;
}

// Case 2: // sibling is Red
void case_2Deletion(Node* DB_node) {
	Node* sibling = DB_node.sibling();
	Node* parent = DB_node->parent;
	// Step 1: Swap DB's parent color with DB's sibling color
	parent.color = Red;
	sibling.color = Black;
	// Step 2: Perform Rotation at parent node in the direction of DB node
	if (DB_node.is_left())
		left_Rotation(parent);
	else
		right_Rotation(parent);
	// Step 3: recursive
	fix_DB(DB_node);
}

// Case 3: // sibling is Red, Sibling's child far from DB is black, 
	//    Sibling's child near to DB in red
void	case_3Deletion(Node* DB_node)
{
	Node* sibling = DB_node.sibling();
	// Step 1: color sibling with Red, and red child sibling with black (swap color)
	sibling.color = Red;
	(DB_node.near_child_sibling()).color = Black;
	// Step 2: Perform Rotation at sibling node in direction opposite of DB node
	if (DB_node.is_left())
		sibling.right_Rotation();
	else
		sibling.left_Rotation();
	// Step 3: Call the case 4
	case_4Deletion(DB_node);
}

// Case 4: // if (sibling.color == Black && (DB_node.far_child_sibling()).color == Red)
void case_4Deletion(Node* DB_node)
{
	Node* sibling = DB_node.sibling();
	Node* far_child_sibling = DB_node.far_child_sibling();
	Node* parent = DB_node->parent;
	// Step 1: Swap color of DB's parent with DB's sibling's color
	sibling.color = parent.color;
	parent.color = Black;
	// Step 2: Perform rotation at DB's parent in direction of DB
	if (DB_node.is_left())
		parent.left_Rotation();
	else
		parent.right_Rotation();
	// Step 3: Remove DB sign
	DB_node.color = Black;
	// Step 4: Change color of DB's sibling far child from Red to Black
	far_child_sibling.color = Black;
}

};


#endif