#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<pair<int, int>> dir { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };

int n;
vector<vector<int>> space;

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= n;
}

pair<pair<int, int>, int> Find(int x, int y, int size)
{
    queue<pair<int, int>> q;
    vector<vector<int>> visited(n, vector<int>(n, INT32_MAX));
    q.push({x, y});
    visited[x][y] = 0;

    vector<vector<bool>> temp(n, vector<bool>(n, false));

    vector<pair<int, int>> fishes;
    int minDist = INT32_MAX;

    while (!q.empty())
    {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        if (minDist <= visited[cx][cy])
            break;

        for (const auto& d : dir)
        {
            int nx = cx + d.first;
            int ny = cy + d.second;

            if (OOB(nx, ny))
                continue;

            if (visited[nx][ny] <= visited[cx][cy] + 1)
                continue;

            if (space[nx][ny] > size)
                continue;

            visited[nx][ny] = visited[cx][cy] + 1;
            q.push({nx, ny});

            temp[nx][ny] = true;

            if (space[nx][ny] != 0 && space[nx][ny] < size && minDist >= visited[nx][ny])
            {
                minDist = visited[nx][ny];
                fishes.push_back({nx, ny});
            }
        }
    }

    if (fishes.empty())
        return { pair<int, int>{-1, -1}, -1};
    else
    {
        sort(fishes.begin(), fishes.end());
        space[fishes.front().first][fishes.front().second] = 0;
        return { fishes.front(), minDist };
    }
}

int main()
{
    // freopen("../../input.txt", "r", stdin);

    cin >> n;

    int timeElapse = 0;
    int size = 2;
    int quota = size;

    space.resize(n, vector<int>(n));
    pair<int, int> shark;

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cin >> space[i][j];
            if (space[i][j] == 9)
            {
                shark = {i, j};
                space[i][j] = 0;
            }
        }
    }

    while (true)
    {
        pair<pair<int, int>, int> ret = Find(shark.first, shark.second, size);
        pair<int, int> pos = ret.first;

        if (pos.first == -1)
            break;
        
        timeElapse += ret.second;

        shark = pos;
        --quota;
        if (quota == 0)
        {
            ++size;
            quota = size;
        }
    }

    cout << timeElapse << endl;
    return 0;
}