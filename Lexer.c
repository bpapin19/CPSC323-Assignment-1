//
//  Lexor.c
//  323
//
//  Created by Brandon Papin on 2/19/20.
//  Copyright © 2020 Brandon Papin. All rights reserved.
//
#include <iostream>
#include <string.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


//delimeter - all seperators and operators
bool isDelimiter(char ch) {
    if (ch == ' '|| ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ','
        || ch == ';' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')'
        || ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return true;
    else
        return false;
}

//comment
bool isComment(char ch) {
    if (ch == '!')
        return true;
    else
        return false;
}

//seperator
bool isSeparator(char ch) {
    if (ch == '(' || ch == ')' || ch == ':' || ch == '[' || ch == ']' || ch == '{'
        || ch == '}' || ch == ' ' || ch == ';' || ch == ',' || ch == '.' || ch == '\'')
        
        return true;
    else
        
        return false;
}

// operator
bool isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' ||ch == '/' || ch == '>'
        || ch == '<' || ch == '=')
        return true;
    else
        return false;
}

// keyword
bool isKeyword(char* str) {
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do")
        || !strcmp(str, "then") || !strcmp(str, "whileend") ||
        !strcmp(str, "bool") || !strcmp(str, "and") || !strcmp(str, "float")
        || !strcmp(str, "function") || !strcmp(str, "int") ||
        !strcmp(str, "char") || !strcmp(str, "true") ||
        !strcmp(str, "false") || !strcmp(str, "endif")
        || !strcmp(str, "doend") || !strcmp(str, "forend")
        || !strcmp(str, "input") || !strcmp(str, "output")
        || !strcmp(str, "or") || !strcmp(str, "not"))
        
        return true;
    else
        return false;
}

// identifier
bool isIdentifier(char* str) {
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3'
        || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7'
        || str[0] == '8' || str[0] == '9' || isDelimiter(str[0]) == true || str[0] == '$')
        return (false);
    return (true);
}

// integer
bool isInteger(char* str) {
    int length = strlen(str);
    
    if (length == 0)
        return (false);
    for (int i = 0; i < length; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4'
            && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}


// real number
bool isRealNumber(char* str) {
    int length = strlen(str);
    bool dec = false;  //decimal or not
    
    if (length == 0)
        return (false);
    for (int i = 0; i < length; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3'
            && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7'
            && str[i] != '8' && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            dec = true;
    }
    return (dec);
}


// substring
char* subString(char* str, int left, int right) {
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
    
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

int counter = 0;

// read thru string
void parse(char* str, string outFileName) {
    int left = 0, right = 0;
    int len = strlen(str);
    string outputStr = "";
    
    while (right <= len && left <= right) {
        
        //First state
        if (isDelimiter(str[right]) == false)
            right++;
        
        if (isDelimiter(str[right]) == true && left == right) {
            if (isOperator(str[right]) == true)
            {
                cout << "OPERATOR           " << str[right] << endl;
            }
            else if (isSeparator(str[right]) == true) {
                cout << "SEPARATOR          " << str[right] << endl;
            }
            right++;
            left = right;
        }
        
        //second state
        else if (isDelimiter(str[right]) == true && left != right
                 || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);
            
            if (isKeyword(subStr) == true)
                cout << "KEYWORD            " << subStr << endl;
            
            else if (isInteger(subStr) == true)
                cout << "INTEGER            " << subStr << endl;
            
            else if (isRealNumber(subStr) == true)
                cout << "REAL               " << subStr << endl;
            
            else if (isIdentifier(subStr) == true
                     && isComment(str[right-1]) == true) {
                counter++;
                if (counter == 2) {
                    counter = 0;
                }
            }
            
            else if (isIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false)
                
                if (counter%2 == 0) {
                    cout << "IDENTIFIER         " << subStr << endl;
                }
            left = right;
        }
    }
    
    return;
}

int main() {
    
    string fileName;
    cout << "Enter file name: ";
    ifstream infile;
    string line;
    cin >> fileName;
    
    
    infile.open(fileName);
    if (infile.is_open())
    {
        string outFileName;
        cout << "Enter output file name: ";
        cin >> outFileName;
        ofstream myfile(outFileName);
        cout << "***************************" << endl;
        cout << " LEXICAL ANALYZER " << endl;
        cout << "***************************" << endl;
        
        cout << "Token              Lexeme" << endl;
        cout << "-------------------------" << endl;
        while (getline(infile, line, '\n')) {
            stringstream ss(line);
            while (getline(ss, line, ' ')) {
                
                char *cstr;
                cstr = new char[line.size() + 1];
                strcpy(cstr, line.c_str());
                parse(cstr, outFileName);
                myfile << cstr << " ";
            }
        }// end while
        
        infile.close();
        
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
    
    return (0);
}