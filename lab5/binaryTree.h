/* This code is written by Neelkumar Shailesh Bhuva
   as part of CSE 6341 (Foundations of Programming Languages) 
   project at the Ohio State University. 
*/
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;


typedef struct node{ 
	string value;
	node *left;
	node *right;
}tree_node;

class BinaryTree{
	public:
		tree_node* root;
		BinaryTree();
		//~BinaryTree() { cout << "constructor called\n";}
		
	public:
		tree_node* createDummy();
		tree_node createNode(string,tree_node*,tree_node*);
		void insert(tree_node*);
		void Print(tree_node*);
		void makeRoot(tree_node*);
		void inorderPrint(tree_node*);
		void makeNIL(tree_node*);
};

#endif