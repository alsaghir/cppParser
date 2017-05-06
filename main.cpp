#include <fstream>
#include <vector>
#include <iostream>
#include <regex>

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
    return cindex >= allTokens.size() ?  false : statement_list();
}

bool statement_list(){
    return cindex >= allTokens.size() ?  false : (statement() && (++cindex, statement_list_dash()))  ;
}

bool statement_list_dash(){
    if(statement()){
        return (++cindex, statement_list_dash());
    }else
    {
        cindex--;
        return true;
    }
}

bool statement(){
    int tmpindex = cindex;
    return cindex >= allTokens.size() ?  false : ( (cindex = tmpindex, var_statement()) || (cindex = tmpindex, if_statement()) ) ;
}

bool var_statement(){
    return cindex >= allTokens.size() ?  false : (terminalLexeme("(") && (++cindex, iv()) && (++cindex, terminalLexeme(")")) && (++cindex, var())  && (++cindex, terminalLexeme(";")) );
}

bool iv(){
    int tmpindex = cindex;
    return cindex >= allTokens.size() ?  false : ((cindex = tmpindex,terminalLexeme("int")) || (cindex = tmpindex,terminalLexeme("void")));
}

bool var(){
    int tmpindex = cindex;
    return cindex >= allTokens.size() ?  false : (  ((cindex = tmpindex, terminalClass("id")) && (++cindex ,terminalLexeme("[")) && (++cindex ,terminalClass("num")) && (++cindex ,terminalLexeme("]"))) || (cindex = tmpindex, terminalClass("id"))  ) ;
}

bool if_statement(){
    int tmpindex = cindex;
    return cindex >= allTokens.size() ?  false : (  ((cindex = tmpindex, terminalLexeme("if")) && (++cindex, terminalLexeme("(")) && (++cindex, expression()) && (++cindex, terminalLexeme(")")) && (++cindex, statement_list()) && (++cindex, terminalLexeme("else")) && (++cindex, statement_list()))
                                                    || ((cindex = tmpindex, terminalLexeme("if")) && (++cindex, terminalLexeme("(")) && (++cindex, expression()) && (++cindex, terminalLexeme(")")) && (++cindex, statement_list()))  );
}

bool expression(){
    int tmpindex = cindex;
    return cindex >= allTokens.size() ?  false : (  ((cindex = tmpindex, var()) && (++cindex, terminalLexeme("=")) && (++cindex, expression()))
                                                    || ((cindex = tmpindex, add_expression()) && (++cindex, relop()) && (++cindex, add_expression()))
                                                    || (cindex = tmpindex, add_expression())  ) ;
}

bool relop(){
    return cindex >= allTokens.size() ?  false : (terminalLexeme(">=") || terminalLexeme("<=") || terminalLexeme("<>") || terminalLexeme("<") || terminalLexeme(">") || terminalLexeme("==")) ;
}

bool add_expression(){
    return cindex >= allTokens.size() ?  false : ( term() && (++cindex, add_expression_dash()) ) ;
}

bool add_expression_dash() {
    cout << "add_expression_dash() : ";
    if (cindex < allTokens.size()) cout << allTokens[cindex].lexemeToken;
    cout << endl;
    if (addop() && !(cindex >= allTokens.size())) {
        return (++cindex, term()) && (++cindex, add_expression_dash());
    } else {
        --cindex;
        return true;
    }
}

bool addop(){
    return cindex >= allTokens.size() ?  false : (terminalLexeme("+") || terminalLexeme("-")) ;
}

bool term(){
    return cindex >= allTokens.size() ?  false : (factor() && (++cindex, term_dash())) ;
}

bool term_dash(){
    
    if (mulop() && !(cindex >= allTokens.size())){
        return (++cindex, factor()) && (++cindex, term_dash());
    } else{
        --cindex;
        return true;
    }
}

bool mulop(){
    return cindex >= allTokens.size() ?  false : (terminalLexeme("*") || terminalLexeme("/")) ;
}

bool factor(){
    return cindex >= allTokens.size() ?  false : terminalClass("num") ;
}

bool terminalLexeme(string expected) {

    return cindex >= allTokens.size() ?  false : allTokens[cindex].lexemeToken == expected;
}

bool terminalClass(string expected) {
    return cindex >= allTokens.size() ?  false : allTokens[cindex].classToken == expected;
}


int main() {

    if (program())
        cout << endl << "parsing is success >> 1" << endl << endl;
    else
        cout << endl << "parsing is fail >> 0" << endl << endl;

    cout << "Index number is = " << cindex << endl;
    cout << "Tokens number is = " << allTokens.size() << endl;

    return 0;
}