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
#include "staticChecker.h"
#include <vector>
#include "common.h"
#include <map>

using namespace std;

vector<struct dlist> dl;
//struct dlist* staticChecker::dl[100];
//int staticChecker::i = 0;
//vector<struct dlist*> staticChecker::dl = new vector<struct dlist*>[100];
staticChecker::staticChecker()
{
	this->flag = 0;
}

int staticChecker::length(tree_node* s)
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

tree_node* staticChecker::car(tree_node* s)
{
	if(!s or s->left == NULL and s->right == NULL)
	{
		if(s->value == "NIL")
		{
			//well typed
			tree_node* t = createNode("1",NULL,NULL);
			return t;
		}	
		//empty binary tree.
		cout << "ERROR : car failed, undefined input\n";
		throw("");
	}
	else
		return s->left;
}
/*
tree_node* staticChecker::car(tree_node* s)
{
	//cout << "In car\n";
	if(!s or s->left == NULL and s->right == NULL)
	{
		if(s->value == "NIL")
		{
			//well typed
			tree_node* t = createNode("List(Nat)",NULL,NULL);
			return t;
		}
		else
		{
			//empty binary tree.
			cout << "TYPE ERROR : car failed, undefined input\n";
			throw("");
		}	
	}
	else if(isList(s))
		return s->left;
	else
	{
		cout << "TYPE ERROR : s in (CAR s) is not List(Nat)\n";
		throw("");
	}
}
*/
tree_node* staticChecker::cdr(tree_node* s)
{
	if(!s or s->left == NULL and s->right == NULL)
	{
		//Undefined
		cout << "TYPE ERROR : cdr failed, input is not List(Nat)\n";
		throw("");
	}
	else
		return s->right;
}

tree_node* staticChecker::cdr_type_check(tree_node* s)
{
	if(!s or s->left == NULL and s->right == NULL)
	{
		if(s->value == "NIL")
		{
			tree_node* t = createNode("NIL",NULL,NULL);
			return t;
		}
		//Undefined
		cout << "TYPE ERROR : cdr failed, input is not List(Nat)\n";
		throw("");
	}
	else if(isList(s))
		return s->right;
	else
	{
		cout << "TYPE ERROR : cdr failed, input is not List(Nat)\n";
		throw("");
	}
}

tree_node* staticChecker::cons(tree_node* s1, tree_node* s2)
{
	if(!isNumeric(s1) or !isList(s2))
	{
		cout << "TYPE ERROR : cons failed\n"; throw("");
	}
	//cout << "In cons\n"; cout << s1->value << "-" << s2->value << endl;
	tree_node* temp = new tree_node();
	temp->value = "DUMMY";
	temp->left = s1;
	temp->right = s2;
	//this->printSExpression(temp);
	//this->inorderPrint(temp);
	//cout << "Cons done\n";
	return temp;
}

tree_node* staticChecker::atom(tree_node* s)
{
	//cout << "In atom()\n";
	tree_node* temp = new tree_node();
	if(!s){ cout << "ERROR : atom function failed, empty input\n"; throw(""); }
	else if(s->left == NULL and s->right == NULL)
	{
		if(s->value == "T" or s->value == "F" or isNumeric(s))
		{
			//Input is fine, do nothing.
			temp = this->createNode("T",NULL,NULL);
		}
		else if(s->value =="NIL")
		{
			//Input is fine, do nothing.
			temp = this->createNode("F",NULL,NULL);
		}
		else
		{
			//cout << "H\n";
			cout << "TYPE ERROR : s :" << s->value <<  " in (ATOM s) is not recognized\n";
			throw("");
		}
		//cout << "Atom\n";
		//temp = this->createNode("T",NULL,NULL);
	}
	else if(isList(s))
	{
		//it is a List(Nat). Expression is valid or well typed.
		//cout << "Not an atom\n";
		temp = this->createNode("F",NULL,NULL);
		//cout << temp->value;
	}
	else
	{
		cout << "TYPE ERROR : s " << s->value << " in (ATOM s) is not recognized\n";
		throw("");
	}
	return temp;
}

