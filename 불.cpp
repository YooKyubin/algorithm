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

    bool OOB(int h, int w)
    {
        return x < 0 || x >= h || y < 0 || y >= w;
    }
    Coord operator+(const Coord& other) const
    {
        return { x + other.x, y + other.y };
    }
};

const vector<Coord> dirs = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

void Solve()
{
    int w, h;
    cin >> w >> h;
    const int INF = w * h;

    vector<string> board(h);
    for (int i = 0; i < h; ++i)
    {
        cin >> board[i];
    }

    queue<Coord> sanguen[2];
    queue<Coord> fires[2];
    // vector<vector<bool>> isFire(h, vector<bool>(w, false));
    vector<vector<int>> dist(h, vector<int>(w, INF));
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (board[i][j] == '@')
            {
                sanguen[0].push({ i, j });
                dist[i][j] = 0;
            }

            if (board[i][j] == '*')
            {
                fires[0].push({ i, j });
                // isFire[i][j] = true;
            }
        }
    }

    // simulate
    while (!fires[0].empty() || !sanguen[0].empty())
    {
        while (!fires[0].empty())
        {
            Coord curr = fires[0].front();
            fires[0].pop();

            for (Coord dir : dirs)
            {
                Coord next = curr + dir;
                if (next.OOB(h, w))
                {
                    continue;
                }

                if (board[next.x][next.y] == '#')
                {
                    continue;
                }

                if (board[next.x][next.y] == '*')
                {
                    continue;
                }

                board[next.x][next.y] = '*';
                fires[1].push(next);
            }
        }
        swap(fires[0], fires[1]);

        while (!sanguen[0].empty())
        {
            Coord curr = sanguen[0].front();
            sanguen[0].pop();

            for (Coord dir : dirs)
            {
                Coord next = curr + dir;

                if (next.OOB(h, w))
                {
                    cout << dist[curr.x][curr.y] + 1 << endl;
                    return;
                }

                if (board[next.x][next.y] == '#')
                {
                    continue;
                }

                if (board[next.x][next.y] == '*')
                {
                    continue;
                }

                if (dist[next.x][next.y] <= dist[curr.x][curr.y] + 1)
                {
                    continue;
                }

                dist[next.x][next.y] = dist[curr.x][curr.y] + 1;
                // board[next.x][next.y] = dist[next.x][next.y] + '0';
                sanguen[1].push(next);
            }
        }
        swap(sanguen[0], sanguen[1]);
    }

    cout << "IMPOSSIBLE" << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--)
    {
        Solve();
        // 큐 두개 쓰는 시뮬레이션,
        // 종료조건 주의하기!!
    }

    return 0;
}