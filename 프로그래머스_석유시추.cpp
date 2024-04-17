#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <set>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }

vector<pair<int, int>> dir { {0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int n, m;
vector<vector<int>> board;
vector<set<int>> positions;
vector<int> sizes;

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

int bfs(int x, int y, vector<vector<bool>>& visited, set<int>& position)
{
    int ret = 0;
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    ++ret;

    while (!q.empty())
    {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        position.insert(cy);

        for (auto d : dir)
        {
            int nx = cx + d.first;
            int ny = cy + d.second;

            if (OOB(nx, ny))
                continue;

            if (visited[nx][ny])
                continue;

            if (board[nx][ny] == 0)
                continue;

            visited[nx][ny] = true;
            q.push({nx, ny});
            ++ret;
        }
    }

    return ret;
}

int solution(vector<vector<int>> land) {
    int answer = 0;

    board = land;
    n = land.size();
    m = land[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            if (visited[i][j])
                continue;

            if (board[i][j] == 0)
                continue;

            set<int> pos;
            sizes.push_back(bfs(i, j, visited, pos));
            positions.push_back(pos);
        }
    }

    vector<int> sums (m, 0);
    for (int i=0; i<sizes.size(); ++i)
    {
        for (int pos : positions[i])
        {
            sums[pos] += sizes[i];
        }
    }

    for (int i=0; i<m; ++i)
    {
        answer = max(answer, sums[i]);
    }

    return answer;
}

vector<vector<int>> input {
    // {0, 0, 0, 1, 1, 1, 0, 0}, 
    // {0, 0, 0, 0, 1, 1, 0, 0}, 
    // {1, 1, 0, 0, 0, 1, 1, 0}, 
    // {1, 1, 1, 0, 0, 0, 0, 0}, 
    // {1, 1, 1, 0, 0, 0, 1, 1}};
    {1, 0, 1, 0, 1, 1}, 
    {1, 0, 1, 0, 0, 0}, 
    {1, 0, 1, 0, 0, 1}, 
    {1, 0, 0, 1, 0, 0}, 
    {1, 0, 0, 1, 0, 1}, 
    {1, 0, 0, 0, 0, 0}, 
    {1, 1, 1, 1, 1, 1}};

int main()
{
    cout << solution(input) << endl;
    return 0;
}