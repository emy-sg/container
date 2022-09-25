# ifndef RBTREE_HPP
#define RBTREE_HPP

#include "node.hpp"
//#in

/* Red-Black Tree is a self-balanced Binary Tree */
// Search and Insert and Remove this operation in O log(n) time complexity

//template <class value_type, class key_type, class mapped_value, class Alloc>
template <class key_type, class mapped_value>
class Tree {
	public:
		typedef std::pair<key_type, mapped_value> value_type;
    private:
		typedef Node<value_type> Node;
		size_t _size;
		Node _end_node;
		Node* _begin_node;
		Node _NIL;

	private:    
		// We suppose that: root = end_node->left_child
		Node* _root;
    
	public:
    // Constructor
    Tree() { 
		//std::cout << "Default Tree constructor\n";
		_size = 0;
		_begin_node = &_end_node;
	}

	~Tree() {
		//std::cout << "Tree Destructor\n";
		// if (_size > 0)
		// 	//delete all
	}

	void printHelper(Node *root, std::string indent, bool last) {
    if (root != &_NIL) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "   ";
      } else {
        std::cout << "L----";
        indent += "|  ";
      }

      std::string sColor = root->color == Red ? "RED" : "BLACK";
      std::cout << root->value.first << "(" << sColor << ")" << std::endl;
      printHelper(root->l_child, indent, false);
      printHelper(root->r_child, indent, true);
    }
  }
  void printTree() {
    if (_root) {
      printHelper(this->_root, "", true);
    }
  }

    // Methods

    bool isRoot(Node* node) {
	    if (node == _root)
		    return true;
	    return false;
    }

    Node*	searchByKey(const key_type& key) {
	    Node* tmp = _root;
	
	    while (!tmp->is_null())
	    {
		    if ((tmp->value_type)->first == key)
			    return tmp;
		    else
		    {
			    if ((tmp->value_type)->first < key)
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

void	insertion_BST(Node* parent, Node* curr, Node* new_node) {
	// Just answer the new Node, no need to do anything else
	if (curr->is_null())
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
	else
	{
		if (curr->value > new_node->value)
			insertion_BST(curr, curr->l_child, new_node);
		else
			insertion_BST(curr, curr->r_child, new_node);
	}
}

Node* insertion_RBTree(const value_type& val) {

	Node* new_node;

	try {
		// 1- Create (alloc and construct a new node)
		//new_node = create_node(val);
		new_node = new Node(val);
		new_node->color = Red;
		new_node->l_child = &_NIL;
		new_node->r_child = &_NIL;
		new_node->_is_null = 1;

		//new_node->printNode();
		// 2- increment the size of the container
		_size++;
		// 3- Insert in the Tree
		if (_root == NULL) 		// case 1: Empty Tree
		{
			//std::cout << "Empty Tree\n";

			_root = new_node;
			_root->parent = &_end_node;
			_end_node.l_child = _root;

			// 4- Update begin of Tree
			_begin_node = new_node;
		}
		else 				// case 2: Recursive
		{
			insertion_BST(_root, _root, new_node);
			// 4- Update begin of Tree
			if (val < _begin_node->value)
				_begin_node = new_node;
		}
		// 5- Balance the RedBlack Tree
		balancing_insertion(new_node); // new_node is not a "NIL node"
		return new_node;
	}
	catch (...) {
		std::cout << "ERROR insertion\n";
	}
	return new_node;

}

void	balancing_insertion(Node* new_node) {
	Node* parent = new_node->parent;

	// Case 1:
	if (isRoot(new_node))
	{
		new_node->color = Black;
		return ;
	}	
	// Case 2:
	if (parent->color == Black)
		return ;
	// Case 3:
	else { // if(parent.color == Red)
		
		Node* uncle = parent->sibling();    // Maybe uncle could be NIL
		Node* grandParent = parent->parent;

		// Case 3.1:
		if (uncle->color == Red) // Parent && Uncle are Red
		{
			parent->color = Black;
			uncle->color = Black;
			grandParent->color = Red;
			balancing_insertion(grandParent);
		}
		// Case 3.2:
		else // Parent is Red && Uncle is Black and Maybe in this Case Uncle is NIL
		{
			if (parent->isRight() && new_node->isRight())
				case_1Insertion(grandParent);
			else if (parent->isRight() && new_node->isLeft()) {
				parent->right_Rotation();
				// 1- After Rotation, Update the _root
				_root = _end_node.l_child;
				// new_node become the parent of Parent
				// 2- call case 3.2.1
				case_1Insertion(grandParent);
			}
			else if (parent->isLeft() && new_node->isLeft())
				case_2Insertion(grandParent);
			// if (parent.isLeft() && new_node.isRight())
			else {
				// So with rotation parent will go down and new_node will go up 
				parent->left_Rotation();
				// 1- After Rotation, Update the _root
				_root = _end_node.l_child;
				// new_node become the parent of Parent
				// 2- call case 3.2.2
				case_2Insertion(grandParent);
			}
		}
	}
	
}

void case_1Insertion(Node* grandParent) {
	grandParent->left_Rotation();
	// 1- After Rotation, Update the _root
	_root = _end_node.l_child;
	// grandParent is sibling now
	// 2- Recoloring
	grandParent->color = Red;
	(grandParent->sibling())->color = Red;
	(grandParent->parent)->color = Black;
}

void	case_2Insertion(Node* grandParent) {
	grandParent->right_Rotation();
	// 1- After Rotation, Update the _root
	_root = _end_node.l_child;
	// grandparent is sibling now
	// 2- Recoloring
	grandParent->color = Red;
	(grandParent->sibling())->color = Red;
	(grandParent->parent)->color = Black;
}

        ////////////////////////////////////
        //        Deletion                //
        ///////////////////////////////////




// Node* choose_the_replacement_node(Node* node)
// {
// 	// Replace the node to be deleted With RED node if possible
// 	// 	 [ InOrderSuccessor OR InOrderPredecessor ]
// 	Node* InOrderSuccessor = node_to_delete.inOrderSuccessor();
// 	Node* InOrderPredecessor = node_to_delete.inOrderPredeccessor();

// 	if (InOrderSuccessor.is_null())
// 		return InOrderPredecessor;
// 	else if (InOrderPredecessor.is_null())
// 		return InOrderSuccessor;
// 	else if (InOrderPredecessor.color == Red)
// 		return InOrderPredecessor;
// 	return InOrderSuccessor;
// }

// // Case 1: sibling is Black and Both of this children are black
// void case_1Deletion(Node* DB_node) {
// 	Node* sibling = DB_node.sibling();

// 	DB_node.color = Black;
// 	sibling.color = Red;
// 	if ((DB_node->parent).color == Black)
// 	{
// 		(DB_node->parent).color = DB;
// 		fix_DB(DB_node->parent);
// 	}
// 	else
// 		(DB_node->parent).color = Black;
// }

// // Case 2: // sibling is Red
// void case_2Deletion(Node* DB_node) {
// 	Node* sibling = DB_node.sibling();
// 	Node* parent = DB_node->parent;
// 	// Step 1: Swap DB's parent color with DB's sibling color
// 	parent.color = Red;
// 	sibling.color = Black;
// 	// Step 2: Perform Rotation at parent node in the direction of DB node
// 	if (DB_node.is_left())
// 		left_Rotation(parent);
// 	else
// 		right_Rotation(parent);
// 	// Step 3: recursive
// 	fix_DB(DB_node);
// }

// // Case 3: // sibling is Red, Sibling's child far from DB is black, 
// 	//    Sibling's child near to DB in red
// void	case_3Deletion(Node* DB_node)
// {
// 	Node* sibling = DB_node.sibling();
// 	// Step 1: color sibling with Red, and red child sibling with black (swap color)
// 	sibling.color = Red;
// 	(DB_node.near_child_sibling()).color = Black;
// 	// Step 2: Perform Rotation at sibling node in direction opposite of DB node
// 	if (DB_node.is_left())
// 		sibling.right_Rotation();
// 	else
// 		sibling.left_Rotation();
// 	// Step 3: Call the case 4
// 	case_4Deletion(DB_node);
// }

// // Case 4: // if (sibling.color == Black && (DB_node.far_child_sibling()).color == Red)
// void case_4Deletion(Node* DB_node)
// {
// 	Node* sibling = DB_node.sibling();
// 	Node* far_child_sibling = DB_node.far_child_sibling();
// 	Node* parent = DB_node->parent;
// 	// Step 1: Swap color of DB's parent with DB's sibling's color
// 	sibling.color = parent.color;
// 	parent.color = Black;
// 	// Step 2: Perform rotation at DB's parent in direction of DB
// 	if (DB_node.is_left())
// 		parent.left_Rotation();
// 	else
// 		parent.right_Rotation();
// 	// Step 3: Remove DB sign
// 	DB_node.color = Black;
// 	// Step 4: Change color of DB's sibling far child from Red to Black
// 	far_child_sibling.color = Black;
// }

};


#endif