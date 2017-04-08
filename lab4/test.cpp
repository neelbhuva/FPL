#include <string.h>
#include <iostream>
#include <map>
#include <utility>
 
using namespace std;
 
int main()
{	
	map< double*, T> mapa;
	
	double a[3] = {1,2,3};
	double b[3] = {1,0,0};
	
	mapa[a] = "a";
	mapa[b] = "b";
 
   cout << mapa[a] << endl; //This print ok.

   for( map<double*,string>::iterator ii=mapa.begin(); ii!=mapa.end(); ++ii)
   {
       cout << (*ii).first << ": " << (*ii).second << endl;
   }
   // (*ii).first gives me trash.
   
}