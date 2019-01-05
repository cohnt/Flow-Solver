#include "../tree/tree.h"
#include <cassert>
#include <vector>

int main() {
	//Test the various Node constructors available.
	Tree<int>::Node* n1 = new Tree<int>::Node();
	Tree<int>::Node* n2 = new Tree<int>::Node(10);
	Tree<int>::Node* n3 = new Tree<int>::Node(n2);
	Tree<int>::Node* n4 = new Tree<int>::Node(n2, 20);
	Tree<int>::Node* n5 = new Tree<int>::Node(n2, 30);
	Tree<int>::Node* n6 = new Tree<int>::Node(n4, 40);

	//Suppress the unused variable warning -- they are being used.
	(void)n3;
	(void)n5;
	(void)n6;

	//Run with valgrind to ensure no memory is leaked
	delete n1;
	delete n2;


	//Test adding children to a node.
	Tree<int>::Node* n7 = new Tree<int>::Node(1);
	n7->addChild();
	Tree<int>::Node* n8 = n7->addChild(5);
	n8->addChild(10);

	//Run with valgrind to ensure no memory is leaked
	delete n7;


	//Test deleting children manually in various ways
	Tree<int>::Node* n9 = new Tree<int>::Node(1);
	n9->addChild(1);
	n9->addChild(2);
	n9->addChild(3);
	n9->addChild(4);
	Tree<int>::Node* n10 = n9->addChild(5);
	n10->addChild(100);
	n10->addChild(200);
	n9->addChild(43);

	assert(n9->deleteFirstChild() == true);
	assert(n9->firstChild()->datum == 2);

	assert(n9->deleteNthChild(2) == true);
	assert(n9->nthChild(2)->datum == 5);

	assert(n9->lastChild()->datum == 43);
	assert(n9->deleteLastChild() == true);
	assert(n9->lastChild()->datum == 5);

	assert(n9->deleteNthChild(50) == false);

	//Run with valgrind to ensure no memory is leaked
	delete n9;


	//Test the getParent method
	Tree<int>::Node* n11 = new Tree<int>::Node(1);
	n11 = n11->addChild(2);

	//Run with valgrind to ensure no memory is leaked
	delete n11->getParent();


	//Test accessing the first, last, and nth child of a node
	Tree<int>::Node* n12 = new Tree<int>::Node();
	n12->addChild(1);
	n12->addChild(2);
	n12->addChild(3);
	n12->addChild(4);
	n12->addChild(5);

	assert(n12->firstChild()->datum == 1);
	assert(n12->lastChild()->datum == 5);
	assert(n12->nthChild(2)->datum == 3);
	assert(n12->nthChild(5) == nullptr);
	assert(n12->nthChild(43) == nullptr);

	delete n12;


	//Test child accessing and deleting for a node with no children
	Tree<int>::Node* n13 = new Tree<int>::Node();

	assert(n13->deleteFirstChild() == false);
	assert(n13->deleteLastChild() == false);
	assert(n13->deleteNthChild(0) == false);
	assert(n13->deleteNthChild(1) == false);
	assert(n13->deleteNthChild(5) == false);

	assert(n13->firstChild() == nullptr);
	assert(n13->lastChild() == nullptr);
	assert(n13->nthChild(0) == nullptr);
	assert(n13->nthChild(1) == nullptr);
	assert(n13->nthChild(5) == nullptr);

	delete n13;


	//Test the Tree constructor and destructor
	Tree<int> t0;
	Tree<int> t1(3);


	//Test assigning a new root to a tree, adding some elements to it, etc.
	Tree<int> t2;
	t2.setRoot(new Tree<int>::Node(1));
	Tree<int> t3;
	t3.setRoot(3);


	//Test tree with a more complex object
	Tree<std::vector<int>> t4;
	t4.setRoot(new Tree<std::vector<int>>::Node(std::vector<int>{1, 2, 3}));


	//Test printing out a tree
	Tree<int> t5;
	t5.setRoot(new Tree<int>::Node(1));
	t5.getRoot()->addChild(3);
	auto temp = t5.getRoot()->addChild(4);
	temp->addChild(100);
	temp->addChild(101);
	temp->addChild(43);
	t5.getRoot()->addChild(6);
	t5.getRoot()->addChild(7);
	t5.print();

	return 0;
}