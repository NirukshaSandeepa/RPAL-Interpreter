#include <iostream>
#include <stack>
#include <iterator>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <stdio.h>
#include "token.h"
#include "tree.h"
#include "environment.h"

using namespace std;

stack<tree *> st; // Stack for syntax tree

// Array of operators
char operators[] = {'+', '-', '*', '<', '>', '&', '.', '@', '/', ':', '=', '~', '|', '$', '!', '#', '%',
                    '^', '_', '[', ']', '{', '}', '"', '`', '?'};

// Array of binary operators
string binary_operators[] = {"+", "-", "*", "/", "**", "gr", "ge", "<", "<=", ">", ">=", "ls", "le", "eq", "ne", "&", "or", "><"};

// Array of keywords
string keys[] = {"let", "fn", "in", "where", "aug", "or", "not", "true", "false", "nil", "dummy", "within",
                 "and", "rec", "gr", "ge", "ls", "le", "eq", "ne"};

class parser{
    public:
    token nextToken;     // Next token to be read
    char readnew[10000]; // Stores program for parsing
    int index;           // Index of character
    int sizeOfFile;      // Size of file
    int astFlag;         // Flag to check if AST or ST is to be printed

    parser(char read_array[], int i, int size, int af)
    {
        copy(read_array, read_array + 10000, readnew);
        index = i;
        sizeOfFile = size;
        astFlag = af;
    }

    // Checks if the given string is a keyword
    bool isReservedKey(string str)
    {
        // int size = keys.size();
        int i = 0;
        for (i = 0; i < 20; i++)
        {
            if (str == keys[i])
                return true;
        }
        return false;
    }

    // Checks if the given character is an operator
    bool isOperator(char ch)
    {
        for (int i = 0; i < 25; i++)
        {
            if (ch == operators[i])
            {
                return true;
            }
        }
        return false;
    }

    // Checks if the given character is an alphabet letter
    bool isAlpha(char ch)
    {
        if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
        {
            return true;
        }
        return false;
    }

    // Checks if the given character is a digit
    bool isDigit(char ch)
    {
        if (ch >= 48 && ch <= 57)
        {
            return true;
        }
        return false;
    }

    // Checks if the given string is a binary operator
    bool isBinaryOperator(string op)
    {
        for (int i = 0; i < 18; i++)
        {
            if (op == binary_operators[i])
            {
                return true;
            }
        }
        return false;
    }
        // Checks if the given string is a number
    bool isNumber(const std::string &s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it))
            ++it;
        return !s.empty() && it == s.end();
    }

    // Read the next token
    void read(string val, string type)
    {
        if (val != nextToken.getVal() || type != nextToken.getType()) // Check if the next token is the expected token
        {
            cout << "Parse error: Expected " << "\"" << val << "\"" << ", but " << "\"" << nextToken.getVal() << "\"" << " was there" << endl;
            exit(0);
        }

        if (type == "ID" || type == "INT" || type == "STR") // If the token is an identifier, integer or string
            buildTree(val, type, 0);

        nextToken = getToken(readnew); // Get the next token

        while (nextToken.getType() == "DELETE") // Ignore all DELETE tokens
            nextToken = getToken(readnew);
    }

    // Build tree for the given string, type and number of children
    void buildTree(string val, string type, int child)
    {
        if (child == 0) // Leaf node
        {
            tree *temp = createNode(val, type);
            st.push(temp);
        }
        else if (child > 0) // Non-leaf node
        {
            stack<tree *> temp;
            int no_of_pops = child;
            while (!st.empty() && no_of_pops > 0)
            {
                temp.push(st.top());
                st.pop();
                no_of_pops--;
            }
            tree *tempLeft = temp.top();
            temp.pop();
            child--;
            if (!temp.empty() && child > 0)
            {
                tree *rightNode = temp.top();
                tempLeft->right = rightNode;
                temp.pop();
                child--;
                while (!temp.empty() && child > 0)
                {
                    tree *addRight = temp.top();
                    temp.pop();
                    rightNode->right = addRight;
                    rightNode = rightNode->right;
                    child--;
                }
            }
            tree *toPush = createNode(val, type);
            toPush->left = tempLeft;
            st.push(toPush);
        }
    }

    // Get the next token
    token getToken(char read[])
    {
        token t;
        int i = index;         // Index of character
        string id = "";        // Identifier
        string num = "";       // Number
        string isop = "";      // Operator
        string isString = "";  // String
        string isPun = "";     // Punctuation
        string isComment = ""; // Comment
        string isSpace = "";   // Space

        // Check if end of file is reached
        if (read[i] == '\0' || i == sizeOfFile)
        {
            t.setType("EOF");
            t.setVal("EOF");
            return t;
        }

    
}