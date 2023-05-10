#pragma once
#include <string>
#include <vector>
#include <set>
#include <stack>

namespace GeneralTree {

	/*Represents a point on a tree.
	Using the left-child/right-sibling method therefore
	only these values are needed to traverse the respected tree*/
	template<class T> class Node {
	public:
		//Unique ID
		std::string key;

		//Data inside node
		T value;

		//Surrounding nodes
		Node<T>* lChild;
		Node<T>* rSibling;

		//Constructor
		Node(std::string name, T data) : 
			key(name), value(data), lChild(0), rSibling(0) {};

		bool operator==(const Node<T>&);

		inline T getValue() { return value; };
	};

	enum class SearchMethods {
		DFS,
		BFS
	};

	/*Represents a collection of nodes linked together
	via their left-most child and right siblings*/
	template<class T> class Tree {
		//Allows the use of the nodes members
		friend class Node<T>;
		
		//Top of the tree
		Node<T>* rootNode;
		//Generates a pointer to a new node
		Node<T>* newNode(std::string, T);

		Node<T>* depthFirstSearch(std::string);
	public:
		std::vector<Node<T>*> scan();
		//Constructors
		Tree();
		Tree(Node<T>* root) : rootNode(root) {};
		//Destructor
		~Tree();

		
		//Add nodes to existing nodes
		void addSibling(Node<T>*, std::string, T);
		void addChild(Node<T>*, std::string, T);

		Node<T>* find(SearchMethods, std::string);

		//Getters
		Node<T>* getRoot() { return rootNode; };
	};
}