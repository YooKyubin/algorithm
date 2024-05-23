#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

inline int max(int a, int b) { return a > b ? a : b; }

int n, m;
vector<vector<int>> walls;
vector<int> head;
set<int> rooms;
map<int, int> roomSizes;

// 서 북 동 남
vector<pair<int, int>> dir {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

void Init()
{
    for (int i=0; i<n*m; ++i)
    {
        head[i] = i;
    }
}

int Find(int x)
{
    if (head[x] == x)
        return x;

    return head[x] = Find(head[x]);
}

int Find(int x, int y)
{
    return Find(x * m + y);
}

void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if (x == y)
        return;

    // head[x] = y;
    head[y] = x;
}

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

int BFS(int x, int y, vector<vector<bool>>& visited)
{
    int roomSize = 0;
    // vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    ++roomSize;

    while (!q.empty())
    {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        for (int i=0; i<4; ++i)
        {
            int nx = curX + dir[i].first;
            int ny = curY + dir[i].second;

            if (OOB(nx, ny))
                continue;

            if (visited[nx][ny])
                continue;

            if (walls[curX][curY] & 1 << i)
                continue;

            Union(curX * m + curY, nx * m + ny);
            visited[nx][ny] = true;
            q.push({nx, ny});
            ++roomSize;

        }
    }

    return roomSize;
}

void Set_Group()
{
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            if (visited[i][j])
                continue;

            int roomSize = BFS(i, j, visited);
            roomSizes[Find(i * m + j)] = roomSize;
        }
    }
}

int Find_MaxSize_With_Break()
{
    int maxRoom = 0;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            int curRoom = Find(i, j);

            for (auto d : dir)
            {
                int nx = i + d.first;
                int ny = j + d.second;

                if (OOB(nx, ny))
                    continue;

                if (curRoom == Find(nx, ny))
                    continue;

                maxRoom = max(maxRoom, roomSizes[curRoom] + roomSizes[Find(nx, ny)]);
            }
        }
    }

    return maxRoom;
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> m >> n;
    walls.resize(n, vector<int>(m));
    head.resize(n * m);
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            cin >> walls[i][j];
        }
    }
    Init();

    Set_Group();

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            rooms.insert(Find(i * m + j));
        }
    }

    cout << rooms.size() << endl;
    int maxRoomSize = 0;
    for (int i : rooms)
    {
        maxRoomSize = max(maxRoomSize, roomSizes[i]);
    }
    cout << maxRoomSize << endl;

    cout << Find_MaxSize_With_Break() << endl;

    return 0;
}