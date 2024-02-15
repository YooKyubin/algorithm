#include <iostream>
#include <string>

using namespace std;

int n;
string input;
string target;

void toggle(char& a )
{
    a = a == '0' ? '1' : '0';
}

int Change(string& bulbs)
{
    int sum = 0;
    for (int i=1; i<n; ++i)
    {
        if (bulbs[i-1] != target[i-1])
        {
            ++sum;

            toggle(bulbs[i-1]);
            toggle(bulbs[i]);
            if (i+1 < n) 
                toggle(bulbs[i+1]);
        }
    }

    return sum;
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;

    cin >> input;
    cin >> target;

    string cur = input;
    string switched = input;
    toggle(switched[0]);
    toggle(switched[1]);

    int curSum = Change(cur);
    int switchedSum = Change(switched)+1;

    if (cur.back() == target.back())
        cout << curSum << endl;

    else if (switched.back() == target.back())
        cout << switchedSum << endl;
        
    else
        cout << -1 << endl;

    return 0;
}