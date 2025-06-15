#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int Compute(int operationPriority, const string& expression)
{
    string postExpression;
    vector<char> stack;

    for (size_t i=0; i < expression.size(); ++i)
    {
        char ch = expression[i];
        if (i % 2 == 0)
        {
            postExpression.push_back(ch);
        }
        else
        {
            if (!stack.empty() && (! (operationPriority & 1 << (i / 2))))
            {
                while(!stack.empty())
                {
                    char prevOp = stack.back();
                    stack.pop_back();
                    postExpression.push_back(prevOp);
                }
            }

            stack.push_back(ch);
        }
    }
    while(!stack.empty())
    {
        postExpression.push_back(stack.back());
        stack.pop_back();
    }

    vector<int> operand;
    for (char ch : postExpression)
    {
        if (isdigit(ch))
        {
            operand.push_back(ch - '0');
        }
        else
        {
            int operand1 = 0;
            int operand2 = 0;
            switch (ch)
            {
            case '+':
                operand1 = operand.back();
                operand.pop_back();
                operand2 = operand.back();
                operand.pop_back();

                operand.push_back(operand1 + operand2);
                break;

                case '-':
                operand1 = operand.back();
                operand.pop_back();
                operand2 = operand.back();
                operand.pop_back();

                operand.push_back(operand2 - operand1);
                break;

                case '*':
                operand1 = operand.back();
                operand.pop_back();
                operand2 = operand.back();
                operand.pop_back();

                operand.push_back(operand1 * operand2);
                break;
            }
        }
    }

    return operand[0];
}

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    freopen("../../input.txt", "r", stdin);

    int n;
    cin >> n;
    string expression;
    cin >> expression;

    int maxResult = INT32_MIN;
    for (int i=0; i< (1 << n); ++i)
    {
        bool isValidPriority = true;
        for (int j = 1; j < n; ++j)
        {
            if (i & (1 << j))
            {
                if (i & (1 << (j-1)))
                {
                    isValidPriority = false;
                    break;
                }
            }
        }

        if (isValidPriority)
        {
            maxResult = max(maxResult, Compute(i, expression));
        }
    }
    cout << maxResult << endl;
    // cout << Compute(10, expression) << endl;

    return 0;

}