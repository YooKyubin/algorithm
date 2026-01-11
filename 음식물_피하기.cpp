#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Coord
{
    int x; 
    int y;

    Coord operator+(const Coord& other) const
    {
        return {x + other.x, y + other.y};
    }

    bool OOB(int n, int m) const
    {
        return x < 0 || x >= n || y < 0 || y >= m;
    }
};

const vector<Coord> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int main()
{
    freopen("../../input.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<bool>> hallway(n,vector<bool>(m, false));
    for (int i = 0; i < k; ++i)
    {
        int r, c;
        cin >> r >> c;
        --r;
        --c;

        hallway[r][c] = true;
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int maxSize = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (hallway[i][j] == false)
            {
                continue;
            }
            if(visited[i][j])
            {
                continue;
            }

            int size = 0;
            queue<Coord> q;
            q.push({i, j});
            visited[i][j] = true;

            while (!q.empty())
            {
                Coord curr = q.front();
                q.pop();
                ++size;
                
                for (auto& dir : dirs)
                {
                    Coord next = curr + dir;
                    if (next.OOB(n, m))
                    {
                        continue;
                    }
                    
                    if (hallway[next.x][next.y] == false)
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

            maxSize = max(maxSize, size);
        }
    }

    cout << maxSize << endl;

    return 0;
}