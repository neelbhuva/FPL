/* This code is written by Neelkumar Shailesh Bhuva
   as part of CSE 6341 (Foundations of Programming Languages) 
   project at the Ohio State University. 
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>
#include "binaryTree.h"


using namespace std;

class Interpreter{
	public:
		int length(tree_node*);
		tree_node* car(tree_node* s);
		tree_node* cdr(tree_node* s);
		tree_node* cons(tree_node* s1, tree_node* s2);
		tree_node* atom(tree_node* s);
		tree_node* INT(tree_node* s);
		tree_node* null(tree_node* s);
		tree_node* eq(tree_node* s1,tree_node* s2);
		tree_node* plus(tree_node* s1,tree_node* s2);
		tree_node* minus(tree_node* s1,tree_node* s2);
		tree_node* times(tree_node* s1,tree_node* s2);
		tree_node* less(tree_node* s1,tree_node* s2);
		tree_node* greater(tree_node* s1,tree_node* s2);
		tree_node* createNode(string,tree_node*,tree_node*);
		tree_node* eval(tree_node*);
		bool isNumeric(tree_node*);
		bool in_array(const string&, const vector<string>&);
		void printSExpression(tree_node*);
		bool isList(tree_node*);
		void inorderPrint(tree_node*);
		bool allListOfLengthTwo(tree_node*);
		tree_node* COND_eval(tree_node*);
};


#endif