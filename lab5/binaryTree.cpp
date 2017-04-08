#include <iostream>
#include <string>
#include "binaryTree.h"

using namespace std;

BinaryTree::BinaryTree()
{
	root = new tree_node();
	root->value = "DUMMY";
	root->left = NULL;
	root->right = NULL;
}

void BinaryTree::makeRoot(tree_node* temp)
{
	this->root->value = temp->value;
}

tree_node* BinaryTree::createDummy()
{
	tree_node* dummy_node = new tree_node();
	dummy_node->value = "DUMMY";
	dummy_node->left = NULL;
	dummy_node->right = NULL;
	return dummy_node;
}

tree_node BinaryTree::createNode(string value, tree_node* left, tree_node* right)
{
	tree_node temp = {value,left,right};
	tree_node *temp1 = &temp;
	return temp;
}

void BinaryTree::Print(tree_node* temp)
{
	if(temp->left == NULL and temp->right == NULL)
	{
		cout << temp->value;
	}
	else
	{
		cout << "(";
		this->Print(temp->left);
		cout << " . ";
		this->Print(temp->right);
		cout << ")";
	}
}

void BinaryTree::inorderPrint(tree_node* node)
{
	if(node)
	{
		this->inorderPrint(node->left);
		cout << node->value << " ";
		this->inorderPrint(node->right);
	}
}

void BinaryTree::insert(tree_node* node)
{
	tree_node* temp = node;
	tree_node* tracer = this->root;
	if(tracer->left == NULL)
	{
		tracer->left = temp;
		tracer->right = BinaryTree::createDummy();
	}
	else
	{
		while(tracer->right != NULL)
		{
			tracer = tracer->right;
			if(tracer->left == NULL)
			{
				tracer->left = temp;
				tracer->right = BinaryTree::createDummy();
				break;
			}			
		}
	}
}

void BinaryTree::makeNIL(tree_node* node)
{
	while(node)
	{
		if(node->right == NULL)
		{
			node->value = "NIL";
			break;
		}
		node = node->right;
	}
}
