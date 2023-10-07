#include <iostream>

using namespace std;

class rbNode {
public:
	int value, height;
	bool isBlack;
	rbNode* p;
	rbNode* lc;
	rbNode* rc;
	//Default constructor
	rbNode(int value = 0, int height = 0, bool isBlack = false, rbNode* p = nullptr, rbNode* lc = nullptr, rbNode* rc = nullptr) {
		this->value = value;
		this->height = height;
		this->isBlack = isBlack;
		this->p = p;
		this->lc = lc;
		this->rc = rc;
	}
};

class rbTree {
public:
	rbNode* root;
	rbNode* sentinel;
	//Default constructor
	rbTree(rbNode* root = nullptr) {
		this->root = root;
		this->sentinel = new rbNode();
	}
	//Insert a new node on the tree
	void insert(int value) {

	}

	//Destructor
	~rbTree() {
		delete sentinel;
	}
};
