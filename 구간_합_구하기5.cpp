#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> table(n, vector<int>(n));
    vector<vector<int>> prefixTable(n+1, vector<int>(n+1, 0));

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cin >> table[i][j];
        }
    }

    for (int i=1; i<n+1; ++i)
    {
        for (int j=1; j<n+1; ++j)
        {
            prefixTable[i][j] = prefixTable[i][j-1] + table[i-1][j-1];
        }
    }

    for (int i=1; i<n+1; ++i)
    {
        for (int j=1; j<n+1; ++j)
        {
            prefixTable[i][j] = prefixTable[i][j] + prefixTable[i-1][j];
        }
    }

    for (int i=0; i<m; ++i)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        --x1;
        --y1;
        int sum = prefixTable[x2][y2] - prefixTable[x1][y2] - prefixTable[x2][y1] + prefixTable[x1][y1];
        cout << sum << "\n";
    }

    return 0;
}