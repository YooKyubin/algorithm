#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>

using namespace std;

struct Coord
{
    int x;
    int y;

    Coord(int x, int y)
    : x(x), y(y)
    {}

    Coord(int id)
    : x(id / 5), y(id % 5)
    {}

    bool OOB()
    {
        return x < 0 || x >= 5 || y < 0 || y >= 5;
    }
    Coord operator+(const Coord& other)
    {
        return { x + other.x, y + other.y };
    }
    int GetID()
    {
        return x * 5 + y;
    }
};
static const vector<Coord> dirs = { {0,1}, {1,0}, {-1,0}, {0,-1} };

bool IsChained(int state)
{
    vector<Coord> coords;
    for (int i = 0; i < 25; ++i)
    {
        if (state & (1 << i))
        {
            coords.push_back(Coord(i));
        }
    }

    vector<vector<bool>> visited(5, vector<bool>(5, true));
    for (auto& coord : coords)
    {
        visited[coord.x][coord.y] = false;
    }

    queue<Coord> q;
    q.push(coords.front());
    visited[q.front().x][q.front().y] = true;

    while (!q.empty())
    {
        Coord curr = q.front();
        q.pop();

        for (auto& dir : dirs)
        {
            Coord next = curr + dir;

            if (next.OOB())
            {
                continue;
            }

            if (visited[next.x][next.y])
            {
                continue;
            }

            visited[next.x][next.y] = true;
            q.push(next);
        }
    }

    bool isAllVisited = true;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            isAllVisited &= visited[i][j];
        }
    }
    return isAllVisited;
}

void GetCombinations(int state, int id, int depth, vector<int>& results)
{
    if (depth == 7)
    {
        if (IsChained(state))
        {
            results.push_back(state);
        }
        return;
    }

    for (int i = id; i < 25; ++i)
    {
        GetCombinations(state | (1 << i), i + 1, depth + 1, results);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    vector<string> board(5);
    for (int i = 0; i < 5; ++i)
    {
        cin >> board[i];
    }

    vector<int> results;
    vector<vector<int>> neighborCount(5, vector<int>(5, 0));
    GetCombinations(0, 0, 0, results);

    int answer = 0;
    for (int result : results)
    {
        int cntS = 0;
        for (int i = 0; i< 25; ++i)
        {
            if (result & (1 << i))
            {
                Coord coord(i);
                if (board[coord.x][coord.y] == 'S')
                {
                    ++cntS;
                }
            }
        }

        if (cntS > 3)
        {
            ++answer;
        }
    }

    cout << answer << endl;

    return 0;
}
