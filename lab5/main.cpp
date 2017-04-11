/* This code is written by Neelkumar Shailesh Bhuva
   as part of CSE 6341 (Foundations of Programming Languages) 
   project at the Ohio State University. 
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "scanner.h"
#include "binaryTree.h"
#include "staticChecker.h"
#include "common.h"

using namespace std;

//vector<struct dlist> dl;
//ifstream ifile; //ifile is a stream to input file
string i_filename; string file_content;
pair<string,string> current;//maintains the current current being analysed by the parser
int openParantheses = 0; int closeParantheses = 0; int literalAtom = 0; int numericAtom = 0;
int sum_nAtoms = 0; int p = 0;
vector<string> lAtom;//maintains list of literal atoms found
vector<string> nAtom;//maintains list of numeric atoms found

void writeToFile(string o_filename, vector<string> lAtom, vector<string> nAtom, int literalAtom, int numericAtom, int openParantheses, int closeParantheses)
{
	ofstream ofile; //ofile refers to the output file
	ofile.open(o_filename.c_str());
	ofile << "LITERAL ATOM : " << literalAtom << " ";
	for (int i = 0; i < lAtom.size(); ++i)
	{
		ofile << lAtom[i] << ",";
	}
	ofile << "\n";
	ofile << "NUMERIC ATOM : " << numericAtom << " " << sum_nAtoms << "\n";
	ofile << "OPEN PARANTHESES : " << openParantheses << "\n";
	ofile << "CLOSE PARANTHESES : " << closeParantheses << "\n";
	ofile.close();
}

void count(pair<string,string> token)
{
	if(token.first == "Null")
	{
		//exit the loop if the read function or the get function fails
		throw "Error reading the input file\n";
	}
	if(token.first == "EOF")
	{
		//cout << "End of file reached\n";
		//flag = 0;
	}
	if(token.first == "ERROR")
	{
		throw ("\nERROR: Invalid token%s\n",token.second);		
	}
	else if(token.first == "openParantheses")
		openParantheses++;
	else if(token.first == "closeParantheses")
		closeParantheses++;
	else if(token.first == "literalAtom")
	{
		lAtom.push_back(current.second);
		literalAtom++;
	}
	else if(token.first == "numericAtom")
	{
		nAtom.push_back(current.second);
		numericAtom++;
		int sum = atoi(current.second.c_str());
		sum_nAtoms += sum;
	}
}

tree_node* ParseExpr(Scanner* scanner)
{
	//cout << "In parseexpr\n";
	if (scanner->GetCurrent().first == "literalAtom" || scanner->GetCurrent().first == "numericAtom" ) 	
	{ 
		//cout << "Current token: " << scanner->GetCurrent().second << "\n";
		BinaryTree bt;
		//create new node
		tree_node atom1 = bt.createNode(scanner->GetCurrent().second,NULL,NULL);
		//cout << "Node Created : " << atom1.value << "\n";
		bt.makeRoot(&atom1);
		scanner->MoveToNext();// consume atom
		return bt.root;
	} 
 	else if (scanner->GetCurrent().first == "openParantheses") 
	{
		BinaryTree bt;
		scanner->MoveToNext(); // consume open parenthesis
		tree_node* temp1; int c = 0;
		while (scanner->GetCurrent().first != "closeParantheses") 
		{ 
			c++;
			temp1 = ParseExpr(scanner);
			bt.insert(temp1);
		}
		if(c = 0)
		{
			//cout << "Found Empty paranthese\n";
			tree_node t = bt.createNode("NIL",NULL,NULL);
			bt.insert(&t);
		}
		//Make the right most node as NIL
		bt.makeNIL(bt.root);
		scanner->MoveToNext(); // consume closing parenthesis
		return bt.root;

	}
	else
	{
		throw("Parser Error");	
	}
}


void ParseStart(Scanner* scanner)
{
	//cout << "In parse start\n";
	BinaryTree bt;
	do
	{
		try
		{
			bt.root = ParseExpr(scanner);
		}
	    catch(...)
	    {
	    	throw("Parser Error");
	    }
	    bt.Print(bt.root);
	    cout << "\nPrinting done...\n";
	    try
	    {
	    	staticChecker ip;
	    	//tree_node* temp = ip.car(bt.root);
	    	//int temp23 = ip.length(bt.root);
	    	//cout << temp23 << "\n";
	    	//tree_node* temp1 = ip.car(ip.cdr((bt.root)));
			//tree_node* temp2 = ip.cons(temp,temp1);
			//tree_node* temp5 = ip.car(temp1);
			//tree_node* temp6 = ip.times(temp,temp5);
			//tree_node* temp3 = ip.greater(temp,temp1);
			//tree_node* temp4 = ip.INT(bt.root);
			//cout << "SSUp" <<  "\n";
			
	    	//bt.inorderPrint(bt.root);
	    	//cout << "\n";
	    	//ip.printSExpression(bt.root);
	    	tree_node* result_tree = ip.eval(bt.root);
	    	//cout << "List Notation...\n";
			//bt.Print(result_tree);
			//cout << "\nInorder Print...\n";
	    	//ip.inorderPrint(result_tree);
	    	//cout << "\nPrinting...\n";
	    	//ip.printSExpression(result_tree);
	    	//cout << "\n";
	    	//cout << dl[0].func_name << "\n";
	    }
	    catch(...)
	    {
	    	return;
	    }
	    try
	    {
	    	emptyListChecker elc;
	    	tree_node* elc_result = elc.eval(bt.root);
	    }
	    catch(...)
	    {
	    	return;
	    }
	}while(scanner->GetCurrent().first != "EOF");
}



int main(int argc, char const *argv[])
{
	//cout << "In main\n";
	Scanner* scanner = new(Scanner);
	//string i_filename;
	int f = 0;
	while(getline(cin,file_content))
	{
	i_filename += file_content;
	p = 0; f = 1;
	if(file_content == "")
	{
		//cout << "Blank line found\n";
		continue;
	}
	}
	/*if(f == 0)
		cout << "Parser error : empty file\n";*/
	//cout << i_filename << "\n";
	//ifile.open(i_filename.c_str());//convert string type to char array format as found in c
	scanner->Init();
	//try{
	  //  count(scanner->current);
	//}
	//catch(...){
	  //  return 0;
	//}
	try
	{
		ParseStart(scanner);
	}
	catch(...)
	{
		cout << "Parser Error  : Terminating the program\n";
		return 0;
	}
	
	
	//ifile.close();
	//writeToFile(argv[2],lAtom,nAtom,literalAtom,numericAtom,openParantheses,closeParantheses);
	i_filename = "";
	return 0;
}

