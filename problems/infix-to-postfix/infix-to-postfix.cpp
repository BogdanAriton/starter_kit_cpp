/*
We need transform an expression from an infix type to a postfix type
Infix is normal mathematic expression:
    A+B*C
    A+(B*C)
Postfix is more machine friendly, the expression above in postfix will be:
    ABC*+ => the operands will be evaluated from left to right
    ABC are operands
    When we first encounter a operation like (*, +, -, \) we need to apply them to the operands in order left to right
    in this case ABC encounters * which will be applied to the last two operands = B and C
    the result will be a new operand added to the stack AD+
    We will see that we encounter + which uses two operands and will add A and D( the result to the previous multiplication )
    A+D

Postfix is a good approach to be used with stack which is why we have chosen this format

Infix to postfix conversion:
    given an expression: A+(B*C)\(X-F+N)
        - we parse the expression from left and add operands to a stack and operators to a different stack based on the their precedence
            - the operators will be added to the operators stack only if higher precedence is not violated
            precedence rule: * > / > + > -
            - if a lower precedence operator needs to be pushed on the the operators stack then we will pop what we have in the list and put them into the first stack
            - then we add the one with lower precedence
        - if we find a parantesis we will just push on the the operator stack and wait until we find it's match - whenver we find the match we pop the stack until we find the match 
*/

#include <stack>
#include <string>
#include <iostream>
#include <unordered_map>

static std::unordered_map<char, int> oprValue({{'*', 3}, {'\\', 3}, {'+', 2}, {'-', 2}, {')', 1}}, 5);

bool isOperator(const char &value)
{
    for (auto &ch : {'(', ')', '*', '\\', '+', '-'})
    {
        if (value == ch)
        {
            return true;
        }
    }
    return false;
};

int main()
{
    //std::string expression = "A+(B*C)\\(X-F+N)";
    //std::string expression = "A+B*C\\X-F+N";
    std::string expression = "A+B*(C\\X-(F+N)+(A*B-C))";


    std::stack<char> operators{};
    std::deque<char> results{};

    for (int i = 0; i < expression.size(); ++i)
    {
        if (isOperator(expression[i]))
        {
            if (operators.empty())
            {
                operators.push(expression[i]);
            }
            else
            {
                if (oprValue[expression[i]] > oprValue[operators.top()] || expression[i] == '(')
                {
                    operators.push(expression[i]);
                }
                else if (oprValue[expression[i]] == oprValue[operators.top()])
                {
                    results.push_back(operators.top());
                    operators.pop();
                    operators.push(expression[i]);
                }
                else
                {
                    while (!operators.empty() && operators.top() != '(')
                    {
                        results.push_back(operators.top());
                        operators.pop();
                    }
                    if (expression[i] != ')')
                    {
                        operators.push(expression[i]);
                    }
                    if (expression[i] == ')' && operators.top() == '(')
                    {
                        operators.pop();
                    }
                }
            }
        }
        else
        {
            results.push_back(expression[i]);
        }
    }

    while (operators.size() > 0)
    {
        results.push_back(operators.top());
        operators.pop();
    }

    std::cout << "Infix expression = " << expression << '\n';
    std::cout << "Postfix expression = ";
    for (auto& item: results)
    {
        std::cout << item;
    }
    std::cout << '\n';
}