tree_node* staticChecker::atom1(tree_node* s)
{
	//cout << "In atom1()\n";
	tree_node* temp = new tree_node();
	if(!s){ cout << "ERROR : atom function failed, empty input\n"; throw(""); }
	else if(s->left == NULL and s->right == NULL)
	{
		//cout << "Atom\n";
		temp = this->createNode("T",NULL,NULL);
	}
	else if(isList1(s))
	{
		//it is a List(Nat). Expression is valid or well typed.
		//cout << "Not an atom\n";
		temp = this->createNode("F",NULL,NULL);
		//cout << temp->value;
	}
	else
	{
		cout << "TYPE ERROR : s " << s->value << " in (ATOM s) is not recognized\n";
		throw("");
	}
	return temp;
}

tree_node* staticChecker::INT(tree_node* s)
{
	tree_node* temp = new tree_node();
	if(!s){ cout << "ERROR : int function failed, empty input\n"; throw(""); }
	if(s->left == NULL and s->right == NULL)
	{
		if(isNumeric(s) or s->value == "T" or s->value == "F" or s->value == "NIL")
			temp = this->createNode("T",NULL,NULL);
		else
		{
			cout << "TYPE ERROR : s : " << s->value << " in (INT s) is not recognized\n";
			throw("");
		}
	}
	else if(isList(s))
	{
		//cout << "Not an atom\n";
		temp = this->createNode("F",NULL,NULL);
		//cout << temp->value;
	}
	else
	{
		cout << "TYPE ERROR : s : " << s->value << " in (INT s) is not recognized\n";
		throw("");
	}
	return temp;
}

tree_node* staticChecker::null(tree_node* s)
{
	//cout << "In null\n";
	tree_node* temp = new tree_node();
	if(!s)
		throw("");
	if(s->left == NULL and s->right == NULL and s->value == "NIL")
	{
		//it is empty List(Nat)
		temp = this->createNode("T",NULL,NULL);
	}
	else if(isList(s))
	{
		temp = this->createNode("F",NULL,NULL);
	}
	else
	{
		cout << "TYPE ERROR : s : " << " in (NULL s) is not List(Nat)\n";
		throw("");
	}
	return temp;
}


tree_node* staticChecker::eq(tree_node* s1,tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	if(s1->left != NULL and s1->right != NULL or s2->left != NULL and s2->right != NULL) //undefined
	{
		cout << "ERROR : eq failed,input is not nat\n";
		throw("");
	}
	else
	{
		if(!isNumeric(s1) or !isNumeric(s2))
		{
			cout << "TYPE ERROR : EQ failed, input is not nat\n"; throw("");
		}
		if(s1->value == s2->value)
		{	
			temp = this->createNode("T",NULL,NULL); 
			//cout << "s1 and s2 are equal\n";
		}
		else
			temp = this->createNode("F",NULL,NULL);
	}
	return temp;
}

