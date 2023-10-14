#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    string str;
    map<string, int> dict;
    int cnt = 0;
    while (getline(cin, str, '\n'))
    {
        ++cnt;
        ++dict[str];
    }

    cout << fixed;
    cout.precision(4);
    for (auto tree : dict)
    {
        cout << tree.first << " " << (float)tree.second / float(cnt) * 100 << endl;
    }
    return 0;
}