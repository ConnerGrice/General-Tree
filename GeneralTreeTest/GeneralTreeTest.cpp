#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeneralTreeTest
{
	TEST_CLASS(GeneralTreeTest)
	{
	public:
		/*Ability to add nodes*/
		TEST_METHOD(addNodes) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "First", 3);
			t.addChild(root, "Second", 4);
			t.addChild(root, "Third", 5);
			auto node = root->getChild()->getSibling()->getSibling();
			t.addSibling(node, "Fourth", 6);
			Assert::IsTrue(root->getChild()->getSibling()->getSibling()->getSibling()->value);
		}

		TEST_METHOD(addNewChild) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "First", 3);
			t.addChild(root, "Second", 4);
			t.addChild(root, "Third", 5);
			auto node = root->getChild()->getSibling()->getSibling();
			std::shared_ptr<GeneralTree::Node<int>> newN(new GeneralTree::Node<int>("NewNode", -1));
			t.addSibling(node, newN);
			Assert::IsTrue(root->getChild()->getSibling()->getSibling()->getSibling()->value);
		}

		/*Simple search using depth first*/
		TEST_METHOD(depthSearchSimple) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "First", 3);
			t.addChild(root, "Second", 4);
			t.addChild(root, "Third", 5);
			auto node = t.find(GeneralTree::SearchMethods::DFS, "Third");
			Assert::AreEqual(5,node->value);
		}

		/*More complex search using depth search*/
		TEST_METHOD(depthSearchComplex) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "First", 3);
			t.addChild(root, "Second", 4);
			t.addChild(root, "Third", 5);
			auto node = t.find(GeneralTree::SearchMethods::DFS, "Second");
			t.addChild(node,"Fourth",6);
			t.addChild(node,"Fifth",8);
			node = node->getChild();
			t.addChild(node,"Sixth",9);
			t.addChild(node,"Seventh",3);
			Assert::IsNotNull(t.find(GeneralTree::SearchMethods::DFS, "Fourth").get());
		}

		/*Execption for node not found*/
		TEST_METHOD(depthSearchNull) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "First", 3);
			t.addChild(root, "Second", 4);
			t.addChild(root, "Third", 5);
			auto node = t.find(GeneralTree::SearchMethods::DFS, "Second");
			t.addChild(node, "Fourth", 6);
			t.addChild(node, "Fifth", 8);
			node = node->getChild();
			t.addChild(node, "Sixth", 9);
			t.addChild(node, "Seventh", 3);

			auto func = [&] { t.find(GeneralTree::SearchMethods::DFS, "NotReal"); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(postOrderTest) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "A", 3);
			t.addChild(root, "B", 2);
			t.addChild(root, "C", 4);
			auto node = t.find(GeneralTree::SearchMethods::DFS, "A");
			t.addChild(node, "D", 5);
			t.addChild(node, "E", 6);
			auto result = t.scan();

			std::vector<int> given;
			for (const auto& item : result) {
				given.push_back(item->value);
			}
			std::vector<int> expected{ 4,2,6,5,3,0 };
			Assert::IsTrue(expected == given);
		}

		/*Simple search using depth first*/
		TEST_METHOD(breadthSearchSimple) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "First", 3);
			t.addChild(root, "Second", 4);
			t.addChild(root, "Third", 5);
			auto node = t.find(GeneralTree::SearchMethods::BFS, "Third");
			Assert::AreEqual(5, node->value);
		}
	};
}
