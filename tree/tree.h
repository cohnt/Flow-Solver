#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <list>
#include <algorithm>
#include <iostream>

template <typename T> class Tree {
public:
	struct Node {
		friend class Tree;
	private:
		std::list<Node*> children;
		Node* parent;

		Node(const Node &);
		Node& operator=(const Node &);

	public:
		T datum;

		Node();
		Node(T);
		Node(Node*);
		Node(Node*, T);
		~Node();

		Node* addChild();
		Node* addChild(T);

		bool deleteFirstChild();
		bool deleteLastChild();
		bool deleteNthChild(size_t);

		Node* getParent() const;

		size_t numChildren() const;
		Node* firstChild() const;
		Node* lastChild() const;
		Node* nthChild(size_t) const;
	};

private:
	Node* root;

	Tree(const Tree &);
	Tree& operator=(const Tree &);

	size_t sizeHelper(Node*) const;
	size_t heightHelper(Node*) const;

	void printHelper(Node*, size_t) const;

public:
	Tree();
	~Tree();

	size_t size() const;
	size_t height() const;

	Node* getRoot() const;
	void setRoot(Node*);

	void print() const;
};


/////////////////////////
// Node
/////////////////////////

//Root, default value constructor
template <typename T>
Tree<T>::Node::Node() : children(), parent(nullptr), datum() {
	// Do nothing
	//
}

//Root, given value constructor
template <typename T>
Tree<T>::Node::Node(T t) : children(), parent(nullptr), datum(t) {
	// Do nothing
	//
}

//Child, default value constructor
template <typename T>
Tree<T>::Node::Node(Node* ptr) : children(), parent(ptr), datum() {
	parent->children.emplace_back(this);
	//
}

//Child, given value constructor
template <typename T>
Tree<T>::Node::Node(Node* ptr, T t) : children(), parent(ptr), datum(t) {
	parent->children.emplace_back(this);
	//
}

//Destructor
template <typename T>
Tree<T>::Node::~Node() {
	//Recursively delete all children
	while(!children.empty()) {
		delete children.front(); //Delete the Node, freeing up the dynamic memory
		children.pop_front(); //Remove the Node from children
	}
}

//Copy constructor and assignment operator. These are private so that they can't be used.
template <typename T>
Tree<T>::Node::Node(const Tree<T>::Node & node) {}

template <typename T>
typename Tree<T>::Node& Tree<T>::Node::operator=(const typename Tree<T>::Node & node) {}

//Add child with default value, and return a pointer to it
template <typename T>
typename Tree<T>::Node* Tree<T>::Node::addChild() {
	new Node(this);
	return children.back();
}

//Add child with a given value, and return a pointer to it
template <typename T>
typename Tree<T>::Node* Tree<T>::Node::addChild(T t) {
	new Node(this, t);
	return children.back();
}

//Delete children from a Node in various ways. Return true if successful, or false if
//the child does not exist.
template <typename T>
bool Tree<T>::Node::deleteFirstChild() {
	if(children.empty()) {
		return false;
	}
	else {
		delete children.front();
		children.pop_front();
		return true;
	}
}

template <typename T>
bool Tree<T>::Node::deleteLastChild() {
	if(children.empty()) {
		return false;
	}
	else {
		delete children.back();
		children.pop_back();
		return true;
	}
}

template <typename T>
bool Tree<T>::Node::deleteNthChild(size_t n) {
	if(n >= children.size()) {
		return false;
	}
	else {
		auto iter = children.begin();
		for(size_t i=0; i<n; ++i) {
			++iter;
		}
		delete *iter;
		children.erase(iter);
		return true;
	}
}

//Get the parent pointer of a node. Note that this will return nullptr if the Node
//is a root Node
template <typename T>
typename Tree<T>::Node* Tree<T>::Node::getParent() const {
	//
	return parent;
}

//Various functions relating to accessing the children of the Node. If the child
//requested doesn't exist, it will return a nullptr.
template <typename T>
size_t Tree<T>::Node::numChildren() const {
	//
	return children.size();
}

template <typename T>
typename Tree<T>::Node* Tree<T>::Node::firstChild() const {
	if(children.empty()) {
		return nullptr;
	}
	else {
		return children.front();
	}
}

template <typename T>
typename Tree<T>::Node* Tree<T>::Node::lastChild() const {
	if(children.empty()) {
		return nullptr;
	}
	else {
		return children.back();
	}
}

template <typename T>
typename Tree<T>::Node* Tree<T>::Node::nthChild(size_t n) const {
	if(n >= children.size()) {
		return nullptr;
	}
	else {
		auto iter = children.begin();
		for(size_t i=0; i<n; ++i) {
			++iter;
		}
		return *iter;
	}
}

/////////////////////////
// Tree
/////////////////////////

//Constructor
template <typename T>
Tree<T>::Tree() : root(nullptr) {
	// Do nothing
	//
}

//Destructor
template <typename T>
Tree<T>::~Tree() {
	delete root; //Because root is dynamically-allocated, we must explicitly call delete
	root = nullptr;
}

//Get the size of the tree.
template <typename T>
size_t Tree<T>::size() const {
	//
	return 1+sizeHelper(root);
}

//Returns the total number of descendants from ptr. The size of the tree rooted at ptr is thus
//sizeHelper(ptr)+1.
template <typename T>
size_t Tree<T>::sizeHelper(Tree<T>::Node* ptr) const {
	if(ptr == nullptr) {
		return 0;
	}

	size_t total = 0;
	const size_t childrenSize = ptr->children.size();
	for(size_t i=0; i<childrenSize; ++i) {
		total += sizeHelper(ptr->children[i]);
	}
	return total;
}

//Get the height of the tree.
template <typename T>
size_t Tree<T>::height() const {
	//
	return heightHelper(root);
}

//Returns the height of the tree rooted at ptr
template <typename T>
size_t Tree<T>::heightHelper(Tree<T>::Node* ptr) const {
	if(ptr == nullptr) {
		return 0;
	}

	std::list<size_t> heights;
	const size_t childrenSize = ptr->children.size();
	for(size_t i=0; i<childrenSize; ++i) {
		heights.emplace_back(heightHelper(ptr->children[i]));
	}
	return 1 + *(std::max_element(heights.begin(), heights.end()));
}

//Return a ptr to the root node.
template <typename T>
typename Tree<T>::Node* Tree<T>::getRoot() const {
	//
	return root;
}

//Erase the current root Node, and assign root to a new Node
template <typename T>
void Tree<T>::setRoot(Tree<T>::Node* ptr) {
	delete root;
	root = nullptr;

	root = ptr;
}

//Print out the contents of a tree to the console, given that T can be
//sent to cout.
template <typename T>
void Tree<T>::print() const {
	if(root == nullptr) {
		std::cout << "." << std::endl;
		return;
	}
	else {
		std::cout << root->datum << std::endl;
		printHelper(root, 0);
	}
}

template <typename T>
void Tree<T>::printHelper(Tree<T>::Node* ptr, size_t numIndents) const {
	const size_t childrenSize = ptr->numChildren();
	for(size_t i=0; i<childrenSize; ++i) {
		for(size_t j=0; j<numIndents; ++j) {
			std::cout << "    ";
		}
		if(i+1 == childrenSize) {
			std::cout << "\u2514";
		}
		else {
			std::cout << "\u251c";
		}
		std::cout << "\u2500\u2500 " << ptr->nthChild(i)->datum << std::endl;
		printHelper(ptr->nthChild(i), numIndents+1);
	}
}

#endif