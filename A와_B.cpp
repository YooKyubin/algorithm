#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool CanChange(string& s, string& t)
{
    while (s.length() < t.length())
    {
        switch (t.back())
        {
            case 'A':
            t.pop_back();
            break;
            
            case 'B':
            t.pop_back();
            reverse(t.begin(), t.end());
            break;
        }
    }

    return s == t;
}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string s, t;
    cin >> s;
    cin >> t;

    cout << CanChange(s, t) << endl;

    return 0;
}