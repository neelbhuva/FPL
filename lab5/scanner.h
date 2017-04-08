/* This code is written by Neelkumar Shailesh Bhuva
   as part of CSE 6341 (Foundations of Programming Languages) 
   project at the Ohio State University. 
*/

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdlib.h>

using namespace std;

extern string i_filename;
extern int openParantheses;
extern int closeParantheses;
extern int p;
class Scanner
{
    public:
	pair<string,string> current;

    public:
	void Init()// get the first token
	{
		this->current = this->getNextToken(); 
		//cout << current.first << " " << current.second << "\n";
	} 

	pair<string,string> GetCurrent() // does not read anything from input
	{ 
		return this->current; 
	} 

	void MoveToNext()
	{ 
		this->current = this->getNextToken(); 
		//cout << current.first << " " << current.second << "\n";
	} 

	pair<string,string> getNextToken();
};

pair<string,string> Scanner::getNextToken()
{
	//char i_filename;
	pair<string,string> token;
	vector<char> literalAtom;
	vector<char> numericAtom;

	/*if(!i_filename[p])
	{
		//get function failed
		token.first = "Null";
		token.second = "Null";
	}*/
	//cout << i_filename[p];
	if(!i_filename[p])
	{
		//End of file reached
		//cout << "End of file reached\n";
		token.first = "EOF";
		token.second = "0";
	}
	else if(isspace(i_filename[p])) //isspace takes into account whitespace, carriage return and linefeed
	{
		p++; //cout << "Space Found\n";
		token = this->getNextToken();
	}
	else if(i_filename[p] == '(')
	{
		p++;
		token.first = "openParantheses"; 
		token.second = "2";
	}
	else if(i_filename[p] == ')')
	{
		p++;
		token.second = "3";
		token.first = "closeParantheses";
	}
	else if(isupper(i_filename[p]))
	{
		token.first = "literalAtom";
		literalAtom.push_back(i_filename[p]);
		p++;
		while(1)
		{
			if(!i_filename[p])
			{				
				//cout << "Error while reading input file\n";
				//exit(0);
				p++;
				break;
			}
			if(isspace(i_filename[p]) or i_filename[p] == '\n') {p++; break;}
			else if((isupper(i_filename[p])) || (isdigit(i_filename[p])))
			{
				literalAtom.push_back(i_filename[p]);
				p++;
			}
			else if(i_filename[p] == '(')
			{
				//ifile.unget();
				openParantheses++;
				break;
			}
			else if(i_filename[p] == ')')
			{
				//ifile.unget();
				closeParantheses++;
				break;
			}
			else
			{
				token.first = "ERROR";
				literalAtom.push_back(i_filename[p]);
				p++;
				break;
			}
			
		}
		string a(literalAtom.begin(),literalAtom.end());
		cout << a << "\n";
		
		token.second = a;
	}
	else if(isdigit(i_filename[p]))
	{
		token.first = "numericAtom";
		numericAtom.push_back(i_filename[p]);
		p++;
		int flag = 0;
		while(1)
		{
			if(!i_filename[p])
			{
				//cout << "Digit : Error while reading input file\n";
				//exit(0);
				p++;
				break;
			}
			if(isspace(i_filename[p]) or i_filename[p] == '\n') {p++; break;}
			else if(isupper(i_filename[p]))
			{
				token.first = "ERROR";
				numericAtom.push_back(i_filename[p]);
				p++;
				flag = 1;
			}
			if(isdigit(i_filename[p]) && flag == 1)
			{
				numericAtom.push_back(i_filename[p]);
				p++;
				continue;
			}
			else if(isdigit(i_filename[p]))
			{
				numericAtom.push_back(i_filename[p]);
				p++;
			}
			else if(i_filename[p] == '(')
			{
				//ifile.unget();
				openParantheses++;
				break;
			}
			else if(i_filename[p] == ')')
			{
				//ifile.unget();
				closeParantheses++;
				break;
			}	
			else
			{
				token.first = "ERROR";
				numericAtom.push_back(i_filename[p]);
				p++;
				break;
			}		
		}		
		string a(numericAtom.begin(),numericAtom.end());
		//cout << a << "\n";
		token.second = a;		
	}
	return token;
}

#endif