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

using namespace std;

ifstream ifile; //ifile is a stream to input file
pair<string,string> current;//maintains the current current being analysed by the parser
int openParantheses = 0; int closeParantheses = 0; int literalAtom = 0; int numericAtom = 0;
int sum_nAtoms = 0;

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
	/*for (int i = 0; i < nAtom.size(); ++i)
	{
		ofile << nAtom[i] << ",";
	}*/
	ofile << "OPEN PARANTHESES : " << openParantheses << "\n";
	ofile << "CLOSE PARANTHESES : " << closeParantheses << "\n";
	ofile.close();
}



int main(int argc, char const *argv[])
{
	Scanner scanner;
	
	string i_filename = argv[1];
	//cout << "Input file : " << argv[2] << "\n";
	vector<string> lAtom;//maintains list of literal atoms found
	vector<string> nAtom;//maintains list of numeric atoms found

	ifile.open(i_filename.c_str());//convert string type to char array format as found in c
	
	//scanner.Init();
	//ParseStart();
	int flag = 1;
	while(flag)
	{
		current = scanner.getNextToken(); //current contains current category and the value of the current as a pair
		//cout << current.first << " " << current.second << "\n";
		if(current.first == "Null")
		{
			//exit the loop if the read function or the get function fails
			cout << "Error reading the input file\n";
			flag = 0;
		}
		if(current.first == "EOF")
		{
			cout << "End of file reached\n";
			flag = 0;
		}
		if(current.first == "ERROR")
		{
			cout << "\nERROR: Invalid token " << current.second << "\n\n";
			flag = 0;		
		}
		else if(current.first == "openParantheses")
			openParantheses++;
		else if(current.first == "closeParantheses")
			closeParantheses++;
		else if(current.first == "literalAtom")
		{
			lAtom.push_back(current.second);
			literalAtom++;
		}
		else if(current.first == "numericAtom")
		{
			nAtom.push_back(current.second);
			numericAtom++;
			int sum = atoi(current.second.c_str());
			sum_nAtoms += sum;
		}
	}

	ifile.close();
	writeToFile(argv[2],lAtom,nAtom,literalAtom,numericAtom,openParantheses,closeParantheses);
	
	return 0;
}

