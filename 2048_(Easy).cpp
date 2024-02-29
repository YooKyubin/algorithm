#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }

int n;
int answer = 0;

void Rotate(vector<vector<int>>& board) // right
{
    vector<vector<int>> rotated(n, vector<int>(n));

    for(int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            rotated[j][n-1 - i] = board[i][j];
        }
    }

    board = rotated;
}

void PushUp(vector<vector<int>>& board)
{
    vector<vector<bool>> changed(n, vector<bool>(n, false));

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            int cur = board[i][j];
            int ni = i-1;
            while (ni >= 0)
            {
                if (board[ni][j] != 0)
                    break;

                --ni;
            } // ni == -1 혹은 0이 아닌 위치

            if (ni < 0 || board[ni][j] != cur || changed[ni][j])
            {
                board[ni+1][j] = cur;
                if (ni != i -1)
                    board[i][j] = 0;
            }
            else //if (!changed[ni][j])
            {
                changed[ni][j] = true;
                board[ni][j] *= 2;
                board[i][j] = 0;
            }
        }
    }
}

int FindMax(const vector<vector<int>>& board)
{
    int m = 0;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            m = max(m, board[i][j]);
        }
    }

    return m;
}

void Print(vector<vector<int>>& board)
{
    for (int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void search(int depth, int maxDepth, vector<vector<int>> board)
{
    if (depth == maxDepth)
    {
        answer = max(FindMax(board), answer);

        return;
    }

    for (int i=0; i<4; ++i)
    {
        Rotate(board);
        vector<vector<int>> temp = board;
        PushUp(temp);
        search(depth+1, maxDepth, temp);
    }

}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    vector<vector<int>> board(n, vector<int>(n));
    for (int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            cin >> board[i][j];
        }
    }

    search(0, 5, board);
    cout << answer << endl;

    return 0;
}