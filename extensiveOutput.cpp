/*
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <stack>

using namespace std;

// ifstream is used for reading files
// We'll read from a file called Sample.dat

struct Token {
    string classToken;
    string lexemeToken;
};

vector<Token> getTokens(ifstream & inf) {
    Token theToken;
    vector<Token> arrayOfTokens;
    while (!inf.eof()) {
        string strInput;
        getline(inf, strInput);
        smatch match;
        regex lexemeRegex(",.*>");
        regex classRegex("<.*,");
        regex_search(strInput, match, lexemeRegex);
        string lexemeToken = match[0];
        regex_search(strInput, match, classRegex);
        string classToken = match[0];
        lexemeToken.replace(0, 2, "");
        classToken.replace(0, 1, "");
        lexemeToken.replace(lexemeToken.length() - 1, 1, "");
        classToken.replace(classToken.length() - 1, 1, "");
        theToken.classToken = classToken;
        theToken.lexemeToken = lexemeToken;
        arrayOfTokens.push_back(theToken);
    }
    return arrayOfTokens;
}

bool program();
bool statement_list();
bool statement();
bool statement_list_dash();
bool var_statement();
bool var();
bool iv();
bool if_statement();
bool expression();
bool add_expression();
bool add_expression_dash();
bool relop();
bool term();
bool term_dash();
bool addop();
bool mulop();
bool factor();
bool terminalLexeme(string expected);
bool terminalClass(string expected);


ifstream inf("Sample.hamada", ifstream::binary);
vector<Token> allTokens = getTokens(inf);
int cindex = 0;

bool program(){
    cout << "program() : "; if (cindex < allTokens.size())  cout << allTokens[cindex].lexemeToken; cout << endl;
    if (cindex >= allTokens.size() ?  false : statement_list()) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool statement_list(){
    cout << "statement_list() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    if ( cindex >= allTokens.size() ?  false : (statement() && (++cindex, statement_list_dash()))) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool statement_list_dash(){
    cout << "statement_list_dash() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    if(statement()){
        cout << " -TRUE_STMT_LIST_DASH- ";
        return (++cindex, statement_list_dash());
    }else
    {
        cindex--;
        return true;
    }
}

bool statement(){
    cout << "statement() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    int tmpindex = cindex;
    if ( cindex >= allTokens.size() ?  false : ( (cindex = tmpindex, var_statement()) || (cindex = tmpindex, if_statement()))) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool var_statement(){
    cout << "var_statement() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    if ( cindex >= allTokens.size() ?  false : (terminalLexeme("(") && (++cindex, iv()) && (++cindex, terminalLexeme(")")) && (++cindex, var()) && (++cindex, terminalLexeme(";"))  )) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool iv(){
    cout << "iv() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    int tmpindex = cindex;
    if( cindex >= allTokens.size() ?  false : ((cindex = tmpindex,terminalLexeme("int")) || (cindex = tmpindex,terminalLexeme("void")))) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool var(){
    cout << "var() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    int tmpindex = cindex;
    if( cindex >= allTokens.size() ?  false : (  ((cindex = tmpindex, terminalClass("id")) && (++cindex ,terminalLexeme("[")) && (++cindex ,terminalClass("num")) && (++cindex ,terminalLexeme("]"))) || (cindex = tmpindex, terminalClass("id"))  )) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool if_statement(){
    cout << "if_statement() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    int tmpindex = cindex;
    if( cindex >= allTokens.size() ?  false : (  ((cindex = tmpindex, terminalLexeme("if")) && (++cindex, terminalLexeme("(")) && (++cindex, expression()) && (++cindex, terminalLexeme(")")) && (++cindex, statement_list()) && (++cindex, terminalLexeme("else")) && (++cindex, statement_list()))
                                                 || ((cindex = tmpindex, terminalLexeme("if")) && (++cindex, terminalLexeme("(")) && (++cindex, expression()) && (++cindex, terminalLexeme(")")) && (++cindex, statement_list()))  )) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool expression(){
    cout << "expression() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout <<endl;
    int tmpindex = cindex;
    if( cindex >= allTokens.size() ?  false : (  ((cindex = tmpindex, var()) && (++cindex, terminalLexeme("=")) && (++cindex, expression()))
                                                 || ((cindex = tmpindex, add_expression()) && (++cindex, relop()) && (++cindex, add_expression()))
                                                 || (cindex = tmpindex, add_expression())  ) ) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool relop(){
    cout << "relop() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    return cindex >= allTokens.size() ?  false : (terminalLexeme(">=") || terminalLexeme("<=") || terminalLexeme("<>") || terminalLexeme("<") || terminalLexeme(">") || terminalLexeme("==")) ;
}

bool add_expression(){
    cout << "add_expression() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    if( cindex >= allTokens.size() ?  false : ( term() && (++cindex, add_expression_dash()) ) ) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool add_expression_dash(){
    cout << "add_expression_dash() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    if (addop() && !(cindex >= allTokens.size())){
        cout << " -TRUE_ADDOP- ";
        return (++cindex, term()) && (++cindex, add_expression_dash());
    } else{
        cindex--;
        return true;}
}

bool addop(){
    cout << "addop() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    return cindex >= allTokens.size() ?  false : (terminalLexeme("+") || terminalLexeme("-")) ;
}

bool term(){
    cout << "term() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    if( cindex >= allTokens.size() ?  false : (factor() && (++cindex, term_dash())) ) {
        cout << "TRUE";
        return true;
    }
    else
    {
        cout << "FALSE";
        return false;
    }
}

bool term_dash(){
    cout << "term_dash() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    if (mulop() && !(cindex >= allTokens.size())){
        cout << " -TRUE_TERM_DASH- ";
        return (++cindex, factor()) && (++cindex, term_dash());
    } else {
        cindex--;
        return true;
    }
}

bool mulop(){
    cout << "mulop() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    return cindex >= allTokens.size() ?  false : (terminalLexeme("*") || terminalLexeme("/")) ;
}

bool factor(){
    cout << "factor() : ";if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << endl;
    return cindex >= allTokens.size() ?  false : terminalClass("num") ;
}

bool terminalLexeme(string expected) {

    cout << "terminalLexeme() : "; if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken; cout << " ON " << expected << endl;
    return cindex >= allTokens.size() ?  false : allTokens[cindex].lexemeToken == expected;
}

bool terminalClass(string expected) {

    cout << "terminalClass() : "; if (cindex < allTokens.size()) cout << allTokens[cindex].classToken; cout << " ON " << expected << endl;
    return cindex >= allTokens.size() ?  false : allTokens[cindex].classToken == expected;
}


int main() {

    if (program())
        cout << endl << endl << "parsing is success >> 1" << endl << endl;
    else
        cout << endl << endl << "parsing is fail >> 0" << endl << endl;

    cout << "Index Of remaining is = " << cindex << endl;
    cout << "Tokens number is = " << allTokens.size() << endl;

    return 0;
}*/
