#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> answer;

void search(int sum, string str,  int n, int idx, int sign, int pre)
{
    if (n < idx)
    {
        if (sum == 0)
        {
            answer.push_back(str);
        }   

        return;
    }

    search(sum + idx, str + "+" + to_string(idx), n, idx+1, 1, idx);
    search(sum - idx, str + "-" + to_string(idx), n, idx+1, -1, -idx);
    search(sum - pre + pre * 10 + idx * sign, str + " " + to_string(idx), n, idx+1, sign, pre * 10 + idx * sign);   
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

        sort(answer.begin(), answer.end());
        for (auto& a : answer)
            cout << a << "\n";

        answer.clear();
        cout << "\n";
    }


    return 0;
}