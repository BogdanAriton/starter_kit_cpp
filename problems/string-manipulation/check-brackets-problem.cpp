/*
The problem asks that you check if a series of brackets are opened and closed correctly

We will solve this problems using a stack.
The implementation below also return the position of the element that was either not closed or opened correctly.
It will only care about the first item that is found in this situation.
*/

#include <iostream>
#include <stack>
#include <deque>
#include <vector>

bool isPair(const char& left, const char& right)
{
    if (right == ')' && left == '(')
    {
        return true;
    }
    
    if (right == ']' && left == '[')
    {
        return true;
    }

    if (right == '}' && left == '{')
    {
        return true;
    }

    return false;
}

void checkBracket(const std::string& brackets)
{
    std::stack<std::pair<char, int>> myStack;
    for (int i = 0; i < brackets.size(); ++i)
    {
        if (brackets[i] == ')' || brackets[i] == ']' || brackets[i] == '}')
        {
            if (!myStack.empty())
            {
                std::cout << "Found  item: " << brackets[i] << '\n';
                if (isPair(myStack.top().first, brackets[i]))
                {
                    std::cout << "Poping item: " << myStack.top().first << '\n';
                    myStack.pop();
                }
                else
                {
                    std::cout << "Element " << brackets[i] << " at position: " << i << " has no corresponding opening" << '\n';
                    return;
                }
            }
        }
        else
        {
            std::cout << "Adding item: " << brackets[i] << '\n';
            myStack.push({brackets[i], i});
        }
    }

    while (!myStack.empty())
    {
        if (myStack.top().first == '(' || myStack.top().first == '[' || myStack.top().first == '{')
        {
            std::cout << "Element " << myStack.top().first << " at position: " << myStack.top().second << " was never closed" << '\n';
            myStack.pop();
        }
    }
    return;
}

int main()
{
    // {([{(){()}}])}
    // we will add items to the que until we encouter a reversed paranthesis
    // when we do we will pop the one before an will not add it to the list until the queue is empty

    // Cases:
    // good case: {([{(){()}}])}
    // bad case : {(})}
    // bad case: {[{{{{(((())))}}}}}]}
    
    checkBracket("{{[{{{{(((())))}}}}]}");
    
}