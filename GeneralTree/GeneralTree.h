#pragma once
#include <string>

namespace GeneralTree {

	template<class T> class Node {
		std::string key;
		T value;
		Node<T>* lChild;
		Node<T>* rSibling;

	public:
		Node(std::string name, T data) : key(name), value(data) {};
		inline T getValue() { return value; };
	};

	template<class T> class Tree {
		friend class Node<T>;
		Node<T>* rootNode;

		Node<T>* newNode(std::string, T);
	public:
		Tree();
		Tree(Node<T>* root) : rootNode(root) {};
	};
}