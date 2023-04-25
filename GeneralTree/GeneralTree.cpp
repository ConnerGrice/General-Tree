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
		root = newNode("Root", 0);
	}
}
