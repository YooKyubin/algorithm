#include <iostream>
#include <vector>
#include <cmath>

#define MAX_N 500'000

using namespace std;

int m;
int q;
vector<vector<int>> sparseTable;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> m;
    int log2maxN = ceil(log2(MAX_N));
    sparseTable.resize(log2maxN, vector<int>(m+1));

    for (int i=1; i<m+1; ++i)
    {
        cin >> sparseTable[0][i];
    }

    for (int i=1; i<log2maxN; ++i)
    {
        for (int j=1; j<m+1; ++j)
        {
            int half = sparseTable[i-1][j];
            sparseTable[i][j] = sparseTable[i-1][half];
        }
    }

    cin >> q;
    while (q--)
    {
        int n, x;
        cin >> n >> x;

        int step = x;
        for (int i=0; i<log2maxN; ++i)
        {
            if (n & 1 << i) // == 1
            {
                step = sparseTable[i][step];
            }
        }

        cout << step << "\n";
    }

    return 0;
}