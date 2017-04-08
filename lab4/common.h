#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include "binaryTree.h"
using namespace std;

struct dlist{
	string func_name;
	vector<string> formal_param;
	tree_node* func_body;
};

extern vector<struct dlist> dl;

#endif