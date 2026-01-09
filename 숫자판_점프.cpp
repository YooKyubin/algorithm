#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

const vector<int> dx = { 0, 0, 1, -1 };
const vector<int> dy = { -1, 1, 0, 0 };

using Board = vector<vector<int>>;

void Find(int x, int y, int depth, int number, const Board& board, set<int>& visited)
{
    int nextNumber = number * 10 + board[x][y];
    if (depth == 6)
    {
        visited.insert(number);
        return;
    }

    for (int i = 0; i < 4; ++i)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5)
        {
            continue;
        }

        Find(nx, ny, depth + 1, nextNumber, board, visited);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    Board board(5, vector<int>(5));
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            cin >> board[i][j];
        }
    }

    set<int> visited;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            Find(i, j, 0, 0, board, visited);
        }
    }
    cout << visited.size() << endl;
    
    return 0;
}
