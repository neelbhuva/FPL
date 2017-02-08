/* This code is written by Neelkumar Shailesh Bhuva
   as part of CSE 6341 (Foundations of Programming Languages) 
   project at the Ohio State University. 
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <sstream>
#include "interpreter.h"
#include <vector>

using namespace std;

int Interpreter::length(tree_node* s)
{
	if(!s)
		return 0;
	if(s->left == NULL and s->right == NULL)
		return 1;
	return length(s->left)+1+length(s->right);
}

tree_node* Interpreter::car(tree_node* s)
{
	if(!s or this->length(s) == 1)
	{
		//empty binary tree.
		throw("");
	}
	else
		return s->left;
}

tree_node* Interpreter::cdr(tree_node* s)
{
	if(!s or this->length(s) == 1)
	{
		//Undefined
		throw("");
	}
	else
		return s->right;
}

tree_node* Interpreter::cons(tree_node* s1, tree_node* s2)
{
	tree_node* temp = new tree_node();
	temp->value = "DUMMY";
	temp->left = s1;
	temp->right = s2;
	return temp;
}

tree_node* Interpreter::atom(tree_node* s)
{
	tree_node* temp = new tree_node();
	if(!s)
		throw("");
	else if(this->length(s) == 1)
	{
		//cout << "Atom\n";
		temp = this->createNode("T",NULL,NULL);
	}
	else if(s->left != NULL and s->right != NULL)
	{
		//cout << "Not an atom\n";
		temp = this->createNode("NIL",NULL,NULL);
		//cout << temp->value;
	}
	return temp;
}

tree_node* Interpreter::INT(tree_node* s)
{
	tree_node* temp = new tree_node();
	if(!s)
		throw("");
	if(this->length(s) == 1)
	{
		if(isNumeric(s))
			temp = this->createNode("NIL",NULL,NULL);
		else
			temp = this->createNode("T",NULL,NULL);
	}
	else if(this->length(s) > 1)
	{
		//cout << "Not an atom\n";
		temp = this->createNode("NIL",NULL,NULL);
		//cout << temp->value;
	}
	return temp;
}

tree_node* Interpreter::null(tree_node* s)
{
	tree_node* temp = new tree_node();
	if(!s)
		throw("");
	if(this->length(s) == 1 and s->value == "NIL")
	{
		temp = this->createNode("T",NULL,NULL);
	}
	else if(this->length(s) > 1)
	{
		temp = this->createNode("NIL",NULL,NULL);
	}
	return temp;
}


tree_node* Interpreter::eq(tree_node* s1,tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
		throw("");
	else
	{
		if(s1->value == s2->value)
			temp = this->createNode("T",NULL,NULL);
		else
			temp = this->createNode("NIL",NULL,NULL);
	}
	return temp;
}

tree_node* Interpreter::plus(tree_node* s1, tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
		throw("");
	if(!isNumeric(s1) or !isNumeric(s2))
		throw("");
	else
	{
		int s = atoi(s1->value.c_str()) + atoi(s2->value.c_str());
		ostringstream ss;
		ss << s;
		temp->value = ss.str();
	}
	return temp;
}

tree_node* Interpreter::minus(tree_node* s1, tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
		throw("");
	if(!isNumeric(s1) or !isNumeric(s2))
		throw("");
	else
	{
		int s = atoi(s1->value.c_str()) - atoi(s2->value.c_str());
		ostringstream ss;
		ss << s;
		temp->value = ss.str();
	}
	return temp;
}

tree_node* Interpreter::times(tree_node* s1, tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
		throw("");
	if(!isNumeric(s1) or !isNumeric(s2))
		throw("");
	else
	{
		int s = atoi(s1->value.c_str()) * atoi(s2->value.c_str());
		ostringstream ss;
		ss << s;
		temp->value = ss.str();
	}
	return temp;
}

tree_node* Interpreter::less(tree_node* s1,tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
		throw("");
	if(!isNumeric(s1) or !isNumeric(s2))
		throw("");
	else
	{
		if(atoi(s1->value.c_str()) < atoi(s2->value.c_str()))
			temp = this->createNode("T",NULL,NULL);
		else
			temp = this->createNode("NIL",NULL,NULL);
	}
	return temp;
}

tree_node* Interpreter::greater(tree_node* s1,tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
		throw("");
	if(!isNumeric(s1) or !isNumeric(s2))
		throw("");
	else
	{
		if(atoi(s1->value.c_str()) > atoi(s2->value.c_str()))
			temp = this->createNode("T",NULL,NULL);
		else
			temp = this->createNode("NIL",NULL,NULL);
	}
	return temp;
}

tree_node* Interpreter::eval(tree_node* s)
{
	vector<string> arithmetic {"PLUS", "MINUS","TIMES","LESS","GREATER"};
	vector<string> unary {"ATOM", "INT","NULL"};
	vector<string> carcdr {"CAR","CDR"};
	if(this->INT(s)->value == "T")
		return s;
	if(this->null(s)->value == "T")
		return s;
	if(s->value == "T" and this->length(s) == 1)
		return s;
	if(this->length(s) == 1)
		throw("");
	if(this->in_array(this->car(s)->value,arithmetic))
	{
		if(this->length(s) != 3)
			throw("");
				
	}


}

tree_node* Interpreter::createNode(string value, tree_node* left, tree_node* right)
{
	//cout << "Creating a new node : " << value << "\n";
	tree_node* temp = new tree_node();
	temp->value = value;
	temp->left = left;
	temp->right = right;
	//tree_node* temp1 = &temp;
	//cout << temp->value << "\n";
	return temp;
}

bool Interpreter::isNumeric(tree_node* s)
{
	string value = s->value; int i = 0;
	while (i < value.size())
	{
		//cout << value[i] << "\n";
		if(!isdigit(value[i]))
		{
			//cout << value[i] << " Not a number\n";
			return false;
		}
		i++;
	}
	if(i == value.size())
	{
		//cout << value << " Number\n";
		return true;
	}
}

bool Interpreter::in_array(const std::string &value, const std::vector<string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}