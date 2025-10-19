#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> L(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> L[i];
    }
    vector<int> J(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> J[i];
    }

    vector<vector<int>> dpTable(n, vector<int>(101, 0));
    for (int i = 0; i <= 100; ++i)
    {
        if (L.front() < i)
        {
            dpTable[0][i] = J.front();
        }
    }

    for (int i = 1; i < n; ++i)
    {
        int life = L[i];
        int joy = J[i];
        for (int j = 0; j <= 100; ++j)
        {
            if (j <= life)
            {
                dpTable[i][j] = dpTable[i-1][j];
            }
            else
            {
                dpTable[i][j] = max(dpTable[i-1][j - life] + joy, dpTable[i-1][j]);
            }
        }
    }

    cout << *max_element(dpTable.back().begin(), dpTable.back().end()) << endl;

    return 0;
}
