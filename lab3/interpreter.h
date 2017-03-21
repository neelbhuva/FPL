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
#include <map>

#if 0
struct dlist{
	string func_name;
	vector<string> formal_param;
	tree_node* func_body;
};
#endif

using namespace std;

void printmap(map<string,string>);
tree_node* getFuncBody(string);
bool inalist(string,map<string,string>);
string getFormalParamValue(string,map<string, string>);
//extern vector<struct dlist*> dl;

class Interpreter{
	public:
		int flag;
		//dlist is used to store information about DEFUN expression
		//It stores formal parameter list, function name and function body
		//struct dlist d_list;
		//dl is the list of all such dlist throughout the program
		//static struct dlist* dl[100];
		//static int i;

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
		tree_node* eval(tree_node*,map<string,string> = map<string,string>());
		bool isNumeric(tree_node*);
		bool in_array(const string&, const vector<string>&);
		void printSExpression(tree_node*);
		bool isList(tree_node*);
		void inorderPrint(tree_node*);
		bool allListOfLengthTwo(tree_node*);
		tree_node* COND_eval(tree_node*);
		Interpreter();
		void validate_defun_expression(tree_node*,vector<string>,vector<string>,vector<string>,vector<string>);
		vector<string> isListOfLiteralAtoms(tree_node*,vector<string>,vector<string>,vector<string>,vector<string>);
		void printdlist(tree_node*);
		bool isFuncNameInDlist(string);
		void validateFuncCall(tree_node*,string);
		map<string, string> evaluateActualList(tree_node*);
		vector<string> getFormalParam(string);
		tree_node* apply(string,tree_node*,map<string, string>);

};


#endif