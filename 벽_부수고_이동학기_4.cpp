#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int n, m;
vector<vector<int>> room;
vector<vector<int>> indices;
vector<int> area;
vector<pair<int, int>> dir { {0,1}, {1,0}, {-1,0}, {0, -1} };

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}


int dfs(int idx, int curx, int cury, vector<vector<bool>>& visited)
{
    visited[curx][cury] = true;
    indices[curx][cury] = idx;
    
    int sum = 0;
    for (auto d : dir)
    {
        int nx = curx + d.first;
        int ny = cury + d.second;

        if (OOB(nx, ny))
            continue;

        if (visited[nx][ny])
            continue;

        if (room[nx][ny] == 1)
            continue;
        
        sum += dfs(idx, nx, ny, visited) + 1;
    }

    return sum;
}

void makeSet()
{
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int idx = 0;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            if (room[i][j] == 1)
                continue;

            if (visited[i][j])
                continue;
            
            int sum = dfs(idx, i, j, visited)+1;
            // area[idx] = sum;
            area.push_back(sum);
            ++idx;
        }
    }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    room.resize(n, vector<int>(m));
    indices.resize(n, vector<int>(m, -1));
    // area.reserve(n * m);
    // area.resize(n * m);
    for (int i=0; i<n; ++i)
    {
        string input;
        cin >> input;
        for (int j=0; j<m; ++j)
            room[i][j] = input[j] - '0';
    }
    makeSet();

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            if(room[i][j] == 0)
            {
                cout << 0;
                continue;
            }

            int sum = 0;
            set<int> unique;
            for (auto d : dir)
            {
                int nx = i + d.first;
                int ny = j + d.second;

                if (OOB(nx, ny))
                    continue;
                
                int nIdx = indices[nx][ny];
                if (unique.find(nIdx) != unique.end())
                    continue;

                if (nIdx == -1)
                    continue;

                unique.insert(nIdx);
                sum += area[nIdx];
            }
            cout << (sum + 1) % 10;
        }
        cout << "\n";
    }
    
    return 0;
}