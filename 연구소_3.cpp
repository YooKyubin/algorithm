#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> dir { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };

int n, m;
vector<vector<int>> lab;
vector<pair<int, int>> virusPos;
vector<int> combination;
int minDist = INT32_MAX;

int numRemaining = 0;

int max(int a, int b) { return a > b ? a : b; }

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= n;
}

int GetMaxDist(const vector<int>& virus)
{
    int maxDist = 0;
    int cntBlank = 0;

    queue<pair<int, int>> q;
    vector<vector<int>> dist(n, vector<int>(n, INT32_MAX));
    for (int virusIdx : virus)
    {
        pair<int, int> pos = virusPos[virusIdx];
        q.push({pos});
        dist[pos.first][pos.second] = 0;
    }
    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (const auto& d : dir)
        {
            int nx = x + d.first;
            int ny = y + d.second;

            if (OOB(nx, ny))
                continue;

            if (dist[nx][ny] <= dist[x][y] + 1)
                continue;

            if (lab[nx][ny] == 1)
                continue;

            dist[nx][ny] = dist[x][y]+1;
            q.push({nx, ny});

            if (lab[nx][ny] == 0)
            {
                ++cntBlank;
                maxDist = max(maxDist, dist[nx][ny]);
            }
        }
    }

    if (cntBlank < numRemaining)
        maxDist = INT32_MAX;

    return maxDist;
}

void GetCombination(int idx, int depth)
{
    if (depth == m)
    {
        minDist = min(minDist, GetMaxDist(combination));
        return;
    }

    for (int i=idx; i<virusPos.size(); ++i)
    {
        combination.push_back(i);
        GetCombination(i+1, depth+1);
        combination.pop_back();
    }
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin >> n >> m;
    lab.resize(n, vector<int>(n));

    for(int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cin >> lab[i][j];

            if (lab[i][j] == 0)
                ++numRemaining;
            else if (lab[i][j] == 2)
                virusPos.push_back({i, j});
        }
    }
    
    GetCombination(0, 0);

    if (minDist == INT32_MAX)
        minDist = -1;
    cout << minDist << endl;

    return 0;
}