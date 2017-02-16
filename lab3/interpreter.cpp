/* This code is written by Neelkumar Shailesh Bhuva
   as part of CSE 6341 (Foundations of Programming Languages) 
   project at the Ohio State University. 
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include "interpreter.h"
#include <vector>

using namespace std;

int Interpreter::length(tree_node* s)
{
	if(!s)
		return 0;
	if(s->left == NULL and s->right == NULL and s->value == "NIL")
		return 0;//empty list
	else if(s->left == NULL and s->right == NULL)
		return 1;
	return 1+length(s->right);
}

tree_node* Interpreter::car(tree_node* s)
{
	if(!s or s->left == NULL and s->right == NULL)
	{
		//empty binary tree.
		cout << "ERROR : car failed, undefined input\n";
		throw("");
	}
	else
		return s->left;
}

tree_node* Interpreter::cdr(tree_node* s)
{
	if(!s or s->left == NULL and s->right == NULL)
	{
		//Undefined
		cout << "ERROR : cdr failed, undefined input\n";
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
	if(!s){ cout << "ERROR : atom function failed, empty input\n"; throw(""); }
	else if(s->left == NULL and s->right == NULL)
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
	if(!s){ cout << "ERROR : int function failed, empty input\n"; throw(""); }
	if(s->left == NULL and s->right == NULL)
	{
		if(isNumeric(s))
			temp = this->createNode("T",NULL,NULL);
		else
			temp = this->createNode("NIL",NULL,NULL);
	}
	else if(s->left != NULL and s->right != NULL)
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
	if(s->left == NULL and s->right == NULL and s->value == "NIL")
	{
		temp = this->createNode("T",NULL,NULL);
	}
	else if(s->left != NULL and s->right != NULL)
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
	if(s1->left != NULL and s1->right != NULL or s2->left != NULL and s2->right != NULL) //undefined
	{
		cout << "ERROR : eq failed,\n";
		throw("");
	}
	else
	{
		if(s1->value == s2->value)
			{temp = this->createNode("T",NULL,NULL); cout << "s1 and s2 are equal\n";}
		else
			temp = this->createNode("NIL",NULL,NULL);
	}
	return temp;
}

tree_node* Interpreter::plus(tree_node* s1, tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2){cout << "ERROR: Plus failed, s1 or s2 is empty"; throw("");}
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: Plus failed " << s1->value << "or" << s2->value << "is not numeric\n"; throw("");}
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
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: minus failed " << s1->value << "or" << s2->value << "is not numeric\n"; throw("");}
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
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: times failed " << s1->value << "or" << s2->value << "is not numeric\n"; throw("");}
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
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: less failed " << s1->value << "or" << s2->value << "is not numeric\n"; throw("");}
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
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: greater failed " << s1->value << "or" << s2->value << "is not numeric\n"; throw("");}
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
	tree_node* temp = new tree_node();
	if(this->INT(s)->value == "T")
		return s;
	else if(this->null(s)->value == "T")
		return s;
	else if(s->value == "T" and this->length(s) == 1)
		return s;
	else if(this->atom(s)->value == "T"){ cout << "ERROR: eval failed, " << s->value << " not recognized\n"; throw("");}
	string car_value = this->car(s)->value;
	//cout << "car_value : " << car_value << "\n";
	if(this->in_array(car_value,arithmetic))
	{
		//cout << "Arithmetic\n";
		if(this->length(s) != 3){ cout << "ERROR : Length(s) not equal to 3\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		tree_node* s2 = this->car(this->cdr(this->cdr(s)));
		cout << car_value << " " << s1->value << " " << s2->value << "\n";
		if(!isNumeric(this->eval(s1)) or !isNumeric(this->eval(s2)))
		{	
			cout << "ERROR : Not numeric, cannot perform arithmetic operation\n"; 
			throw("");
		}
     	if(car_value == "PLUS"){ temp = plus(this->eval(s1),this->eval(s2)); }
     	else if(car_value == "MINUS"){temp = minus(this->eval(s1),this->eval(s2)); }
      	else if(car_value == "TIMES"){temp = times(this->eval(s1),this->eval(s2)); }
      	else if(car_value == "LESS"){temp = less(this->eval(s1),this->eval(s2)); }
      	else if(car_value == "GREATER"){temp = greater(this->eval(s1),this->eval(s2)); }
      	else{cout << "Could not map input to the right function\n"; throw("");}
   					
	}
	else if(this->in_array(car_value,unary))
	{
		if(this->length(s) != 2){ cout << "ERROR : Length(s) not equal to 2, cannot perform unary\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		cout << car_value << " " << s1->value << "\n";
     	if(car_value == "ATOM") {temp = atom(this->eval(s1));}
		else if(car_value == "INT") {temp = INT(this->eval(s1));}      		
		else if(car_value == "NULL") {temp = null(this->eval(s1));}
      	else{cout << "Could not map input to the right function\n"; throw("");}
	}
	else if(this->in_array(car_value,carcdr))
	{
		if(this->length(s) != 2){ cout << "ERROR : Length(s) not equal to 2,cannot perform car or cdr\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		if(this->atom(this->eval(s1))->value == "T")
			throw("");
     	if(car_value == "CAR") {temp = car(this->eval(s1));}
     	else if(car_value == "CDR") {temp = cdr(this->eval(s1));}
     	else{cout << "Could not map input to the right function\n"; throw("");}
     	
	}
	else if(car_value == "EQ")
	{
		if(this->length(s) != 3){ cout << "ERROR : Length(s) not equal to 3, cannot perform EQ\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		tree_node* s2 = this->car(this->cdr(this->cdr(s)));
		cout << car_value << " " << s1->value << " " << s2->value << "\n";
		if(this->atom(this->eval(s1))->value == "NIL" or this->atom(this->eval(s1))->value == "NIL")
			throw("");
		temp = this->eq(this->eval(s1),this->eval(s2));
	}
	else if(car_value == "CONS")
	{
		if(this->length(s) != 3){ cout << "ERROR : Length(s) not equal to 3, cannot perform cons\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		tree_node* s2 = this->car(this->cdr(this->cdr(s)));
		temp = this->cons(this->eval(s1),this->eval(s2));
	}
	else if(car_value == "QUOTE")
	{
		if(this->length(s) != 2){ cout << "ERROR : Length(s) not equal to 2,cannot do QUOTE\n"; throw("");}
		temp = this->car(this->cdr(s));
	}
	else if(car_value == "COND")
	{
		//check if any si is not a list or if it is a list then whether length == 2
		if(allListOfLengthTwo(s))
		{
			cout << "Calling COND_eval\n";
			temp = this->COND_eval(s);
			//cout << temp->value << "\n";
		}
		else
		{
			cout << "ERROR in COND : Some si in (COND s1 s2 ...sn) is not a list or has length != 2\n";
			throw("");
		}

	}
	else
	{
		cout << "ERROR: No match for car(s)\n";
		throw("");
	}
	return temp;
}

tree_node* Interpreter::COND_eval(tree_node* s)
{
	//s includes the COND node
	tree_node* temp = s;
	temp = this->cdr(temp);
	while(temp->left != NULL)
	{
		if(this->eval(this->car(this->car(temp)))->value != "NIL")
		{
			cout << "True COndition found\n";
			return this->eval(this->car(this->cdr(this->car(temp))));
		}
		else
		{
			cout << "False COndition found\n";
			temp = this->cdr(temp);
		}
	}
	if(temp->left == NULL)
	{
		cout << "ERROR : None of the bi's are T in COND\n";
		throw("");
	}
}

/*void Interpreter::printSExpression(tree_node* s)
{
	if(s->left == NULL and s->right == NULL)
		cout << s->value;
	else if(s->left->left == NULL and s->right->right == NULL and s->right->value == "NIL")
	{
		this->printSExpression(s->left);
		cout << ")" << "\n";
	}
	else if(s->left->left == NULL and s->right->right == NULL  and s->right->value != "NIL")
	{
		this->printSExpression(s->left);
		cout << " . ";
		this->printSExpression(s->right);
		cout << ")";
	}
	else
	{
		cout << "(";
		this->printSExpression(s->left);
		this->printSExpression(s->right);
	}
}*/

