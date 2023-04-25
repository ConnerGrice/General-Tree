// GeneralTree.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "GeneralTree.h"

namespace GeneralTree {

	template<class T> Node<T>* Tree<T>::newNode(std::string name, T data) {
		auto node = new Node<T>(name, data);
		return node;
	}

	template<class T> Tree<T>::Tree() {
		rootNode = newNode("Root", 0);
	}

	template<class T> void Tree<T>::addSibling(
		Node<T>* child, std::string name, T value) {

		while (child->rSibling)
			child = child->rSibling;
		child->rSibling = newNode(name, value);

	}

	template<class T> void Tree<T>::addChild(
		Node<T>* parent, std::string name, T value) {

		if (parent->lChild)
			addSibling(parent->lChild, name, value);
		else
			parent->lChild = newNode(name, value);
	}

	template<class T> Node<T>* Tree<T>::depthFirstSearch(std::string key) {
		std::vector<Node<T>*> stack{ rootNode };
		std::set<Node<T>*> visited;
		while (!stack.empty()) {
			auto node = stack.back();
			stack.pop_back();
			
			if (node->key == key)
				return node;

			auto iter = visited.find(node);
			if (iter == visited.end()) {
				visited.insert(node);
				
				//TODO: Go through all children

			}
			
		}
		throw std::invalid_argument("Node not FOUND. Please give a value key");
		
	}

	template<class T> Node<T>* Tree<T>::find(SearchMethods method, std::string key) {
		if (method == SearchMethods::DFS)
			return depthFirstSearch(key);
		else if (method == SearchMethods::BFS)
			return newNode("Error", 0);
	}
}
