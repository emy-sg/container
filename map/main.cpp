#include "./RBTree.hpp"
#include <utility>
#include <vector>

#include "./programizRbTree.hpp"

int main(int argc, char**argv)
{
    ////////////////////////////////
/*    int main() {
  RedBlackTree bst;
  bst.insert(55);
  bst.insert(40);
  bst.insert(65);
  bst.insert(60);
  bst.insert(75);
  bst.insert(57);

  bst.printTree();
  cout << endl
     << "After deleting" << endl;
  bst.deleteNode(40);
  bst.printTree();
}*/
    ///////////////////////////////////////
    Tree<int, int> tree;
    //std::vector<Node<std::pair<int, int> >* > nodes;
    test::RedBlackTree ptree;
    for (int i = 1; i < argc; i++)
    {
        //std::cout << ::atoi(argv[i]) << std::endl;

        //nodes.push_back(tree.insertion_RBTree(std::make_pair<int, int>( ::atoi(argv[i]), i + 1)));
        tree.insertion_RBTree(std::make_pair<int, int>( ::atoi(argv[i]), i + 1));
        ptree.insert(::atoi(argv[i]));
    }

    /*for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->printNode();
    }*/

    tree.printTree();
    std::cout << "========================================================================" << std::endl;
    ptree.printTree();

    std::cout << "=========================== Deletion 18=================================" << std::endl;

    tree.delete_RBTree(18);
    ptree.deleteNode(18);

    tree.printTree();
    ptree.printTree();

    std::cout << "=========================== Deletion 11 =================================" << std::endl;
    tree.delete_RBTree(11);
    ptree.deleteNode(11);

    tree.printTree();
    ptree.printTree();

    std::cout << "=========================== Deletion 3=================================" << std::endl;
    tree.delete_RBTree(3);
    ptree.deleteNode(3);

    tree.printTree();
    ptree.printTree();

    
    std::cout << "=========================== Deletion 10=================================" << std::endl;
    tree.delete_RBTree(10);
    ptree.deleteNode(10);

    tree.printTree();
    ptree.printTree();
    
    std::cout << "=========================== Deletion 22=================================" << std::endl;
    tree.delete_RBTree(22);
    ptree.deleteNode(22);

    tree.printTree();  
    ptree.printTree();
    
    std::cout << "========================================================================" << std::endl;
    //ptree.printTree();
}