void Interpreter::printSExpression(tree_node* s)
{
	if(this->atom(s)->value == "T")
	{
		cout << s->value << " ";
		return;
	}
	else
	{
		cout << "(";
		while(s->right->right != NULL)
		{
			this->printSExpression(this->car(s));
			s = this->cdr(s);
		}
		if(s->right->right == NULL)
		{
			this->printSExpression(this->car(s));
			if(this->cdr(s)->value == "NIL")
				cout << ")" << "\n";
			else
			{
				cout << " . ";
				this->printSExpression(this->cdr(s));
				cout << ")\n";
			}
		}
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

bool Interpreter::isList(tree_node* s)
{
	//s is a list if and only if the right most leaf node is a special literal atom NIL
	tree_node* temp = s;
	if(!temp)
		return false;
	while(temp->right != NULL and temp->left != NULL)
	{
		temp = temp->right;
	}
	if(temp->right == NULL and temp->left == NULL and temp->value == "NIL")
		return true;
	else
		return false;
}

void Interpreter::inorderPrint(tree_node* node)
{
	if(node)
	{
		this->inorderPrint(node->left);
		cout << node->value << " ";
		this->inorderPrint(node->right);
	}
}

bool Interpreter::allListOfLengthTwo(tree_node* s)
{
	//input s has COND as car(s), check for the rest of the tree whether si are list and length == 2 
	if(this->length(s) < 2)
		return false;
	tree_node* temp = s;
	temp = this->cdr(temp);
	while(temp->left != NULL)
	{
		//cout << length(car(temp)) << "\n";
		if(isList(this->car(temp)) and length(car(temp)) == 2)
		{
			temp = this->cdr(temp);
		}
		else
			return false;
	}
	return true;
	
}