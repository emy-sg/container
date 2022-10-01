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
		typedef ::Node<value_type> Node;
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
	
		if (!_root)
		{
			std::cout << "NOT FOUND\n";
			return NULL;
		}
	    while (!tmp->is_null())
	    {
		    if ((tmp->value).first == key)
			    return tmp;
		    else
		    {
			    if ((tmp->value).first < key)
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
				std::cout << "     ________________NIL ";
				_NIL.printNode();
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

void	delete_leaf(Node* node) {
	// Node to be "deleted" has no children : i.e, it is a lead node
	Node* parent = node->parent;
	if (node->isLeft())
		parent->l_child = node->l_child;
	else
		parent->r_child = node->r_child;
	// destroy node
	delete node;
}

void delete_RBTree(const key_type& key)
{
	Node* node_to_delete = searchByKey(key);

	if (node_to_delete)
	{
				std::cout << "     ________________NIL ";
				_NIL.printNode();
		node_to_delete->printNode();
		deletion_RBTree(node_to_delete);

		std::cout << "     ________________NIL ";
				_NIL.printNode();
	}
	else
		 std::cout << "I'm null";
}
//void deletion_RBTree(Node& node_to_delete)
void deletion_RBTree(Node* node_to_delete)
{
	std::cout << "      ========== Node to delete is: ============== \n";
	node_to_delete->printNode();
	std::cout << "      ============================================\n";
	// Case 1:
	if (isRoot(node_to_delete) && node_to_delete->is_leaf())
		delete_leaf(node_to_delete);
	// Case 2:
	else if (node_to_delete->is_leaf() && node_to_delete->color == Red)
		delete_leaf(node_to_delete); // is Red leaf
	// Case 3:
	else if (node_to_delete->is_leaf() && node_to_delete->color == Black)
	{
		std::cout << "Black leaf\n";
		std::cout << "     ________________NIL ";
		_NIL.printNode();
		//node_to_delete->printNode();
		Node	*parent = node_to_delete->parent;// parent
		if (node_to_delete->isRight())
		{
			std::cout << "is Right\n";
			delete_leaf(node_to_delete);
			Node* new_node = new Node(); // is Black Null Node
			new_node->_is_null = 0;
			new_node->parent = parent;
			parent->r_child = new_node;
			new_node->l_child = &_NIL;
			new_node->r_child = &_NIL;
			new_node->color = DB; // enum {RED, Black, DB}
			fix_DB(new_node);
			delete_leaf(new_node);
		}
		else // isLeft()
		{
			std::cout << "is Left\n";
			delete_leaf(node_to_delete);
			Node* new_node = new Node();
			parent->l_child = new_node;
			new_node->_is_null = 0;
			new_node->parent = parent;
			new_node->l_child = &_NIL;
			new_node->r_child = &_NIL;
			new_node->color = DB;
			fix_DB(new_node);
			delete_leaf(new_node);
		}
	}
	// Case 4: Internal Node
	else
	{
		std::cout << "----Delete Internal node-----\n";
		// In this case of Internal Node, we don't delete the node:
		// 		==> Actually we replace the node.
		// Replace it with his InOrderSuccessor OR InOrderPredecessor
		//    and delete the actual node(node_to_delete)

		std::cout << "     ________________NIL ";
		_NIL.printNode();
		
		Node* node_replace;
	
		node_replace = choose_replacement_of_node(node_to_delete);
		std::cout << " ====> Replace node will be: \n";
		// node_replace->printNode();
		// node_to_delete->l_child->printNode();
		// node_to_delete->r_child->printNode();
		if (node_replace != node_to_delete->l_child && node_replace != node_to_delete->r_child)
		{
			std::cout << "choosing replacement node is not a child\n";
			node_to_delete->swap(node_replace);
			//exit(1);
		}
		else
		{
			std::cout << "special case when the replace node is the child of node\n";
			// exit(1);
			// Special case of : Swap node with one of his children
			if (node_to_delete->isLeft())
			{
				std::cout << "node to delete is left\n";
				(node_to_delete->parent)->l_child = node_replace;
				// swap with left child
				if (node_replace->isLeft())
				{
					std::cout << "node replace is left\n";
					//exit(1);
					node_replace->parent = node_to_delete->parent;
					Node* left_child = node_replace->l_child;
					Node* right_child = node_replace->r_child;

					// swap r_child of node to delete to node replace
					node_replace->r_child = node_to_delete->r_child;
					if (!(node_replace->r_child)->is_null())
						(node_replace->r_child)->parent = node_replace;
					// swap parent of node to delete to node replace
					node_replace->l_child = node_to_delete;
					node_to_delete->parent = node_replace;
					// give children of node_replace to the node to delete
					node_to_delete->l_child = left_child;
					node_to_delete->r_child = right_child;
				}
				// swap with right child
				else // node_replace is right
				{
					std::cout << "node replace is right\n";
					//exit(1);
					node_replace->parent = node_to_delete->parent;
					Node* left_child = node_replace->l_child;
					Node* right_child = node_replace->r_child;

					// swap r_child of node to delete to node replace
					node_replace->l_child = node_to_delete->l_child;
					if (!(node_replace->l_child)->is_null())
						(node_replace->l_child)->parent = node_replace;
					// swap parent of node to delete to node replace
					node_replace->r_child = node_to_delete;
					node_to_delete->parent = node_replace;
					// give children of node_replace to the node to delete
					node_to_delete->l_child = left_child;
					node_to_delete->r_child = right_child;				
				}
			}
			else
			{
				std::cout << "node to delete is right\n";
				(node_to_delete->parent)->r_child = node_replace;
					// swap with left child
				if (node_replace->isLeft())
				{
					std::cout << "node replace is left\n";
					// exit(1);
					node_replace->parent = node_to_delete->parent;
					Node* left_child = node_replace->l_child;
					Node* right_child = node_replace->r_child;

					// swap r_child of node to delete to node replace
					node_replace->r_child = node_to_delete->r_child;
					if (!(node_replace->r_child)->is_null())
						(node_replace->r_child)->parent = node_replace;
					// swap parent of node to delete to node replace
					node_replace->l_child = node_to_delete;
					node_to_delete->parent = node_replace;
					// give children of node_replace to the node to delete
					node_to_delete->l_child = left_child;
					node_to_delete->r_child = right_child;
					//exit(1);
				}
				// swap with right child
				else // node_replace is right
				{
					std::cout << "node replace is right\n";
					std::cout << "     ________________NIL ";
					_NIL.printNode();
					//exit(1);
					node_replace->parent = node_to_delete->parent;
					Node* left_child = node_replace->l_child;
					Node* right_child = node_replace->r_child;

					// swap r_child of node to delete to node replace
					node_replace->l_child = node_to_delete->l_child;
					if (!(node_replace->l_child)->is_null())
						(node_replace->l_child)->parent = node_replace;
					// swap parent of node to delete to node replace
					node_replace->r_child = node_to_delete;
					node_to_delete->parent = node_replace;
					// give children of node_replace to the node to delete
					node_to_delete->l_child = left_child;
					node_to_delete->r_child = right_child;
					std::cout << "     ________________NIL ";
					_NIL.printNode();		
				}					
			}




			/*// swap node with one of his children
			if ((node_to_delete->l_child)->is_null()) // internal node with one child
			{
				std::cout << "internal node with one child l_child\n";
				replace_node = node_to_delete->r_child;
				//node_to_delete->swap_node(replace_node);
				Node* pparent = node_to_delete->parent;
			if (node_to_delete->isLeft())
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
		else if ((node_to_delete->r_child)->is_null()) // internal node with one child
		{
			std::cout << "internal node with one child r_child\n";
			replace_node = node_to_delete->l_child;
			//node_to_delete->swap_node(replace_node);
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
		}	*/

/*		Node* replace_node;
		if ((node_to_delete->l_child)->is_null()) // internal node with one child
		{
			std::cout << "internal node with one child l_child\n";
			replace_node = node_to_delete->r_child;
			//node_to_delete->swap_node(replace_node);
			Node* pparent = node_to_delete->parent;
			if (node_to_delete->isLeft())
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
		else if ((node_to_delete->r_child)->is_null()) // internal node with one child
		{
			std::cout << "internal node with one child r_child\n";
			replace_node = node_to_delete->l_child;
			//node_to_delete->swap_node(replace_node);
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
		else // internal node with two children
*/		/*{
			std::cout << "internal node with two children\n";
			replace_node = choose_replacement_of_node(node_to_delete);
			std::cout << "Replace_node\n";
			replace_node->printNode();
			if (!(node_to_delete->l_child)->is_null())
			 	node_to_delete->swap1(replace_node);
			else if (!(node_to_delete->r_child)->is_null())
			 	node_to_delete->swap2(replace_node);
			else
				node_to_delete->swap_node(replace_node);
		}*/
		}
		Color color = node_replace->color;
		node_replace->color = node_to_delete->color;
		node_to_delete->color = color;
		// ==> After Rotation, Update the _root
		_root = _end_node.l_child;
		std::cout << "Recursive call for deletion_RBTree for this node:\n";
		node_to_delete->printNode();
		std::cout << "     ________________NIL ";
		_NIL.printNode();
		//this->printTree();
		//exit(1);
		deletion_RBTree(node_to_delete); // is leaf or one child those are the only cases
	}
}

Node* choose_replacement_of_node(Node* node_to_delete)
{
	// Replace the node to be deleted With RED node if possible
	// 	 [ InOrderSuccessor OR InOrderPredecessor ]
	Node* InOrderSuccessor = node_to_delete->inOrderSuccessor();
	Node* InOrderPredecessor = node_to_delete->inOrderPredecessor();

	//std::cout << "===> Successor:\n";
	//InOrderSuccessor->printNode();
	//std::cout << "===> Predecessor:\n";
	//InOrderPredecessor->printNode();
	if (InOrderSuccessor->is_null())
		return InOrderPredecessor;
	else if (InOrderPredecessor->is_null())
		return InOrderSuccessor;
	//else if (InOrderSuccessor->color == Red)
		return InOrderSuccessor;
	//return InOrderPredecessor;
}

void fix_DB(Node* DB_node)
{
	// Case 0:
	if (isRoot(DB_node))
		DB_node->color = Black;
	else
	{
		Node* sibling = DB_node->sibling();
		// Case 1: // sibling is Black and Both of this children are black
		if (sibling->color == Black && 
			(sibling->l_child)->color == Black &&
			(sibling->r_child)->color == Black)
			case_1Deletion(DB_node);
		// Case 2: // sibling is Red
		else if (sibling->color == Red)
			case_2Deletion(DB_node);
		// Case 3: // sibling is Red, Sibling's child far from DB is black, 
		//    Sibling's chilf near to DB in red
		else if (sibling->color == Black &&
			(DB_node->far_child_sibling())->color == Black &&
			(DB_node->near_child_sibling())->color == Red)
			case_3Deletion(DB_node);
		else // if (sibling.color == Black && (DB_node.far_child_sibling()).color == Red)
			case_4Deletion(DB_node);
	}
}

// Case 1: sibling is Black and Both of this children are black
void case_1Deletion(Node* DB_node) {
	//std::cout << "case_1Deletion\n";
	Node* sibling = DB_node->sibling();

	DB_node->color = Black;
	sibling->color = Red;
	if ((DB_node->parent)->color == Black)
	{
		(DB_node->parent)->color = DB;
		fix_DB(DB_node->parent);
	}
	else
		(DB_node->parent)->color = Black;
}

// Case 2: // sibling is Red
void case_2Deletion(Node* DB_node) {
	//std::cout << "case_2Deletion\n";
	std::cout << "     ________________NIL  case_ 2Deletion \n";
				_NIL.printNode();
	Node* sibling = DB_node->sibling();
	Node* parent = DB_node->parent;

	// Step 1: Swap DB's parent color with DB's sibling color
	parent->color = Red;
	sibling->color = Black;
	//	std::cout << "sibling ";
	//		sibling->printNode();
	//	std::cout << "parent ";
	//		parent->printNode();
	//this->printTree();
	//		std::cout << "RRRight child ";
	//		(((DB_node->sibling())->l_child)->r_child)->printNode();
	// Step 2: Perform Rotation at parent node in the direction of DB node
	if (DB_node->isLeft())
	{
				std::cout << "     ________________NIL Before rotation if \n";
				_NIL.printNode();
		parent->left_Rotation();
				std::cout << "     ________________NIL After rotation \n";
				_NIL.printNode();
		// ==> After Rotation, Update the _root
		_root = _end_node.l_child;
	}
	else
	{
				std::cout << "     ________________NIL Before rotation else \n";
				_NIL.printNode();
		parent->right_Rotation();
				std::cout << "     ________________NIL After rotation ";
				_NIL.printNode();
		// ==> After Rotation, Update the _root
		_root = _end_node.l_child;
	}
	//this->printTree();
	// Step 3: recursive
			//std::cout << "sibling ";
			//(DB_node->sibling())->printNode();
		//std::cout << "left child ";
		//	((DB_node->sibling())->l_child)->printNode();
		//std::cout << "right child ";
		//	((DB_node->sibling())->r_child)->printNode();
	fix_DB(DB_node);
}

// Case 3: // sibling is Red, Sibling's child far from DB is black, 
	//    Sibling's child near to DB in red
void	case_3Deletion(Node* DB_node)
{
	std::cout << "case_3Deletion\n";
	Node* sibling = DB_node->sibling();
	// Step 1: color sibling with Red, and red child sibling with black (swap color)
	sibling->color = Red;
	(DB_node->near_child_sibling())->color = Black;
	// Step 2: Perform Rotation at sibling node in direction opposite of DB node
	if (DB_node->isLeft())
	{
		sibling->right_Rotation();
		// ==> After Rotation, Update the _root
		_root = _end_node.l_child;
	}
	else
	{
		sibling->left_Rotation();
		// ==> After Rotation, Update the _root
		_root = _end_node.l_child;
	}
	// Step 3: Call the case 4
	case_4Deletion(DB_node);
}

// Case 4: // if (sibling.color == Black && (DB_node.far_child_sibling()).color == Red)
void case_4Deletion(Node* DB_node)
{
	std::cout << "case_4Deletion\n";
	//exit(1);
	Node* sibling = DB_node->sibling();
	Node* far_child_sibling = DB_node->far_child_sibling();
	//exit(1);
	Node* parent = DB_node->parent;
	// Step 1: Swap color of DB's parent with DB's sibling's color
	sibling->color = parent->color;
	parent->color = Black;
	// Step 2: Perform rotation at DB's parent in direction of DB
	if (DB_node->isLeft())
	{
		parent->left_Rotation();
		//exit(1);
		// ==> After Rotation, Update the _root
		_root = _end_node.l_child;
	}
	else
	{
		parent->right_Rotation();
		//exit(1);
		// ==> After Rotation, Update the _root
		_root = _end_node.l_child;
	}
	//exit(1);
	// Step 3: Remove DB sign
	DB_node->color = Black;
	// Step 4: Change color of DB's sibling far child from Red to Black
	std::cout << "siri na3si\n";
	far_child_sibling->color = Black;
	//exit(1);
}

};


#endif