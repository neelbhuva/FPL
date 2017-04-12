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
#include "emptyListChecker.h"
#include <vector>
#include "common.h"
#include <map>

using namespace std;

//vector<struct dlist> dl;
//struct dlist* emptyListChecker::dl[100];
//int emptyListChecker::i = 0;
//vector<struct dlist*> emptyListChecker::dl = new vector<struct dlist*>[100];
emptyListChecker::emptyListChecker()
{
	this->flag = 0;
}

int emptyListChecker::length(tree_node* s)
{
	//cout << "In length\n";
	if(!s)
		return 0;
	if(s->left == NULL and s->right == NULL and s->value == "NIL")
		return 0;//empty list
	else if(s->left == NULL and s->right == NULL)
		return 1;
	return 1+length(s->right);
}

tree_node* emptyListChecker::car(tree_node* s)
{
	if(!s or s->left == NULL and s->right == NULL)
	{
		if(s->value == "NIL")
		{
			cout << "EMPTY LIST ERROR : car failed for List[>=0]\n";
			throw("");
		}
		//empty binary tree.
		cout << "ERROR : car failed, undefined input\n";
		throw("");
	}
	else if(length(s) > 0)
		return s->left;
	else
	{
		cout << "EMPTY LIST ERROR : car failed for List[>=0]\n"; throw("");
	}
}

tree_node* emptyListChecker::cdr(tree_node* s)
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

tree_node* emptyListChecker::cons(tree_node* s1, tree_node* s2)
{
	tree_node* temp = new tree_node();
	temp->value = "DUMMY";
	temp->left = s1;
	temp->right = s2;
	return temp;
}

tree_node* emptyListChecker::atom(tree_node* s)
{
	//cout << "In atom()";
	tree_node* temp = new tree_node();
	if(!s){ cout << "ERROR : atom function failed, empty input\n"; throw(""); }
	else if(s->left == NULL and s->right == NULL)
	{
		if(s->value == "NIL")
		{
			temp = this->createNode("F",NULL,NULL);
		}
		else
		{
			//cout << "Atom\n";
			temp = this->createNode("T",NULL,NULL);
		}
	}
	else if(s->left != NULL and s->right != NULL)
	{
		//cout << "Not an atom\n";
		temp = this->createNode("F",NULL,NULL);
		//cout << temp->value;
	}
	return temp;
}

tree_node* emptyListChecker::INT(tree_node* s)
{
	tree_node* temp = new tree_node();
	if(!s){ cout << "ERROR : int function failed, empty input\n"; throw(""); }
	if(s->left == NULL and s->right == NULL)
	{
		if(isNumeric(s))
			temp = this->createNode("T",NULL,NULL);
		else
			temp = this->createNode("F",NULL,NULL);
	}
	else if(s->left != NULL and s->right != NULL)
	{
		//cout << "Not an atom\n";
		temp = this->createNode("F",NULL,NULL);
		//cout << temp->value;
	}
	return temp;
}

tree_node* emptyListChecker::null(tree_node* s)
{
	//cout << "In null\n";
	tree_node* temp = new tree_node();
	if(!s)
		throw("");
	if(s->left == NULL and s->right == NULL and s->value == "NIL")
	{
		temp = this->createNode("T",NULL,NULL);
	}
	else
	{
		temp = this->createNode("F",NULL,NULL);
	}
	return temp;
}


tree_node* emptyListChecker::eq(tree_node* s1,tree_node* s2)
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
		{	
			temp = this->createNode("T",NULL,NULL); 
			//cout << "s1 and s2 are equal\n";
		}
		else
			temp = this->createNode("NIL",NULL,NULL);
	}
	return temp;
}

tree_node* emptyListChecker::plus(tree_node* s1, tree_node* s2)
{
	//cout << "In plus\n";
	tree_node* temp = new tree_node();
	if(!s1 or !s2){cout << "ERROR: Plus failed, s1 or s2 is empty"; throw("");}
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: Plus failed " << s1->value << " or " << s2->value << " is not numeric\n"; throw("");}
	else
	{
		int s = atoi(s1->value.c_str()) + atoi(s2->value.c_str());
		ostringstream ss;
		ss << s;
		temp->value = ss.str();
	}
	return temp;
}

tree_node* emptyListChecker::minus(tree_node* s1, tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: minus failed " << s1->value << " or " << s2->value << " is not numeric\n"; throw("");}
	else
	{
		int s = atoi(s1->value.c_str()) - atoi(s2->value.c_str());
		ostringstream ss;
		ss << s;
		temp->value = ss.str();
	}
	return temp;
}

tree_node* emptyListChecker::times(tree_node* s1, tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: times failed " << s1->value << " or " << s2->value << " is not numeric\n"; throw("");}
	else
	{
		int s = atoi(s1->value.c_str()) * atoi(s2->value.c_str());
		ostringstream ss;
		ss << s;
		temp->value = ss.str();
	}
	return temp;
}

