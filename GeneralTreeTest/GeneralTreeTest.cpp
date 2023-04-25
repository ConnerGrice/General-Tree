#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeneralTreeTest
{
	TEST_CLASS(GeneralTreeTest)
	{
	public:
		
		TEST_METHOD(addNodes) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "First", 3);
			t.addChild(root, "Second", 4);
			t.addChild(root, "Third", 5);
			auto node = root->lChild->rSibling->rSibling;
			t.addSibling(node, "Fourth", 6);
			Assert::IsTrue(root->lChild->rSibling->rSibling->rSibling);
		}

		TEST_METHOD(depthSearchSimple) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "First", 3);
			t.addChild(root, "Second", 4);
			t.addChild(root, "Third", 5);
			auto node = t.find(GeneralTree::SearchMethods::DFS, "Third");
			Assert::AreEqual(5,node->value);
		}

		TEST_METHOD(depthSearchComplex) {
			GeneralTree::Tree<int> t;
			auto root = t.getRoot();
			t.addChild(root, "First", 3);
			t.addChild(root, "Second", 4);
			t.addChild(root, "Third", 5);
			auto node = t.find(GeneralTree::SearchMethods::DFS, "Second");
			t.addChild(node,"Fourth",6);
			t.addChild(node,"Fifth",8);
			node = node->lChild;
			t.addChild(node,"Sixth",9);
			t.addChild(node,"Seventh",3);
			Assert::IsNotNull(t.find(GeneralTree::SearchMethods::DFS, "Fourth"));
		}
	};
}
