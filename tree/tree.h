#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <list>

template <typename T> class Tree {
public:
	struct Node {
		friend class Tree;
	private:
		std::list<Node*> children;
		Node* parent;
		T datum;

		Node(const Node &);
		Node& operator=(const Node &);

	public:
		Node();
		Node(T);
		Node(Node*);
		Node(Node*, T);
		~Node();

		T& operator*();
	};

private:
	Node* root;
	size_t size;
	size_t height;

	Tree(const Tree &);
	Tree& operator=(const Tree &);

public:
	Tree();
	~Tree();

	size_t getSize() const;
	size_t getHeight() const;

	Node* getRoot() const;
	Node* addChild(Node*, T);
	
	bool deleteFirstChild(Node*);
	bool deleteLastChild(Node*);
	bool deleteNthChild(Node*, size_t n);

	Node* getParent(Node*) const;

	size_t numChildren(Node*) const;
	Node* firstChild(Node*) const;
	Node* lastChild(Node*) const;
	Node* nthChild(Node*, size_t n) const;
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
	// Do nothing
	//
}

//Child, given value constructor
template <typename T>
Tree<T>::Node::Node(Node* ptr, T t) : children(), parent(ptr), datum(t) {
	// Do nothing
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

/////////////////////////
// Tree
/////////////////////////

#endif