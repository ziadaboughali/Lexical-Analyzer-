#include <map>
#include <string>
#include <vector>
#include "lex.h"

using namespace std;
map<Token, string>::iterator iter;
map<Token, string> mapHolder =
    {{PROGRAM, "PROGRAM"}, {WRITELN, "WRITELN"}, {INTEGER, "INTEGER"}, {BEGIN, "BEGIN"}, {END, "END"}, 
    {IF, "IF"}, {REAL, "REAL"}, {STRING, "STRING"}, {VAR, "VAR"}, 
    {ELSE, "ELSE"}, {FOR, "FOR"}, {THEN, "THEN"}, {DO, "DO"}, {TO, "TO"}, {DOWNTO, "DOWNTO"}, 
    {IDENT, "IDENT"}, {ICONST, "ICONST"}, {RCONST, "RCONST"}, {SCONST, "SCONST"}, {PLUS, "PLUS"}, {MINUS, "MINUS"}, {MULT, "MULT"}, 
    {DIV, "DIV"}, {ASSOP, "ASSOP"}, {LPAREN, "LPAREN"}, {RPAREN, "RPAREN"}, {COMMA, "COMMA"}, {EQUAL, "EQUAL"}, {GTHAN, "GTHAN"}, 
    {LTHAN, "LTHAN"}, {SEMICOL, "SEMICOL"}, {COLON, "COLON"}, {ERR, "ERR"}, {DONE, "DONE"}};

LexItem id_or_kw(const string &lexeme, int linenum)
{
    Token t = IDENT;
    iter = mapHolder.begin();

    while (iter != mapHolder.end())

    {
        Token tempToken = (*iter).first;
        bool check = lexeme.compare((*iter).second);
        if (check == 0)
        {
            t = tempToken;
        }
        iter++;
    }
    return LexItem(t, lexeme, linenum);
}
ostream &operator<<(ostream &out, const LexItem &tok)
{
    iter = mapHolder.begin();
    while (iter != mapHolder.end())

    {
        Token tempToken = (*iter).first;
        Token getTok = tok.GetToken();
        string tokString = (*iter).second;
        string lex = tok.GetLexeme();
        int getLineNum = tok.GetLinenum();
        if (tempToken == getTok )
        {
            if(getTok == IDENT || getTok == ICONST || getTok == RCONST || getTok == SCONST)
            {
                    out << tokString << "(" << lex << ")";
                

            }

            else
            {
                out << tokString;
            }

        }
        iter++;
    }
    return out;
}



LexItem getNextToken(istream& in, int& linenum)
{
enum TokenState { START, INID, INSTRING, ININT, INREAL, INCOMMENT, SIGN} 
lexstate = START;
string lexeme = "";
char ch;
vector<char> vec;
int singleQuote = 0;
int doubleQuote = 1;



    while(in.get(ch))
    {
        switch(lexstate)
        {
            case START:
                if(ch == '\n') //newlines 
                {
                    linenum++;
                }
                
                vec.insert(vec.begin(),'(');
                vec.insert(vec.begin()+1, '*');
                if(ch == '(') //comments
                    if(in.peek() == '*')
                    { 
                    lexstate = INCOMMENT;
                    continue;
                    }

                if(in.eof())  //DONE when it reaches the end of the file 
                {
                    return LexItem(DONE, lexeme, linenum);
                }
                
                if(ch == ' ') //when a space is found, move along 
                {
                    continue;
                }

              
                Token toke = ERR;
                switch(ch)
                {
                    case '+':
                    toke = PLUS;
                    break;

                    case '-':
                    toke = MINUS;
                    break;
                    case '*':
                    toke = MULT;
                    break;
                    case '/':
                    toke = DIV;
                    break;
                    case '(':
                    toke = LPAREN;
                    break;
                    case ')':
                    toke = RPAREN;
                    break;
                    case ';':
                    toke = SEMICOL;
                    break;
                    case ',':
                    toke = COMMA;
                    break;
                    case '<':
                    toke = LTHAN;
                    break;
                    case '>':
                    toke = GTHAN;
                    break;
                    case '=':
                    toke = EQUAL;
                    break;
                    case ':':
                    toke = COLON;
                    if(isdigit(in.peek()) == '=')
                    {
                        in.get(ch);
                        toke = ASSOP;
                        break;
                    }
                    case '.':
                    if(isdigit(in.peek()))
                    {
                        lexstate = INREAL;
                        continue;
                    }
                    else{
                        lexeme = in.peek();
                        return LexItem(ERR, lexeme,linenum);
                    }
                return LexItem(toke,lexeme,linenum);
                }
            else{
                lexeme = ch;
                return LexItem(ERR, lexeme,linenum);
            }
               
                if(ch == '\'' && ch != '"')
                {
                    lexstate = INSTRING;
                    continue;
                }
                
                if(isdigit(ch))   //integers
                {
                lexstate = ININT;
                lexeme = ch;
                continue;
                }
                if(ch == '.')  //reals
                {
                lexeme = '.';
                if(!isdigit(in.peek()))
                {
                    lexeme += in.get();
                    return LexItem(ERR, lexeme,linenum);
                }
                lexstate = INREAL;

                
                if(isalpha(ch) || ch == '_') //  //identifiers
                {
                    
                    lexeme = toupper(ch);
                    lexstate = INID;


                continue;
                }

                return LexItem(ERR,lexeme,linenum);

            case INID:
                if(ch == '\n')
                {
                    linenum++;
                    return id_or_kw(lexeme,linenum);
                }
                else if(ch == ' ')
                {
                    return id_or_kw(lexeme,linenum);
                }
                else if(isdigit(ch) || ch == '_')
                {
                    lexeme += ch;
                }
            case INSTRING:
                lexeme += ch;

                if(ch =='\n')
                {
                    return LexItem(ERR,lexeme,linenum);
                }
                if (ch == '"' && singleQuote)
                {
                    lexeme = lexeme.substr(1,lexeme.length()-2);
                    return LexItem(SCONST,lexeme,linenum);
                }
                else if(ch == '\'' && doubleQuote)
                {
                    lexeme = lexeme.substr(1,lexeme.length()-2);
                    return LexItem(SCONST,lexeme,linenum);
                }
                break;
            case ININT:

                if(isdigit(ch))
                {
                    lexeme += ch;
                }
                else if(ch == '.')
                {
                    if(isdigit(in.peek())) //INREAL check
                    {
                        lexstate = INREAL;
                        in.putback(ch);
                    }
                }
                else{
                    in.putback(ch);
                    return LexItem(ICONST,lexeme,linenum);
                }
                break;
            case INREAL:
            if(ch=='.')
            {
                if(isdigit(in.peek()))
                {
                    lexeme += ch;
                }

            }
            else if(isdigit(ch))
            {
                lexeme += ch;
            }
            else if(ch == '.')
            {
                if(!isdigit(in.peek()))
                {
                    lexeme += ch;
                    return LexItem(ERR,lexeme,linenum);
                }
            }
            else{
                in.putback(ch);
                return LexItem(RCONST,lexeme,linenum);
            }
            break;

            case INCOMMENT:
                if( ch == '\n')
                {
                    linenum++;
                    lexstate = START;
                    continue;
                }
                break;
            }
            return LexItem(DONE,"",linenum);
        }   
    }

}