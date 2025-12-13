#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int maxMove = 200 * 200 + 1;

struct Coord
{
    Coord(int x, int y)
    : x(x)
    , y(y)
    {}

    Coord operator+(const Coord& other)
    {
        return Coord(x + other.x, y + other.y);
    }

    bool OOB(int h, int w)
    {
        return x < 0 || x >= h || y < 0 || y >= w;
    }

    int x;
    int y;
};

const vector<Coord> dirs = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} }; 
const vector<Coord> jump = { {-2, 1}, {1, -2}, {-1, -2}, {-2, -1}, {2, 1}, {1, 2}, {-1, 2}, {2, -1} };

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int k;
    cin >> k;

    int w, h;
    cin >> w >> h;
    
    vector<vector<int>> board(h, vector<int>(w));
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            cin >> board[i][j];
        }
    }

    vector<vector<vector<int>>> dist(k + 1, vector<vector<int>>(h, vector<int>(w, maxMove)));
    queue<pair<Coord, int>> q; // coord, jump count

    dist[0][0][0] = 0;
    q.push({ Coord(0, 0), 0 });

    while (!q.empty())
    {
        Coord curr = q.front().first;
        int jumpCount = q.front().second;
        q.pop()

        // 일반 움직임
        for (const Coord& dir : dirs)
        {
            Coord next = curr + dir;

            if (next.OOB(h, w))
            {
                continue;
            }

            if (dist[jumpCount][next.x][next.y] != maxMove)
            {
                continue;
            }

            if (board[next.x][next.y] == 1)
            {
                continue;
            }

            dist[jumpCount][next.x][next.y] = dist[jumpCount][curr.x][curr.y] + 1;
            q.push({ next, jumpCount });
        }

        if (jumpCount >= k)
        {
            continue;
        }

        // 말 움직임
        for (const Coord& dir : jump)
        {
            Coord next = curr + dir;

            if (next.OOB(h, w))
            {
                continue;
            }

            if (dist[jumpCount + 1][next.x][next.y] != maxMove)
            {
                continue;
            }

            if (board[next.x][next.y] == 1)
            {
                continue;
            }

            dist[jumpCount + 1][next.x][next.y] = dist[jumpCount][curr.x][curr.y] + 1;
            q.push({ next, jumpCount + 1 });
        }
    }

    int answer = maxMove;
    for (auto& plane : dist)
    {
        answer = min(answer, plane[h-1][w-1]);
    }
    cout << (answer == maxMove ? -1 : answer) << endl;

    return 0;
}