// Student name: Berk Tinaz
// Studnet ID  : 40115829

// Submission deadline: Thursday, 28 March 2019, 2 pm

// Implement the functions evaluate_postfix() and evaluate_infix()

// Binary operators in the expression are delimited by white-space char.
// Operand with negative value (preceded with the minus sign) is allowed.
// Operands are delimited by white-space char or bracket (in the case of infix expression).

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cmath>  // pow(double x, double y), compute the value of x to power y

using namespace std;
bool isOperator(const string& expr, int i);
double evaluateOperator(char opr, const double& d1, const double& d2);
int precNum(char opr);
double nextOperand(const string& expr, int& i);

//------------------- function to evaluate postfix expression

double evaluate_postfix(const string& postfix_expr)
{
	stack<double> S;  // stack to store operands

	// You need to consider 3 cases:
	// 1. postfix_expr[i] is white-space char
	// 2. postfix_expr[i] is an operator
	// 3. postfix_expr[i] is the first char of an operand
	//    Use the function nextOperand() to extract the operand from the expression.
	
	int i = 0;
	char sym;
	double operand1;
	double operand2;
	double res;

	while (i < postfix_expr.length()) // read all input
	{
		sym = postfix_expr[i];

		if (iswspace(sym)) // skip whitespace
		{
			i++;
		}
		else if (isOperator(postfix_expr, i)) //if operator compute it using last 2 data
		{
			operand2 = S.top();
			S.pop();
			operand1 = S.top();
			S.pop();

			res = evaluateOperator(sym, operand1, operand2);
			S.push(res);

			i++;
		}
		else // add operand to stack
		{
			S.push(nextOperand(postfix_expr, i));
		}				
	}
	
	return S.top(); 
}

//------------------- function to evaluate infix expression

// You may define other supporting function if required.

double evaluate_infix(const string& infix_expr)
{
	stack<double> dataStack;  // stack to store operands
	stack<char> oprStack;     // stack to store operators and '('

	oprStack.push('@');  // bottom of stack symbol, with lowest precedence number

	// You need to consider 5 cases:
	// 1. infix_expr[i] is white-space char
	// 2. infix_expr[i] is '('
	// 3. infix_expr[i] is ')'
	// 4. infix_expr[i] is an operator
	// 5. infix_expr[i] is the first char of an operand
	//    Use the function nextOperand() to extract the operand from the expression.

	int i = 0;
	char sym;
	double operand1;
	double operand2;
	double res;

	while (i < infix_expr.length())
	{
		sym = infix_expr[i];

		if (iswspace(sym)) // skip if whitespace
		{
			i++;
		}
		else if (sym == '(') // add to opr stack if opening paranthesis
		{
			oprStack.push('(');
			i++;
		}
		else if (sym == ')') // if closing paranthesis process all operators until first opening paranthesis
		{
			while (oprStack.top() != '(')
			{
				operand2 = dataStack.top();
				dataStack.pop();
				operand1 = dataStack.top();
				dataStack.pop();

				dataStack.push( evaluateOperator(oprStack.top(), operand1, operand2) );
				oprStack.pop();
			}
			oprStack.pop(); // '(' removed
			i++;
		}
		else if (isOperator(infix_expr,i)) // if operator process all operators in the stack with higher precedence
		{
			while (precNum(oprStack.top()) >= precNum(sym))
			{
				operand2 = dataStack.top();
				dataStack.pop();
				operand1 = dataStack.top();
				dataStack.pop();
				
				dataStack.push(evaluateOperator(oprStack.top(), operand1, operand2));
				oprStack.pop(); // remove used operator
			}
			oprStack.push(sym); // add current operator
			i++;
		}
		else // if operand add to data stack
		{
			dataStack.push(nextOperand(infix_expr, i));
		}
	}

	// When you have reached the end of infix_expr, some operators and operands 
	// may be saved in the oprStack and dataStack.
	// You need to process the remaining operators to obtain the final result.

	while (oprStack.top() != '@') // process remaining operators in the stack
	{
		operand2 = dataStack.top();
		dataStack.pop();
		operand1 = dataStack.top();
		dataStack.pop();

		dataStack.push(evaluateOperator(oprStack.top(), operand1, operand2));
		oprStack.pop();
	}
	
	return dataStack.top(); 
}

// ---------------------------------------- functions given to you

bool isOperator(const string& expr, int i)
{
	// return true if the symbol (char) at index i of expr is an operator

	char c = expr[i];
	if (c == '+' || c == '*' || c == '/' || c == '$')
		return true;

	// not the minus sign of an operand
	if (c == '-' && (i+1 >= expr.length() || isspace(expr[i+1])))
		return true;

	return false;
}

double evaluateOperator(char opr, const double& d1, const double& d2)
{
	//This output statement is for debugging purpose.
	//cout << "evaluate " << d1 << " " << opr << " " << d2 << endl;

	switch (opr) 
	{
		case '+' : return d1 + d2;
		case '-' : return d1 - d2;
		case '*' : return d1 * d2;
		case '/' : return d1 / d2;
		case '$' : return pow(d1, d2);
		default : return 0;
	}
}

int precNum(char opr)
{
	// This function is used to support evaluate_infix()

	if (opr == '+' || opr == '-')
		return 1;
	if (opr == '*' || opr == '/')
		return 2;
	if (opr == '$')
		return 3;

	return 0; // default precedence number for '(' and '@'
}

double nextOperand(const string& expr, int& i)
{
	// return the value of the operand at index i of the expression
	// index i is advanced to the char that follows the extracted operand

	int j = i;
	while (j < expr.length() && !isspace(expr[j]) && expr[j] != ')' && expr[j] != '(')
		j++;

	string number = expr.substr(i, j-i);
	i = j;

	return stod(number);  // string to double conversion
}

int main()
{	
	cout << "----- Evaluate Postfix Expression -----" << endl << endl;

	ifstream infile("postfix_expr.txt");
	if (!infile.is_open())
	{
		cout << "Error: cannot open postfix_expr.txt" << endl;
		system("pause");
		exit(0);
	}

	string postfix_expr;
	while (getline(infile, postfix_expr))
	{
		double value = evaluate_postfix(postfix_expr);

		cout << "postfix expression: " << postfix_expr << " = " << value << endl << endl;
	}
	infile.close();

	cout << endl;
	cout << "----- Evaluate Infix Expression -----" << endl << endl;

	infile.open("infix_expr.txt");
	if (!infile.is_open())
	{
		cout << "Error: cannot open prefix_expr.txt" << endl;
		system("pause");
		exit(0);
	}

	string infix_expr;
	while (getline(infile, infix_expr))
	{		
		double value = evaluate_infix(infix_expr);
		cout << "infix expression: " << infix_expr << " = " << value << endl << endl;
	}	
	infile.close();

	system("pause");
	exit(0);
}