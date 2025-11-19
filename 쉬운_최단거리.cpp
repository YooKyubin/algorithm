#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Coord
{
    Coord(int x, int y)
    : x(x)
    , y(y)
    {}
    Coord()
    : x(0)
    , y(0)
    {}

    int x;
    int y;

    Coord operator+(const Coord other) const
    {
        return Coord(x + other.x, y + other.y);
    }

    bool OOB(int n, int m)
    {
        return x < 0 || x >= n || y < 0 || y >= m;
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> ground(n, vector<int>(m));
    Coord start;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> ground[i][j];
            if (ground[i][j] == 2)
            {
                start.x = i;
                start.y = j;
            }
            else if (ground[i][j] == 0)
            {
                dist[i][j] = 0;
            }
        }
    }

    queue<Coord> q;
    q.push(start);
    dist[start.x][start.y] = 0;

    const vector<Coord> dirs = 
    {
        Coord(0, 1),
        Coord(1, 0),
        Coord(0, -1),
        Coord(-1, 0),
    };

    while (!q.empty())
    {
        Coord curr = q.front();
        q.pop();

        for (const Coord& dir : dirs)
        {
            Coord next = curr + dir;

            if (next.OOB(n, m))
            {
                continue;
            }

            if (dist[next.x][next.y] != -1)
            {
                continue;
            }
            if (ground[next.x][next.y] == 0)
            {
                continue;
            }

            dist[next.x][next.y] = dist[curr.x][curr.y] + 1;
            q.push(next);
        }
    }

    for (auto& line : dist)
    {
        for (int i : line)
        {
            cout << i << " ";
        }
        cout << "\n";
    }

    return 0;
}