tree_node* emptyListChecker::less(tree_node* s1,tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: less failed " << s1->value << " or " << s2->value << " is not numeric\n"; throw("");}
	else
	{
		if(atoi(s1->value.c_str()) < atoi(s2->value.c_str()))
			temp = this->createNode("T",NULL,NULL);
		else
			temp = this->createNode("NIL",NULL,NULL);
	}
	return temp;
}

tree_node* emptyListChecker::greater(tree_node* s1,tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "ERROR: greater failed " << s1->value << " or " << s2->value << " is not numeric\n"; throw("");}
	else
	{
		if(atoi(s1->value.c_str()) > atoi(s2->value.c_str()))
			temp = this->createNode("T",NULL,NULL);
		else
			temp = this->createNode("NIL",NULL,NULL);
	}
	return temp;
}

tree_node* emptyListChecker::eval(tree_node* s,map<string,tree_node*> alist)
{
	//cout << "In eval\n";
	string art[] = {"PLUS","LESS"};
	string un[] = {"ATOM", "INT","NULL"};
	string cc[] = {"CAR","CDR"};
	string oth[] = {"T","F","CONS","COND","EQ"};

	vector<string> arithmetic (art,art+2);
	vector<string> unary (un,un+3);
	vector<string> carcdr (cc,cc+2);
	vector<string> other (oth,oth+5);

	tree_node* temp = new tree_node();
	//cout << "In eval : "; printmap(alist); cout << endl;
	//cout << alist.empty() << "\n";
	
	if(isNumeric(s)) //AnyNat
	{
		//cout << s->value << " ";
		return s;
	}
	else if(s->value == "NIL")//List[>=0]
		return s;
	else if((s->value == "T" or s->value == "F") and this->length(s) == 1)
		return s;
	else if(s->left == NULL and s->right == NULL){ cout << "EMPTY LIST ERROR: eval failed, " << s->value << " not recognized\n"; throw("");}
	
	string car_value = this->car(s)->value;
	//cout << "car_value : " << car_value << "\n";
	if(this->in_array(car_value,arithmetic))
	{
		//cout << "Arithmetic\n";
		if(this->length(s) != 3){ cout << "ERROR : Length(s) not equal to 3 for " << car_value << "\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		tree_node* s2 = this->car(this->cdr(this->cdr(s)));
		//cout << car_value << " " << s1->value << " " << s2->value << "\n";
		if(!isNumeric(this->eval(s1,alist)) or !isNumeric(this->eval(s2,alist)))
		{	
			cout << "ERROR : " << this->eval(s1,alist)->value << " or " << this->eval(s2,alist)->value << " not numeric, cannot perform " << car_value << " operation\n"; 
			throw("");
		}
     	if(car_value == "PLUS"){ temp = plus(this->eval(s1,alist),this->eval(s2,alist)); }
     	else if(car_value == "MINUS"){temp = minus(this->eval(s1,alist),this->eval(s2,alist)); }
      	else if(car_value == "TIMES"){temp = times(this->eval(s1,alist),this->eval(s2,alist)); }
      	else if(car_value == "LESS"){temp = less(this->eval(s1,alist),this->eval(s2,alist)); }
      	else if(car_value == "GREATER"){temp = greater(this->eval(s1,alist),this->eval(s2,alist)); }
      	else{cout << " ERROR : Could not map input to the right function\n"; throw("");}
   					
	}
	else if(this->in_array(car_value,unary))
	{
		if(this->length(s) != 2){ cout << "ERROR : Length(s) not equal to 2, cannot perform unary\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		//cout << car_value << " " << s1->value << "\n";
     	if(car_value == "ATOM") {temp = atom(this->eval(s1,alist));}
		else if(car_value == "INT") {temp = INT(this->eval(s1,alist));}      		
		else if(car_value == "NULL") {temp = null(this->eval(s1,alist));}
      	else{cout << "ERROR : Could not map input to the right function\n"; throw("");}
	}
	else if(this->in_array(car_value,carcdr))
	{
		if(this->length(s) != 2){ cout << "ERROR : Length(s) not equal to 2,cannot perform "<< car_value << "\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		if(this->atom(this->eval(s1,alist))->value == "T")
		{
			cout << "ERROR : Atom found after performing eval, cannot perform " << car_value << " on ";
			this->printSExpression(s1); cout << " in "; this->printSExpression(s); cout << endl;  
			throw("");
		}
     	if(car_value == "CAR") {temp = car(this->eval(s1,alist));}
     	else if(car_value == "CDR") {temp = cdr(this->eval(s1,alist));}
     	else{cout << "ERROR : Could not map input to the right function\n"; throw("");}    	
	}
	else if(car_value == "EQ")
	{
		if(this->length(s) != 3){ cout << "ERROR : Length(s) not equal to 3, cannot perform EQ\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		tree_node* s2 = this->car(this->cdr(this->cdr(s)));
		//cout << car_value << " " << s1->value << " " << s2->value << "\n";
		if(this->atom(this->eval(s1,alist))->value == "NIL" or this->atom(this->eval(s2,alist))->value == "NIL")
		{
			cout << "ERROR : Atom not found after performing eval, cannot perform " << car_value << "\n";
			throw("");
		}
		temp = this->eq(this->eval(s1,alist),this->eval(s2,alist));
	}
	else if(car_value == "CONS")
	{
		if(this->length(s) != 3){ cout << "ERROR : Length(s) not equal to 3, cannot perform cons\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		tree_node* s2 = this->car(this->cdr(this->cdr(s)));
		temp = this->cons(this->eval(s1,alist),this->eval(s2,alist));
	}
	else if(car_value == "QUOTE")
	{
		//cout << "In Quote\n";
		if(this->length(s) != 2){ cout << "ERROR : Length(s) not equal to 2,cannot do QUOTE\n"; throw("");}
		//this->printSExpression(s);
		temp = this->car(this->cdr(s));
		//cout << this->length(temp);
		//this->printSExpression(temp);
		//printlast(temp);
	}
	else if(car_value == "COND")
	{
		//check if any si is not a list or if it is a list then whether length == 2
		if(allListOfLengthTwo(s))
		{
			//cout << "Calling COND_eval\n";
			temp = this->COND_eval(s,alist);
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
		cout << "ERROR: car(s) : " << car_value << " cannot be mapped to valid operation\n";
		throw("");
	}
	//cout << "eval done\n";
	return temp;
}

tree_node* emptyListChecker::COND_eval(tree_node* s,map<string,tree_node*> alist)
{
	//s includes the COND node
	tree_node* temp = s;
	temp = this->cdr(temp);
	while(temp->left != NULL)
	{
		if(this->eval(this->car(this->car(temp)),alist)->value != "NIL")
		{
			//cout << "True COndition found\n";
			return this->eval(this->car(this->cdr(this->car(temp))),alist);
		}
		else
		{
			//cout << "False COndition found\n";
			temp = this->cdr(temp);
		}
	}
	if(temp->left == NULL)
	{
		cout << "ERROR : None of the bi's are T in COND\n";
		throw("");
	}
}

vector<string> emptyListChecker::isListOfLiteralAtoms(tree_node* s1,vector<string> arithmetic,vector<string> unary,vector<string> carcdr,vector<string> other)
{
	//cout << "In isListOfLiteralAtoms\n";

	tree_node* temp = s1;
	vector<string> formal_param;
	string param;
	while(temp->left != NULL)
	{
		param = this->car(temp)->value;
		//cout << "param : " << param << "\n"; 
		if(this->in_array(param,arithmetic) || this->in_array(param,unary) || this->in_array(param,carcdr) || this->in_array(param,other))
		{
			cout << "ERROR : Formal parameter " << param << " cannot be the same as built in function name\n";
			throw("");
		}
		if(this->in_array(param,formal_param))
		{
			cout << "ERROR : Cannot repeat formal parameters in s1 (DEFUN F s1 s2)\n";
			throw("");
		}		
		if(isupper(param[0]))
		{
			formal_param.push_back(param);
			temp = this->cdr(temp);
		}
		else
		{
			cout << "ERROR : Formal parameters is not a list of literal atoms\n";
			throw("");
		}
	}
	return formal_param;
}

bool emptyListChecker::isFuncNameInDlist(string F)
{
	//cout << "Looking for function in dlist...\n";
	for(int i = 0; i < dl.size(); i++)
	{
		if(dl[i].func_name == F)
			return true;
	}
	return false;
}

void emptyListChecker::printSExpression(tree_node* s)
{
	//cout << "In printSExpression...\n";
	if(this->atom(s)->value == "T")
	{
		cout << s->value;
		if(flag == 0)
			cout << " ";
		return;
	}
	else
	{
		cout << "(";
		while(s->right->right != NULL)
		{
			flag = 0;
			this->printSExpression(this->car(s));
			s = this->cdr(s);
		}
		if(s->right->right == NULL)
		{
			flag = 1;
			this->printSExpression(this->car(s));
			if(this->cdr(s)->value == "NIL")
				cout << ")";
			else
			{
				cout << " . ";
				this->printSExpression(this->cdr(s));
				cout << ")";
			}
		}
	}
}

tree_node* emptyListChecker::createNode(string value, tree_node* left, tree_node* right)
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

bool emptyListChecker::isNumeric(tree_node* s)
{
	//cout << "In isNumeric\n";
	string value = s->value; int i = 0;
	/*cout << "value : " << value << "\n";
	int number; 
	if((number = stoi(value)) == 0)
	{

	}
	cout << "Number is : " << number << "\n";
	if(number < 0)
	{
		number = -1 * number;
		value = to_string(number);
		//cout << "Number string is : " << value << "\n";
	}*/
	while (i < value.size())
	{
		//cout << value[i] << "\n";
		if(value[i] == '-' and value.size() > 1)
		{
			i++;
			continue;
		}
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

bool emptyListChecker::in_array(const std::string &value, const std::vector<string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}

bool emptyListChecker::isList(tree_node* s)
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

void emptyListChecker::inorderPrint(tree_node* node)
{
	if(node)
	{
		this->inorderPrint(node->left);
		cout << node->value << " ";
		this->inorderPrint(node->right);
	}
}

bool emptyListChecker::allListOfLengthTwo(tree_node* s)
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
