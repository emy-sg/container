#include "./RBTree.hpp"
#include <utility>

#include "./programizRbTree.hpp"

int main(int argc, char**argv)
{
    Tree<int, int> tree;
    test::RedBlackTree ptree;
    for (int i = 1; i < argc; i++)
    {
        std::cout << ::atoi(argv[i]) << std::endl;

        tree.insertion_RBTree(std::make_pair<int, int>( ::atoi(argv[i]), i + 1));
        ptree.insert(::atoi(argv[i]));
    }

    // print _root;

    tree.printTree();
    std::cout << "========================================================================" << std::endl;
    ptree.printTree();

}