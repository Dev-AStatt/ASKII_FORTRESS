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
		if(getNumChildren() < i) {throw std::invalid_argument("Tree Ref to child out of bounds");}
		return children[i];
	}
	int getNumChildren() {return (int)children.size();}

};


