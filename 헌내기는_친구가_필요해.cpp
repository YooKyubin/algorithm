#include <vector>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Coord
{
    Coord(int x, int y)
    : x(x)
    , y(y)
    {
    }

    Coord operator+(const Coord& other) const
    {
        return Coord(x + other.x, y + other.y);
    }

    bool OOB(int n, int m)
    {
        return x < 0 || x >= n || y < 0 || y >= m;
    }

    int x;
    int y;
};

const static vector<Coord> dirs = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<string> campus(n);
    for (int i =0 ; i < n; ++i)
    {
        cin >> campus[i];
    }
    
    Coord start(0, 0);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (campus[i][j] == 'I')
            {
                start.x = i;
                start.y = j;
            }
        }
    }

    queue<Coord> q;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    q.push(start);
    visited[start.x][start.y] = true;

    int answer = 0;
    while (!q.empty())
    {
        Coord curr = q.front();
        q.pop();

        for (auto& dir : dirs)
        {
            Coord next = dir + curr;

            if (next.OOB(n, m))
            {
                continue;
            }

            if (campus[next.x][next.y] == 'X')
            {
                continue;
            }
            
            if (visited[next.x][next.y])
            {
                continue;
            }

            if (campus[next.x][next.y] == 'P')
            {
                ++answer;
            }

            visited[next.x][next.y] = true;
            q.push(next);
        }
    }

    if (answer == 0)
    {
        cout << "TT" << endl;
    }
    else
    {
        cout << answer << endl;
    }

    return 0;
}