#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

struct Coord
{
    int x;
    int y;

    bool OOB()
    {
        return x < 0 || x >= 12 || y < 0 || y >= 12;
    }
    Coord operator+(const Coord& other) const
    {
        return { x + other.x, y + other.y };
    }
};

bool TryRemoveGroup(vector<string>& board, vector<vector<bool>>& visited, Coord start)
{
    static const vector<Coord> dirs = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };
    const char color = board[start.x][start.y];

    queue<Coord> q;
    vector<Coord> sameColorCoords;

    q.push(start);
    sameColorCoords.push_back(start);
    visited[start.x][start.y] = true;

    while (!q.empty())
    {
        Coord curr = q.front();
        q.pop();

        for (Coord dir : dirs)
        {
            Coord next = curr + dir;

            if (next.OOB())
            {
                continue;
            }

            if (board[next.x][next.y] != color)
            {
                continue;
            }

            if (visited[next.x][next.y])
            {
                continue;
            }

            visited[next.x][next.y] = true;
            sameColorCoords.push_back(next);
            q.push(next);
        }
    }

    if (sameColorCoords.size() < 4)
    {
        return false;
    }

    for (Coord coord : sameColorCoords)
    {
        board[coord.x][coord.y] = '.';
    }

    return true;
}

bool Pop(vector<string>& board)
{
    vector<vector<bool>> visited(12, vector<bool>(6, false));
    bool isPopped = false;

    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            if (board[i][j] == '.')
            {
                visited[i][j] = true;
                continue;
            }

            if (visited[i][j])
            {
                continue;
            }

            isPopped |= TryRemoveGroup(board, visited, { i, j });
        }
    }

    return isPopped;
}

void SimulateGravity(vector<string>& board)
{
    vector<vector<int>> blankCount(12, vector<int>(6, 0));

    for (int i = 11; i >= 1; --i)
    {
        for (int j = 0; j < 6; ++j)
        {
            blankCount[i-1][j] = blankCount[i][j];
            if (board[i][j] == '.')
            {
                ++blankCount[i-1][j];
            }
        }
    }

    for (int i = 11; i >= 0; --i)
    {
        for (int j = 0; j < 6; ++j)
        {
            int dist = blankCount[i][j];

            if (dist > 0)
            {
                board[i+dist][j] = board[i][j];
                board[i][j] = '.';
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    vector<string> board(12);
    for (int i = 0; i < 12; ++i)
    {
        cin >> board[i];
    }

    int chainCount = 0;
    while (true)
    {
        bool isPopped = Pop(board);
        if (!isPopped)
        {
            break;
        }

        SimulateGravity(board);
        ++chainCount;
    }

    cout << chainCount << endl;
    return 0;
}
