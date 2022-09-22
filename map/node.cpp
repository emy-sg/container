#include "node.hpp"

    template <class value_type>
	Node::Node() { 
		is_null = 0;
		color = Black;
		parent = nullptr;
		l_child = nullptr;
		r_child = nullptr;
		std::cout << "Default Node Constructor\n";
	}

    template <class value_type>
	Node::Node(value_type v) : value(v) {
		is_null = 1; 
		color = 1;
		parent = nullptr;
		l_child = nullptr;
		r_child = nullptr;
		std::cout << "Parameterized Node Constructor\n";
	}
	
	// Assignement and Copy Constructor
    template <class value_type>
	Node::Node(const Node& inst) {
		std::cout << "Copy Node Construtor\n";
		*this = inst;
	}	

    template <class value_type>
	Node&	Node::operator=(const Node& inst) {
		is_null = inst.is_null;
		color = inst.color;
		value = inst.value;
		parent = inst.parent;
		l_child = inst.l_child;
		r_child = inst.r_child;
		std::cout << "Copy Assignement Node operator\n"; 
	}

    template <class value_type>
    Node::~Node() {}
	// comparaison operators ( == != < <= > >= )
	// ==> Call pair here