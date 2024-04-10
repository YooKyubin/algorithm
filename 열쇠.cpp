#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

vector<pair<int, int>> dir { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

bool OOB(int x, int y, int n, int m)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

void Sovle()
{
    int n, m;
    cin >> n >> m;

    vector<vector<char>> floorPlan(n+2, vector<char>(m+2, '.'));
    vector<pair<int, int>> startPos;
    vector<bool> keys('Z'+1, false);
    vector<vector<pair<int, int>>> lockPos('Z' + 1);
    int cnt = 0;

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            cin >> floorPlan[i+1][j+1];
        }
    }

    string inputKeys;
    cin >> inputKeys;
    for (int i=0; i<inputKeys.size(); ++i)
    {
        keys[ inputKeys[i] - 32 ] = true;
        // keys[ inputKeys[i] - ('a' - 'A') ] = true;
    }

    // 테두리 패딩 만들어서 구현
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(n+2, vector<bool>(m+2, false));

    q.push({0, 0});
    visited[0][0] = true;

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (auto d : dir)
        {
            int nx = x + d.first;
            int ny = y + d.second;

            if (OOB(nx, ny, n+2 , m+2))
                continue;

            char nextChar = floorPlan[nx][ny];

            if (visited[nx][ny])
                continue;

            if (nextChar == '*')
                continue;

            if ('A' <= nextChar && nextChar <= 'Z')
            {
                if (!keys[ nextChar ])
                {
                    lockPos[nextChar].push_back({nx, ny});
                    continue;
                }
            }
            else if ('a' <= nextChar && nextChar <= 'z')
            {
                keys[nextChar - 32] = true;
                for (auto pos : lockPos[nextChar - 32])
                {
                    if (visited[pos.first][pos.second])
                        continue;

                    q.push(pos);
                    visited[pos.first][pos.second] = true;
                }
            }

            if (nextChar == '$')
                ++cnt;

            q.push({nx, ny});
            visited[nx][ny] = true;
            
        }
    }

    cout << cnt << "\n";
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        Sovle();
    }
    return 0;
}