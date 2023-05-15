#pragma once
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <memory>
#include <stdexcept>

namespace GeneralTree {
	template<class T> class Tree;

	/*Represents a point on a tree.
	Using the left-child/right-sibling method therefore
	only these values are needed to traverse the respected tree*/
	template<class T> class Node {
		friend Tree<T>;
		
		//Unique ID
		std::string key;
		//Surrounding nodes
		std::shared_ptr<Node<T>> lChild;
		std::shared_ptr<Node<T>> rSibling;
		std::shared_ptr<Node<T>> parent;
	public:

		//Data inside node
		T value;

		//Constructor
		Node(std::string name, T data) :
			key(name), value(data), lChild(0), rSibling(0), parent(0) {};
		Node(std::shared_ptr<Node<T>> parent,std::string name, T data) : 
			key(name), value(data), lChild(0), rSibling(0), parent(parent) {};


		//Comparison
		bool operator==(const Node<T>&);
		bool operator!=(const Node<T>&);

		std::shared_ptr<Node<T>> getChild() { return lChild; };
		std::shared_ptr<Node<T>> getSibling() { return rSibling; };
		std::shared_ptr<Node<T>> getParent() { return parent; };
		std::string getKey() { return key; };
	};

	/*Represents the different methods of searching the tree.*/
	enum class SearchMethods {
		DFS, //Depth first search
		BFS	//Breadth first search
	};

	/*Represents a collection of nodes linked together
	via their left-most child and right siblings*/
	template<class T> class Tree {
		std::shared_ptr<Node<T>> newNode(std::shared_ptr<Node<T>>,std::string, T);

		std::shared_ptr<Node<T>> rootNode;
		//Search methods
		std::shared_ptr<Node<T>> depthFirstSearch(std::string);
		std::shared_ptr<Node<T>> breadthFirstSearch(std::string);
	
	public:
		/*
		An iterator that will scan through the nodes of the tree
		*/
		struct ForwardIterator {
			using iterator_concept = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = Node<T>;
			using pointer = std::shared_ptr<Node<T>>;
			using reference = Node<T>&;

			ForwardIterator() = default;
			ForwardIterator(pointer ptr) : node(ptr) {};

			reference operator*() const { return *node; };
			pointer operator->() { return node; };

			//Pre-order traversal
			ForwardIterator& operator++();
			ForwardIterator operator++(int);

			friend bool operator==(const ForwardIterator& a,
				const ForwardIterator& b) { return a.node == b.node; };
			friend bool operator!=(const ForwardIterator& a,
				const ForwardIterator& b) { return a.node != b.node; }
			
		private:
			pointer node;
			std::stack<pointer> forwardStack;
		};

		//Constructors
		Tree() : rootNode(newNode(nullptr,"Root", 0)) {};
		Tree(std::shared_ptr<Node<T>> root) : rootNode(root) {};
		Tree(std::string key, T value) : rootNode(newNode(nullptr,key, value)) {};

		//Iterator methods
		ForwardIterator begin() { return ForwardIterator(rootNode); };
		ForwardIterator end() { return ForwardIterator(nullptr); };

		//Add nodes to existing nodes
		void addSibling(std::shared_ptr<Node<T>>, std::string, T);
		void addSibling(std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>);
		void addChild(std::shared_ptr<Node<T>>, std::string, T);
		void addChild(std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>);

		//Return a node given a unique key
		std::shared_ptr<Node<T>> find(SearchMethods, std::string);
		
		//Get list of nodes in the post-order order
		std::vector<std::shared_ptr<Node<T>>> scan(std::shared_ptr<Node<T>> start);
		inline std::vector<std::shared_ptr<Node<T>>> scan() { return scan(rootNode); };
		
		std::shared_ptr<Node<T>> getRoot() { return rootNode; };
	};
}