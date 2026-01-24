#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

struct Coord
{
    int x;
    int y;

    bool OOB(int r, int c)
    {
        return x < 0 || x >= r || y < 0 || y >= c;
    }
    Coord operator+(const Coord& other)
    {
        return { x + other.x, y + other.y };
    }
};

const vector<Coord> dirs = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

int DFS(Coord curr, int depth, vector<vector<bool>>& visited, const int k, const vector<string>& board)
{
    if (depth == k)
    {
        if (curr.x == 0 && curr.y == board.back().size() - 1)
        {
            return 1;
        }
        return 0;
    }

    int cnt = 0;
    for (auto& dir : dirs)
    {
        Coord next = curr + dir;

        if (next.OOB(board.size(), board.front().size()))
        {
            continue;
        }

        if (board[next.x][next.y] == 'T')
        {
            continue;
        }

        if (visited[next.x][next.y])
        {
            continue;
        }

        visited[next.x][next.y] = true;
        cnt += DFS(next, depth + 1, visited, k, board);
        visited[next.x][next.y] = false;
    }

    return cnt;
}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int r, c, k;
    cin >> r >> c >> k;

    vector<string> board(r);
    for (int i = 0; i < r; ++i)
    {
        cin >> board[i];
    }

    vector<vector<bool>> visited(r, vector<bool>(c, false));
    visited[r-1][0] = true;
    cout << DFS({ r-1, 0 }, 1, visited, k, board) << endl;

    return 0;
}
