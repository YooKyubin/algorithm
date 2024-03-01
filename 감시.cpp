#include <iostream>
#include <vector>

using namespace std;

struct CCTV
{
    pair<int, int> pos;
    int num;
};

int min(int a, int b) { return a < b ? a : b; }

vector<pair<int, int>> dir { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int n, m;
int answer = INT32_MAX;
vector<CCTV> cctvs;
vector<vector<vector<int>>> rotations
{
    { },
    { {0}, {1}, {2}, {3} },                             // 1
    { {0, 2}, {1, 3} },                                 // 2
    { {0, 1}, {1, 2}, {2, 3}, {3, 0} },                 // 3
    { {0, 1, 2}, {1, 2, 3}, {2, 3, 0}, {3, 0, 1} },     // 4
    { {0, 1, 2, 3} }                                    // 5
};

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

void fill(int x, int y, vector<int>& n, vector<vector<int>>& office)
{
    for (int d : n)
    {
        int cx = x;
        int cy = y;

        while (true)
        {
            int nx = cx + dir[d].first;
            int ny = cy + dir[d].second;
            if (OOB(nx, ny))
                break;

            if (office[nx][ny] == 6)
                break;

            cx = nx;
            cy = ny;
            office[cx][cy] = 7;
        }
    }
}

int countZero(vector<vector<int>>& office)
{   
    int ret = 0;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            if (office[i][j] == 0)
                ++ret;
        }
    }
    return ret;
}

void search(int depth, int maxDepth, vector<vector<int>>& office) //DFS
{
    if (depth == maxDepth)
    {
        answer = min(answer, countZero(office));
        return;
    }

    int cctvNum = cctvs[depth].num;
    int x = cctvs[depth].pos.first;
    int y = cctvs[depth].pos.second;
    for (vector<int>& n : rotations[cctvNum])
    {
        vector<vector<int>> temp = office;
        fill(x, y, n, temp);
        search(depth+1, maxDepth, temp);
    }

}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    vector<vector<int>> office;
    office.resize(n, vector<int>(m));
    
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            cin >> office[i][j];
            if (office[i][j] != 0 && office[i][j] != 6)
            {
                cctvs.push_back({{i, j}, office[i][j]});
            }
        }
    }

    search(0, cctvs.size(), office);

    cout << answer << endl;

    return 0;
}