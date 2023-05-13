// GeneralTree.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "GeneralTree.h"

namespace GeneralTree {

	template<class T>
	bool Node<T>::operator==(const Node<T>& other) {
		return key == other.key && lChild == other.lChild && rSibling == other.rSibling;
	}

	template<class T>
	bool Node<T>::operator!=(const Node<T>& other) {
		return key != other.key || lChild != other.lChild || rSibling != other.rSibling;
	}

	template<class T>
	std::shared_ptr<Node<T>> Tree<T>::newNode(std::string name, T data) {
		std::shared_ptr<Node<T>> node(new Node<T>(name, data));
		return node;
	}

	template<class T>
	std::vector<std::shared_ptr<Node<T>>> Tree<T>::scan() {
		std::stack<std::shared_ptr<Node<T>>> subTree;
		subTree.push(rootNode);
		std::vector<std::shared_ptr<Node<T>>> output;

		while (!subTree.empty()) {
			auto tempNode = subTree.top();
			subTree.pop();
			output.push_back(tempNode);

			std::stack<std::shared_ptr<Node<T>>> siblings;
			if (tempNode->lChild) {
				tempNode = tempNode->lChild;
				siblings.push(tempNode);
				while (tempNode->rSibling) {
					tempNode = tempNode->rSibling;
					siblings.push(tempNode);
				}
			}
			while (!siblings.empty()) {
				subTree.push(siblings.top());
				siblings.pop();
			}
		}
		std::reverse(output.begin(), output.end());
		return output;
	}

	template<class T>
	void Tree<T>::addSibling(
		std::shared_ptr<Node<T>> child, std::string name, T value) {

		//Go to the last sibling
		while (child->rSibling)
			child = child->rSibling;

		child->rSibling = newNode(name, value);
	}

	template<class T>
	void Tree<T>::addChild(
		std::shared_ptr<Node<T>> parent, std::string name, T value) {

		//Check if child exists and add sibling to that child
		if (parent->lChild)
			addSibling(parent->lChild, name, value);
		else
			parent->lChild = newNode(name, value);
	}

	template<class T>
	std::shared_ptr<Node<T>> Tree<T>::depthFirstSearch(std::string key) {
		
		std::vector<std::shared_ptr<Node<T>>> stack{ rootNode };
		std::set<std::shared_ptr<Node<T>>> visited;

		//Continue until all nodes are visited
		while (!stack.empty()) {
			//Pop node off stack
			auto node = stack.back();
			stack.pop_back();
			
			//Return node if found
			if (node->key == key)
				return node;

			//Has node already been visited?
			auto iter = visited.find(node);
			if (iter != visited.end())
				continue;
			
			//Visit node flag
			visited.insert(node);

			//Scan through all linked child nodes and push onto stack
			if (!node->lChild)
				continue;

			node = node->lChild;
			stack.push_back(node);
			while (node->rSibling) {
				node = node->rSibling;
				stack.push_back(node);
			}
		}
		//Node not found
		throw std::invalid_argument("Node not FOUND. Please give a value key");
	}

	template<class T>
	std::shared_ptr<Node<T>> Tree<T>::breadthFirstSearch(std::string key) {
		std::queue<std::shared_ptr<Node<T>>> queue;
		queue.push(rootNode);
		std::set<std::shared_ptr<Node<T>>> visited;

		//Loop until all nodes have been scanned
		while (!queue.empty()) {
			auto node = queue.front();
			queue.pop();

			//Finish search if node is found
			if (node->key == key)
				return node;

			//Skip node if already scanned
			auto iter = visited.find(node);
			if (iter != visited.end())
				continue;

			visited.insert(node);
			
			//Skip if external node
			if (!node->lChild)
				continue;

			//Scan all children of node being scanned
			node = node->lChild;
			queue.push(node);
			while (node->rSibling) {
				node = node->rSibling;
				queue.push(node);
			}
		}
		throw std::invalid_argument("Node not FOUND.Please give a value key!");
	}

	template<class T>
	std::shared_ptr<Node<T>> Tree<T>::find(SearchMethods method, std::string key) {
		if (method == SearchMethods::DFS)
			return depthFirstSearch(key);
		else if (method == SearchMethods::BFS)
			return breadthFirstSearch(key);
	}
}
