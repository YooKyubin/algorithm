#include <iostream>
#include <vector>
#include <string>

using namespace std;

void search(int sum, string str,  int n, int idx, int sign, int pre)
{
    if (n < idx)
    {
        if (sum == 0)
        {
            cout << str << "\n";
        }   

        return;
    }

    search(sum - pre + pre * 10 + idx * sign, str + " " + to_string(idx), n, idx+1, sign, pre * 10 + idx * sign);   
    search(sum + idx, str + "+" + to_string(idx), n, idx+1, 1, idx);
    search(sum - idx, str + "-" + to_string(idx), n, idx+1, -1, -idx);
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        int n;
        cin >> n;

        search(1, "1", n, 2, 1, 1);
        cout << "\n";
    }

    return 0;
}