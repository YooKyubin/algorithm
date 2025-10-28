#include <iostream>
#include <vector>
#include <string>

using namespace std;
//19:38

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    string input;
    cin >> input;

    vector<vector<int>> stacks(1, vector<int>(1, 0));
    bool validate = true;

    if (input.length() % 2 != 0)
    {
        validate = false;
    }


    
    for (char ch : input)
    {
        switch (ch)
        {
        case '(':
            stacks.push_back(vector<int>(1, 2));
            break;

        case ')':
        {
            vector<int>& lastStack = stacks.back();
            if (lastStack.front() != 2)
            {
                validate = false;
                break;
            }
            
            int sum = 0;
            // for (int num : stacks.back())
            for (int i = 1; i < (int)lastStack.size(); ++i)
            {
                sum += lastStack[i];
            }
            stacks.pop_back();
            stacks.back().push_back(sum == 0 ? 2 : sum * 2);
            break;
        }

        case '[':
            stacks.push_back(vector<int>(1, 3));
            break;
        
        case ']':
        {
            vector<int>& lastStack = stacks.back();
            if (lastStack.front() != 3)
            {
                validate = false;
                break;
            }
            int sum = 0;
            // for (int num : stacks.back())
            for (int i = 1; i < (int)lastStack.size(); ++i)
            {
                sum += lastStack[i];
            }
            stacks.pop_back();
            stacks.back().push_back(sum == 0 ? 3 : sum * 3);
            break;
        }
        }

        if (false == validate)
        {
            break;
        }
    }

    if (stacks.size() != 1)
    {
        validate = false;
    }

    if (validate)
    {
        int answer = 0;
        for (int i : stacks.back())
        {
            answer += i;
        }
        cout << answer << endl;
    }
    else
    {
        cout << 0 << endl;
    }
        

    return 0;
}