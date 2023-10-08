#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string input;
    vector<string> arr;
    cin >> input;
    for (int i=0; i<input.length(); ++i)
    {
        arr.push_back(input.substr(i));
    }

    sort(arr.begin(), arr.end());

    for (auto a : arr)
    {
        cout << a << '\n';
    }
    return 0;
}