#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int m, n, h;
vector<vector<vector<int>>> box;

struct Pos
{
    int x;
    int y;
    int z;

    Pos operator+(Pos input)
    {
        Pos ret;
        ret.x = this->x + input.x;
        ret.y = this->y + input.y;
        ret.z = this->z + input.z;
        return ret;
    }
};

vector<Pos> dir { {0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0} };

bool OOB(Pos input)
{
    return 
        input.x < 0 || input.x >= n || 
        input.y < 0 || input.y >= m || 
        input.z < 0 || input.z >= h;
}

queue<Pos> bfs(queue<Pos>& q)
{
    queue<Pos> ret;

    while (!q.empty())
    {
        Pos cur = q.front();
        q.pop();

        for (auto d : dir)
        {
            Pos next = cur + d;

            if (OOB(next))
                continue;

            if (box[next.z][next.x][next.y] == 0)
            {
                box[next.z][next.x][next.y] = 1;
                ret.push(next);
            }
        }
    }

    return ret;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> m >> n >> h;
    box = vector<vector<vector<int>>>(h, vector<vector<int>>(n, vector<int>(m)));
    queue<Pos> buffer;
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            for (int k=0; k<m; ++k)
            {
                int cell;
                cin >> cell;
                box[i][j][k] = cell;
                if (cell == 1)
                    buffer.push({j, k, i});
            }
        }
    }
    
    int cnt = 0;
    while (true)
    {
        buffer = bfs(buffer);
        if (buffer.empty())
            break;
        ++cnt;
    }
    

    for (int i=0; i<h; ++i)
        for (int j=0; j<n; ++j)
            for (int k=0; k<m; ++k)
                if (box[i][j][k] == 0)
                    cnt = -1;

    cout << cnt << endl;
    return 0;
}