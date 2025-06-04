#include <iostream>
#include <vector>
#include <string>

using namespace std;

int CountB(const vector<int>& numBAcc, int begin, int end)
{
    if (begin <= end)
    {
        return numBAcc[end + 1] - numBAcc[begin];
    }
    else
    {
        return numBAcc.back() - numBAcc[begin] + numBAcc[end + 1] - numBAcc[0];
    }
}

int main()
{
    string input;
    cin >> input;

    int length = (int)input.length();
    int numA = 0;
    for (char c : input)
    {
        if (c == 'a')
        {
            ++numA;
        }
    }
    vector<int> numBAcc(length + 1, 0);
    for (int i=0; i<length; ++i)
    {
        numBAcc[i+1] = numBAcc[i] + (input[i] == 'b' ? 1 : 0);
    }

    int changeCount = numA;
    for (int i=0; i < (int)input.length(); ++i)
    {
        int begin = i;
        int end = (i + numA - 1) % input.length();

        changeCount = min(changeCount, CountB(numBAcc, begin, end));
    }

    cout << changeCount << endl;

    return 0;
}