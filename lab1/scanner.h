#include <string>
#include <iostream>
#include <fstream>

using namespace std;

extern ifstream ifile;
extern int openParantheses;
extern int closeParantheses;

class Scanner
{
    public:
	pair<string,string> current;

    public:
	void Init(){current = Scanner::getNextToken();} // get the first token

	pair<string,string> GetCurrent() { return current; } // does not read anything from input

	void MoveToNext(){ current = Scanner::getNextToken(); } 

	pair<string,string> getNextToken();
};

pair<string,string> Scanner::getNextToken()
{
	char buffer;
	pair<string,string> token;
	vector<char> literalAtom;
	vector<char> numericAtom;

	if(!ifile.get(buffer))
	{
		//get function failed
		token.first = "Null";
		token.second = "Null";
	}
	if(ifile.eof())
	{
		//End of file reached
		token.first = "EOF";
		token.second = "0";
	}
	else if(isspace(buffer)) //isspace takes into account whitespace, carriage return and linefeed
	{
		//cout << "White space found, ignoring....\n";
		token = getNextToken();
	}
	else if(buffer == '(')
	{
		token.first = "openParantheses"; 
		token.second = "2";
	}
	else if(buffer == ')')
	{
		token.second = "3";
		token.first = "closeParantheses";
	}
	else if(isupper(buffer))
	{
		literalAtom.push_back(buffer);
		while(1)
		{
			if(!ifile.get(buffer))
				cout << "Error while reading input file\n";
			if(isspace(buffer)) break;
			if((isupper(buffer)) || (isdigit(buffer)))
			{
				literalAtom.push_back(buffer);
			}
			else if(buffer == '(')
			{
				openParantheses++;
				break;
			}
			else if(buffer == ')')
			{
				closeParantheses++;
				break;
			}
			
		}
		string a(literalAtom.begin(),literalAtom.end());
		//cout << a << "\n";
		token.first = "literalAtom";
		token.second = a;
	}
	else if(isdigit(buffer))
	{
		token.first = "numericAtom";
		numericAtom.push_back(buffer);
		int flag = 0;
		while(1)
		{
			if(!ifile.get(buffer))
				cout << "Error while reading input file\n";
			if(isspace(buffer)) break;
			if(isupper(buffer))
			{
				token.first = "ERROR";
				numericAtom.push_back(buffer);
				flag = 1;
			}
			if(isdigit(buffer) && flag == 1)
			{
				numericAtom.push_back(buffer);
				continue;
			}
			if(isdigit(buffer))
				numericAtom.push_back(buffer);
			else if(buffer == '(')
			{
				openParantheses++;
				break;
			}
			else if(buffer == ')')
			{
				closeParantheses++;
				break;
			}
			
		}
		
		string a(numericAtom.begin(),numericAtom.end());
		//cout << a << "\n";
		token.second = a;		
	}

	return token;
}
