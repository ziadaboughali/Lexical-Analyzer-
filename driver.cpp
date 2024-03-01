#include <iostream>
#include <fstream>
#include <string>
#include <map> 
#include <vector>
#include "lex.h"
#include <sstream>
#include <cctype>



using namespace std;

void getNextToken()
{

}

 


int main(int argc, char *argv[])
{
    map<string,int> stringMap;
    map<string,int> identMap;
    map<int,int> intMap;
    map<float,int> floatMap;


    string file = "";
    ifstream inFile;
    int b = 1;
    bool v,iconst,rconst,sconst,ident = false;
    while(argc > b)
    {
        string fileN = argv[b];
        if(fileN == "-v")
        {
            v = !v;
        }
        else if(fileN == "-iconst")
        {
            iconst = !iconst;
        }
        else if(fileN == "-rconst")
        {
            rconst = !rconst;
        }
        else if(fileN == "-sconst")
        {
            sconst = !sconst;
        }
        else if(fileN == "-ident")
        {
            ident = !ident;
        }
        else if(fileN[0] == '-')
        {
            cout<<"UNRECOGNIZED FLAG " <<file<<endl;
            return 0;
        }
        
        else if(file != ""){
        cout << "ONE ONLY FILE NAME ALLOWED." << endl;
        return 1;
        }
        else{
            file = fileN;
        }
       
        fin.open(file.c_str());

        if(file == "")
        {
            cout<< "NO SPECIFIED INPUT FILE NAME."<< endl;
            return 1;
        }
        else if (!inFile)
        {
            cerr << "CANNOT OPEN the File" << file <<endl;
            return 1;
        }
        
        int tokens = 0;
        int lines = 1;
        int linenum = 0;
        int linePrint = 0;
        LexItem token;
        token = getNextToken(inFile,linenum);
        Token currToken = token.GetToken();
        lines = token.GetLinenum();


        tokens++;

        if(currToken != DONE)
        {
            break;
        }

        if(currToken == ICONST)
        {
           
        }
    }
}

