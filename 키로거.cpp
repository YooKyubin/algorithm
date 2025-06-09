#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    freopen("input.txt", "r", stdin);

    int numTestcases = 0;
    cin >> numTestcases;
    while ( numTestcases-- )
    {
        string input;
        cin >> input;
        vector<char> leftCursor;
        vector<char> rightCursor;

        for (const char command : input)
        {
            switch(command)
            {
            case '<':
                if (!leftCursor.empty())
                {
                    const char lastChar = leftCursor.back();
                    leftCursor.pop_back();
                    rightCursor.push_back(lastChar);   
                }
                break;

            case '>':
                if (!rightCursor.empty())
                {
                    const char lastChar = rightCursor.back();
                    rightCursor.pop_back();
                    leftCursor.push_back(lastChar);
                }
                break;

            case '-':
                if (!leftCursor.empty())
                {
                    leftCursor.pop_back();
                }
                break;

            default:
                leftCursor.push_back(command);
                break;
            }
        }

        for (const char c : leftCursor)
        {
            cout << c;
        }
        reverse(rightCursor.begin(), rightCursor.end());
        for (const char c : rightCursor)
        {
            cout << c;
        }
        cout << "\n";
    }
    return 0;
}