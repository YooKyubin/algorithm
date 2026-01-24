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

    bool OOB()
    {
        return x < 0 || x >= 3 || y < 0 || y >= 3;
    }

    Coord operator+(const Coord& other) const
    {
        return { x + other.x, y + other.y };
    }
};

const vector<Coord> dirs = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

int GetID(int n, const string& board)
{
    for (int i = 0; i < 10; ++i)
    {
        if (board[i] - '0' == n)
        {
            return i;
        }
    }

    return -1;
}

Coord GetNextCoord(int currID, const Coord& dir)
{
    Coord currCoord = { currID / 3, currID % 3 };
    return currCoord + dir;
}

int CoordToID(const Coord& coord)
{
    return coord.x * 3 + coord.y;
}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string init;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            char temp;
            cin >> temp;
            init.push_back(temp);
        }
    }

    set<string> visited;
    visited.insert( init );
    queue<pair<string, int>> q;
    q.push({ init, 0 });

    int answer = -1;
    while (!q.empty())
    {
        string currBoard = q.front().first;
        int currDist = q.front().second;
        q.pop();

        if (currBoard == "123456780")
        {
            answer = currDist;
            break;
        }

        int currZero = GetID(0, currBoard);

        for (auto& dir : dirs)
        {
            Coord nextCoord = GetNextCoord(currZero, dir);
            int nextZero = CoordToID(nextCoord);

            if (nextCoord.OOB())
            {
                continue;
            }

            string nextBoard = currBoard;
            swap(nextBoard[currZero], nextBoard[nextZero]);

            if (visited.find(nextBoard) != visited.end())
            {
                continue;
            }

            visited.insert(nextBoard);
            q.push({ nextBoard, currDist + 1 });
        }
    }
    cout << answer << endl;

    return 0;
}
