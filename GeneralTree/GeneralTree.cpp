// GeneralTree.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "GeneralTree.h"

namespace GeneralTree {

	template<class T>
	bool Node<T>::operator==(const Node<T>& other) {
		return key == other.key &&
			lChild == other.lChild &&
			rSibling == other.rSibling &&
			parent == other.parent;
	}

	template<class T>
	bool Node<T>::operator!=(const Node<T>& other) {
		return key != other.key ||
			lChild != other.lChild ||
			rSibling != other.rSibling ||
			parent != other.parent;
	}

	template<class T>
	std::shared_ptr<Node<T>> Tree<T>::newNode(
		std::shared_ptr<Node<T>> parent,std::string name, T data) {
		std::shared_ptr<Node<T>> node(new Node<T>(parent,name, data));
		return node;
	}

	template<class T>
	Tree<T>::ForwardIterator& Tree<T>::ForwardIterator::operator++() {
		if (!node)
			throw std::out_of_range("End of tree");
		
		if (node->lChild) {
			forwardStack.push(node->lChild);
			pointer temp = node->lChild;
			while (temp->rSibling) {
				forwardStack.push(temp->rSibling);
				temp = temp->rSibling;
			}
		}

		if (forwardStack.empty())
			node = nullptr;
		else {
			node = forwardStack.top();
			forwardStack.pop();
		}
		return *this;
	}

	template<class T>
	Tree<T>::ForwardIterator Tree<T>::ForwardIterator::operator++(int) {
		auto old = *this;
		++(*this);
		return old;
	}

	template<class T>
	std::vector<std::shared_ptr<Node<T>>> Tree<T>::scan(std::shared_ptr<Node<T>> start) {
		std::stack<std::shared_ptr<Node<T>>> subTree;
		subTree.push(start);
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

		auto parent = child->parent;
		if (!parent)
			return;

		//Go to the last sibling
		while (child->rSibling)
			child = child->rSibling;

		child->rSibling = newNode(parent,name, value);
	}

	template<class T>
	void Tree<T>::addSibling(
		std::shared_ptr<Node<T>> child, std::shared_ptr<Node<T>> sibling) {

		auto parent = child->parent;
		if (!parent)
			return;
		sibling->parent = parent;
		while (child->rSibling)
			child = child->rSibling;

		child->rSibling = sibling;
	}

	template<class T>
	void Tree<T>::addChild(
		std::shared_ptr<Node<T>> parent, std::string name, T value) {

		//Check if child exists and add sibling to that child
		if (parent->lChild)
			addSibling(parent->lChild, name, value);
		else
			parent->lChild = newNode(parent,name, value);
	}

	template<class T>
	void Tree<T>::addChild(
		std::shared_ptr<Node<T>> parent, std::shared_ptr<Node<T>> child) {
		child->parent = parent;
		if (parent->lChild)
			addSibling(parent->lChild, child);
		else
			parent->lChild = child;
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
		else
			throw std::invalid_argument("Please give a valid search method");
	}
}
