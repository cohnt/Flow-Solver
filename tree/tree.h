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
		T data;
	public:
		Node();
		Node(T);
		~Node();

		T& operator*();
	};

private:
	Node* root;
	size_t size;
	size_t height;

public:
	Tree(T);
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

#endif