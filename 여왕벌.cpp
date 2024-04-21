#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> board;
vector<int*> selfGrowth;

int max (int a, int b) { return a > b ? a : b; }

int main()
{
    freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> m >> n;
    board.resize(m, vector<int>(m, 1));

    for (int i=m-1; i>=0; --i)
    {
        selfGrowth.push_back(&board[i][0]);
    }
    for (int i=1; i<m; ++i)
    {
        selfGrowth.push_back(&board[0][i]);
    }

    vector<int> temp (2 * m, 0);

    while(n--)
    {
        int idx = 0;

        for (int i=0; i<3; ++i)
        {
            int input;
            cin >> input;

            idx += input;
            temp[idx] += 1;
        }
    }

    *selfGrowth[0] = 1 + temp[0];
    for (int i=1; i<2*m - 1; ++i)
    {
        *selfGrowth[i] = *selfGrowth[i-1] + temp[i];
    }

    for (int i=0; i<m; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            if (i >= 1 && j >= 1)
                cout << max(board[i][0], board[0][j]) << " ";
            else
                cout << board[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}