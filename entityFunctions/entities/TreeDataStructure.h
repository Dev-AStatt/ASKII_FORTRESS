#pragma once
// Tree traversal in C++
#include <vector>
#include <memory>
#include <GameConfig.h>

struct Node {
	int slabID;
	int infillID;
	AKI::I3d location;
	std::vector<Node*> children;

	Node(int nSlab, int nInfill) {
		this->slabID = nSlab;
		this->infillID = nInfill;
	}
	void newChild(int nSlab, int nInfill) {
		this->children.emplace_back(new Node(nSlab,nInfill));
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
