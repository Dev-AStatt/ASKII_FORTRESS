#pragma once
// Tree traversal in C++
#include <vector>
#include <memory>
#include <GameConfig.h>

struct Node {
	AKI::Block block;
	AKI::I3d location;
	std::vector<std::unique_ptr<Node>> children;

	Node(AKI::Block b, AKI::I3d pos) {
		this->block = b;
		this->location = pos;
	}
	void newChild(AKI::Block b, AKI::I3d pos) {
		this->children.emplace_back(std::make_unique<Node>(b,pos));
		//this->children.emplace_back(new Node(b,pos));
	}
	bool hasChildren() {
		if(children.size() > 0) {return true;}
		return false;
	}
	//do not call this unless you are sure i is within children
	std::unique_ptr<Node>& getChild(int i) {
		if(getNumChildren() > i) {throw std::invalid_argument("Tree Ref to child out of bounds");}
		return children[i];
	}
	int getNumChildren() {return (int)children.size();}

};


/*
struct Node {
	AKI::Block block;
	AKI::I3d location;
	std::vector<Node*> children;

	Node(AKI::Block b, AKI::I3d pos) {
		this->block = b;
		this->location = pos;
	}
	void newChild(AKI::Block b, AKI::I3d pos) {
		this->children.emplace_back(new Node(b,pos));
	}
	bool hasChildren() {
		if(children.size() > 0) {return true;}
		return false;
	}
	Node* getChild(int i) {
		if(i < (int)children.size()) {return children[i];}
		else{return nullptr;}
	}
	int getNumChildren() {return (int)children.size();}

};
*/


/*
#include <iostream>

struct Node {
  int data;
  struct Node *left, *right;
  Node(int data) {
	this->data = data;
	left = right = NULL;
  }
};

// Preorder traversal
void preorderTraversal(struct Node* node) {
  if (node == NULL)
	return;

  std::cout << node->data << "->";
  preorderTraversal(node->left);
  preorderTraversal(node->right);
}

// Postorder traversal
void postorderTraversal(struct Node* node) {
  if (node == NULL)
	return;

  postorderTraversal(node->left);
  postorderTraversal(node->right);
  std::cout << node->data << "->";
}

// Inorder traversal
void inorderTraversal(struct Node* node) {
  if (node == NULL)
	return;

  inorderTraversal(node->left);
  std::cout << node->data << "->";
  inorderTraversal(node->right);
}

int main() {
  struct Node* root = new Node(1);
  root->left = new Node(12);
  root->right = new Node(9);
  root->left->left = new Node(5);
  root->left->right = new Node(6);

  std::cout << "Inorder traversal ";
  inorderTraversal(root);

  std::cout << "\nPreorder traversal ";
  preorderTraversal(root);

  std::cout << "\nPostorder traversal ";
  postorderTraversal(root);
}

*/
