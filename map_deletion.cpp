// Ressource:
/*
	https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea

	https://www.youtube.com/watch?v=w5cvkTXY0vQ&t=474s&ab_channel=Jenny%27slecturesCS%2FITNET%26JRF
*/

void	delete_leaf(Node node) {
	// Node to be "deleted" has no children : i.e, it is a lead node
	Node* parent = node->parent;
	if (node.isLeft())
		parent->l_child = node->l_child;
	else
		parent->r_child = node->r_child;
	// destroy node
	delete node;
}

void delete_node(Node& node_to_delete)
{
	// Case 1:
	if (isRoot(node_to_delete) && node_to_delete.is_leaf())
		delete_leaf(node_to_delete);
	// Case 2:
	else if (node_to_delete.is_leaf() && node_to_delete.color == Red)
		delete_leaf(node_to_delete); // is Red leaf
	// Case 3:
	else if (node_to_delete.is_leaf() && node_to_delete.color == Black)
	{
		Node	*parent = node_to_delete->parent;// parent
		if (node_to_delete.isRight())
		{
			delete_leaf(node_to_delete);
			Node *new_node = parent->r_child; // is Black Null Node
			new_node.color = DB; // enum {RED, Black, DB}
			fix_DB(new_node);
		}
		else // isLeft()
		{
			delete_leaf(node_to_delete);
			Node *new_node = parent->l_child;
			new_node.color = DB;
			fix_DB(new_node);
		}
	}
	// Case 4: Internal Node
	else
	{
		// In this case of Internal Node, we don't delete the node:
		// 		==> Actually we replace the node.
		// Replace it with his InOrderSuccessor OR InOrderPredecessor
		//    and delete the actual node(node_to_delete)

		node_to_delete.swap_node(choose_replacement_node(node_to_delete));
		delete_node(node_to_delete); // is leaf or one child those are the only cases
	}
}

	//	--------------------------------------------

void fix_DB(Node& DB_node)
{
	// Case 0:
	if (isroot(DB_node))
		DB_node.color = Black;
	else
	{
		Node* sibling = DB_node.sibling();
		// Case 1: // sibling is Black and Both of this children are black
		if (sibling.color == Black && 
			(sibling->l_child).color == Black &&
			(sibling->r_child).color == Black)
			case_1Deletion(DB_node);
		// Case 2: // sibling is Red
		else if (sibling.color == Red)
			case_2Deletion(DB_node);
		// Case 3: // sibling is Red, Sibling's child far from DB is black, 
		//    Sibling's chilf near to DB in red
		else if (sibling.color == Black &&
			(DB_node.far_child_sibling()).color == Black &&
			(DB_node.near_child_sibling()).color == Red)
			case_3Deletion(DB_node);
		else // if (sibling.color == Black && (DB_node.far_child_sibling()).color == Red)
			case_4Deletion(DB_node);
	}
}

	////////////////////////////////////////////



	