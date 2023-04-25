#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeneralTreeTest
{
	TEST_CLASS(GeneralTreeTest)
	{
	public:
		
		TEST_METHOD(firstTest) {
			GeneralTree::Node<int>* root = new GeneralTree::Node<int>("Root", 3);
			GeneralTree::Tree<int> t(root);
			Assert::AreEqual(3, t.getRootValue());
		}
	};
}
