#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void Move(int src, int tmp, int dst, int i)
{
    if (i == 1)
    {
        cout << src << " " << dst << "\n";
    }
    else
    {
        Move(src, dst, tmp, i-1);
        cout << src << " " << dst << "\n";
        Move(tmp, src, dst, i-1);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);   

    int n;
    cin >> n;

    double numOperations = pow(2, n);
    string toString = to_string(numOperations);
    
    string result = toString.substr(0, toString.find('.'));
    result.back() -= 1;
    cout << result << endl;

    if (n <= 20)
    {
        Move(1, 2, 3, n);
    }

    return 0;
}