#include "tree.h"
#include <iostream>

int main() {
	Tree<int> t1;
	Tree<int> t2(5);

	t1.setRoot(new Tree<int>::Node(17));
	t1.setRoot(6);

	std::cout << "size: " << t1.size() << std::endl;
	std::cout << "height: " << t1.height() << std::endl;

	t1.print();

	Tree<int>::Node* root = t1.getRoot();
	auto r2 = t2.getRoot();
	(void)r2;
	std::cout << "root datum: " << root->datum << std::endl;

	auto tempPtr = root->addChild();
	tempPtr->datum = 15;
	root->addChild()->datum = 16;
	root->addChild(17);
	root->addChild(18);
	root->addChild(19);
	root->addChild(20);
	root->addChild(20);

	t1.print();

	root->deleteFirstChild();

	t1.print();

	root->deleteLastChild();
	root->deleteNthChild(3);

	t1.print();

	auto tempPtr2 = root->firstChild();
	tempPtr2->datum = 1;
	root->lastChild()->datum = -1;
	root->nthChild(1)->datum = 43;

	t1.print();

	Tree<int>::Node* child = root->firstChild()->addChild(100);
	child->getParent()->addChild(200);
	child->getParent()->addChild(300);

	std::cout << "root num children: " << root->numChildren() << std::endl;

	t1.print();
}