tree_node* staticChecker::plus(tree_node* s1, tree_node* s2)
{
	//cout << "In plus\n";
	tree_node* temp = new tree_node();
	if(!s1 or !s2){cout << "TYPE ERROR: Plus failed, s1 or s2 is empty"; throw("");}
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

tree_node* staticChecker::minus(tree_node* s1, tree_node* s2)
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

tree_node* staticChecker::times(tree_node* s1, tree_node* s2)
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

tree_node* staticChecker::less(tree_node* s1,tree_node* s2)
{
	tree_node* temp = new tree_node();
	if(!s1 or !s2)
		throw("");
	//if(this->length(s1) > 1 or this->length(s2) > 2) //undefined
	//	throw("");
	if(!isNumeric(s1) or !isNumeric(s2)){cout << "TYPE ERROR: less failed " << s1->value << " or " << s2->value << " is not numeric\n"; throw("");}
	else
	{
		if(atoi(s1->value.c_str()) < atoi(s2->value.c_str()))
			temp = this->createNode("T",NULL,NULL);
		else
			temp = this->createNode("F",NULL,NULL);
	}
	return temp;
}

tree_node* staticChecker::greater(tree_node* s1,tree_node* s2)
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

tree_node* staticChecker::eval(tree_node* s)
{
	//cout << "In eval\n";
	string art[] = {"PLUS","LESS"};
	string un[] = {"ATOM", "INT","NULL"};
	string cc[] = {"CAR","CDR"};
	string oth[] = {"NIL","CONS","COND","EQ"};
	string boolea[] = {"T","F"};

	vector<string> arithmetic (art,art+2);
	vector<string> unary (un,un+3);
	vector<string> carcdr (cc,cc+2);
	vector<string> other (oth,oth+4);
	vector<string> boolean (boolea,boolea+2);

	tree_node* temp = new tree_node();
	//cout << "In eval : "; printmap(); cout << endl;
	//cout << .empty() << "\n";
	
	if(isNumeric(s))
	{
		//cout << s->value << " ";
		return s;
	}
	else if(s->value == "NIL")
		return s;
	else if((s->value == "T" or s->value == "F") and this->length(s) == 1)
	{ 	cout << "";	return s; }
	else if(s->left == NULL and s->right == NULL){ cout << "TYPE ERROR: " << s->value << " not recognized\n"; throw("");}
	
	string car_value = this->car(s)->value;
	//string car_value = s->left->value;
	//cout << "car_value : " << car_value << "\n";
	if(this->in_array(car_value,arithmetic))
	{
		//cout << "Arithmetic\n";
		if(this->length(s) != 3){ cout << "TYPE ERROR : Length(s) not equal to 3 for " << car_value << "\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		tree_node* s2 = this->car(this->cdr(this->cdr(s)));
		//cout << car_value << " " << s1->value << " " << s2->value << "\n";
		if(!isNumeric(this->eval(s1)) or !isNumeric(this->eval(s2)))
		{	
			cout << "TYPE ERROR : " << this->eval(s1)->value << " or " << this->eval(s2)->value << " not numeric, cannot perform " << car_value << " operation\n"; 
			throw("");
		}
     	if(car_value == "PLUS"){ temp = plus(this->eval(s1),this->eval(s2)); }
     	else if(car_value == "MINUS"){temp = minus(this->eval(s1),this->eval(s2)); }
      	else if(car_value == "TIMES"){temp = times(this->eval(s1),this->eval(s2)); }
      	else if(car_value == "LESS"){temp = less(this->eval(s1),this->eval(s2)); }
      	else if(car_value == "GREATER"){temp = greater(this->eval(s1),this->eval(s2)); }
      	else{cout << " ERROR : Could not map input to the right function\n"; throw("");}
   					
	}
	else if(this->in_array(car_value,unary))
	{
		if(this->length(s) != 2){ cout << "TYPE ERROR : Length(s) not equal to 2, cannot perform unary\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		//cout << car_value << " " << s1->value << "\n";
     	if(car_value == "ATOM") {temp = atom(this->eval(s1));}
		else if(car_value == "INT") {temp = INT(this->eval(s1));}      		
		else if(car_value == "NULL") {temp = null(this->eval(s1));}
      	else{cout << "ERROR : Could not map input to the right function\n"; throw("");}
	}
	else if(this->in_array(car_value,carcdr))
	{
		if(this->length(s) != 2){ cout << "ERROR : Length(s) not equal to 2,cannot perform "<< car_value << "\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		if(this->atom(this->eval(s1))->value == "T")
		{
			cout << "TYPE ERROR : Atom found, cannot perform " << car_value; cout << endl;  
			throw("");
		}
     	if(car_value == "CAR") {temp = car(this->eval(s1));}
     	else if(car_value == "CDR") {temp = cdr_type_check(this->eval(s1));}
     	else{cout << "ERROR : Could not map input to the right function\n"; throw("");}    	
	}
	else if(car_value == "EQ")
	{
		if(this->length(s) != 3){ cout << "ERROR : Length(s) not equal to 3, cannot perform EQ\n"; throw("");}
		tree_node* s1 = this->car(this->cdr(s));
		tree_node* s2 = this->car(this->cdr(this->cdr(s)));
		//cout << car_value << " " << s1->value << " " << s2->value << "\n";
		if(this->atom(this->eval(s1))->value == "F" or this->atom(this->eval(s2))->value == "F")
		{
			cout << "ERROR : Atom not found after performing eval, cannot perform " << car_value << "\n";
			throw("");
		}
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
		cout << "ERROR: car(s) : " << car_value << " cannot be mapped to valid operation\n";
		//this->printSExpression(s);
		throw("");
	}
	//cout << "eval done\n";
	return temp;
}

void printlast(tree_node* s)
{
	while(s->left != NULL)
	{
		cout << s->left->value;
		s = s->right;
	}
	cout << "Last : " << s->value;
}


/*{
	tree_node* temp = new tree_node();
	if(this->null(s)->value == "T")
		temp->value = "NIL";
	else 
		temp = this->cons(this->eval(this->car(s)),this->evlist(this->cdr(s)));
	return temp;
}*/

//same as getval(x,z)
/*tree_node* getFormalParamValue(string param, map<string,tree_node*> )
{
	for(map<string,tree_node*>::iterator it = .begin(); it != .end(); ++it)
	{
    	if(it->first == param)
    	{
    		tree_node* temp = new tree_node();
    		temp = it->second;
    		return temp;
    	}
	}
}*/

//same as bound(x,z)
/*bool in(string param, map<string,tree_node*> )
{
	//cout << "In in\n";
	//printmap();
	//cout << param << "\n";
	for(map<string,tree_node*>::iterator it = .begin(); it != .end(); ++it)
	{
		//cout << "Compare " << param << " with " << it->first << "\n"; 
    	if(it->first == param)
    	{
    		//cout << "Found : " << param << endl;;
    		return true;
    	}
	}
	return false;
}*/

/*tree_node* staticChecker::apply(string F,tree_node* s, map<string,tree_node*> )
{
	//s is actual parameter list.
	//cout << "In apply : " << F << " " << .empty() <<  " ";
	tree_node* func_body = getFuncBody(F);
	//cout << "Function body : "; this->printSExpression(func_body); cout << "\n";
	return this->eval(func_body,this->addpairs(getFormalParam(F),s,));
}

map<string,tree_node*> staticChecker::addpairs(vector<string> formal_param, tree_node* actual_values, map<string,tree_node*> )
{
	tree_node* temp = actual_values;
	for(int i = 0; i < formal_param.size(); i++)
	{
		[formal_param[i]] = this->car(temp);
		temp = this->cdr(temp);
	}
	return ;
}*/

tree_node* getFuncBody(string F)
{
	for(int i = 0; i < dl.size(); i++)
	{
		if(dl[i].func_name == F)
			return dl[i].func_body;
	}
} 

/*void printmap(map<string,tree_node*> )
{
	for(map<string,tree_node*>::iterator it = .begin(); it != .end(); ++it)
	{
    	cout << it->first << " => " << it->second->value << ' ';
	}
    cout << "\n";
}*/

tree_node* staticChecker::COND_eval(tree_node* s)
{
	//s includes the COND node
	tree_node* temp = s;
	int flag = 0;
	tree_node* result;
	string type;
	temp = this->cdr(temp);
	if(length(temp) < 1)
	{
		cout << "TYPE ERROR : COND failed, number of inputs should be >= 1\n";
		throw("");
	}
	int i = 0;
	while(temp->left != NULL and i <= length(temp))
	{
		//cout << i << endl;
		tree_node* e = this->car(this->cdr(this->car(temp)));
		if(i == 0)
		{
			type = this->getType(e); 
			//cout << "Type: " << type << "\n";
		}
		if(i > 0)
		{
			string ty = this->getType(e);
			//cout << "Type: " << ty<< "\n";
			if(ty != type)
			{
				cout << "TYPE ERROR : COND failed, types in COND are not same\n"; throw("");
			}
		}
		tree_node * e1 = this->car(this->car(temp));
		if(this->getType(e1) != "bool")
		{
			cout << "TYPE ERROR : COND failed, one of the bi is not boolean\n";
			throw("");
		}
		if(this->eval(this->car(this->car(temp)))->value != "F")
		{
			//cout << "True COndition found\n";
			if(flag == 0)
			{
				result = this->eval(this->car(this->cdr(this->car(temp))));
				flag = 1;
			}
		}
			//cout << "False COndition found\n";
		temp = this->cdr(temp);
		i++;
	}
	if(flag == 0)
	{
		string y = getValueForType(type);
		result = createNode(y,NULL,NULL);
		//cout << result->value << endl;
		//cout << "ERROR : None of the bi's are T in COND\n";
		//throw("");
	}
	return result;
}

string getValueForType(string type)
{
	string temp;
	if(type == "bool")
		temp = "T";
	else if(type == "Nat")
		temp = 1;
	else if(type == "List(Nat)")
		temp = "NIL";
	return temp;
}

string staticChecker::getType(tree_node* s)
{
	tree_node* result = this->eval(s);
	string type;
	//cout << "In getType : " << result->value <<endl;
	if(isNumeric(result))
	{
		type = "Nat";
	}
	else if(isList(s))
	{
		type = "List(Nat)";
	}
	else if(result->value == "T" or result->value == "F")
	{
		type = "bool";
	}
	return type;
}


vector<string> staticChecker::getFormalParam(string F)
{
	for(int i = 0; i < dl.size(); i++)
	{
		if(dl[i].func_name == F)
			return dl[i].formal_param;
	}
}

vector<string> staticChecker::isListOfLiteralAtoms(tree_node* s1,vector<string> arithmetic,vector<string> unary,vector<string> carcdr,vector<string> other)
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

bool staticChecker::isFuncNameInDlist(string F)
{
	//cout << "Looking for function in dlist...\n";
	for(int i = 0; i < dl.size(); i++)
	{
		if(dl[i].func_name == F)
			return true;
	}
	return false;
}

void staticChecker::printSExpression(tree_node* s)
{
	//cout << "In printSExpression...\n";
	if(this->atom1(s)->value == "T")
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
			if(this->cdr(s)->value == "F")
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

tree_node* staticChecker::createNode(string value, tree_node* left, tree_node* right)
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

bool staticChecker::isNumeric(tree_node* s)
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

bool staticChecker::in_array(const std::string &value, const std::vector<string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}

bool staticChecker::isList(tree_node* s)
{
	//s is a list if and only if the right most leaf node is a special literal atom NIL
	tree_node* temp = s;
	if(!temp)
		return false;
	while(temp->right != NULL and temp->left != NULL)
	{
		if(!isNumeric(this->car(temp)))
		{
			cout << "TYPE ERROR : Found a list which is not a list of numbers (i.e List(Nat))\n";
			//this->inorderPrint(s);
			throw("");
		}
		temp = temp->right;
	}
	if(temp->right == NULL and temp->left == NULL and temp->value == "NIL")
		return true;
	else
		return false;
}

bool staticChecker::isList1(tree_node* s)
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

void staticChecker::inorderPrint(tree_node* node)
{
	if(node)
	{
		this->inorderPrint(node->left);
		cout << node->value << " ";
		this->inorderPrint(node->right);
	}
}

bool staticChecker::allListOfLengthTwo(tree_node* s)
{
	//input s has COND as car(s), check for the rest of the tree whether si are list and length == 2 
	if(this->length(s) < 2)
		return false;
	tree_node* temp = s;
	temp = this->cdr(temp);
	while(temp->left != NULL)
	{
		//cout << length(car(temp)) << "\n";
		if(isList1(this->car(temp)) and length(car(temp)) == 2)
		{
			temp = this->cdr(temp);
		}
		else
			return false;
	}
	return true;
	
}
