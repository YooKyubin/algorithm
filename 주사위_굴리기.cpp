#include <iostream>
#include <vector>

using namespace std;

struct vec3 
{ 
    int x;
    int y; 
    int z; 

    bool operator==(const vec3 input)
    {
        return x == input.x && y == input.y && z == input.z;
    }
};

vector<pair<int, int>> dir { {0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
int n, m;
vector<vector<int>> board;
vector<vec3> diceNormals { {0, 0, 1}, {0, 1, 0}, {1, 0, 0}, {0, 0, -1}, {0, -1, 0}, {-1, 0, 0} };
vector<int> dice { 0, 0, 0, 0, 0, 0 };

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

void rotateDiceNormals(int d)
{
    for (int i=0; i<6; ++i)
    {
        vec3 nNormal = diceNormals[i];
        switch (d)
        {
            case 1:
            nNormal.y = diceNormals[i].z;
            nNormal.z = -diceNormals[i].y;
            break;

            case 2:
            nNormal.y = -diceNormals[i].z;
            nNormal.z = diceNormals[i].y;
            break;

            case 3:
            nNormal.x = -diceNormals[i].z;
            nNormal.z = diceNormals[i].x;
            break;

            case 4:
            nNormal.x = diceNormals[i].z;
            nNormal.z = -diceNormals[i].x;
            break;
        }
        diceNormals[i] = nNormal;
    }
}

int findDiceSurf(vec3 normal)
{
    int ret = -1;
    for (int i=0; i<6; ++i)
    {
        if (normal == diceNormals[i])
        {
            ret = i;
            break;
        }
    }

    return ret;
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int x, y, k;
    cin >> n >> m >> x >> y >> k;
    board.resize(n, vector<int>(m));
    for (int i=0; i<n; ++i)   
    {
        for (int j=0; j<m; ++j)
        {
            cin >> board[i][j];
        }
    }

    for (int i=0; i<k; ++i)
    {
        int d;
        cin >> d;
        int nx = dir[d].first + x;
        int ny = dir[d].second + y;

        if (OOB(nx, ny))
            continue;

        rotateDiceNormals(d);
        if (board[nx][ny] == 0)
        {
            int bottom = findDiceSurf({0, 0, -1});
            board[nx][ny] = dice[bottom];
        }
        else
        {
            int bottom = findDiceSurf({0, 0, -1});
            dice[bottom] = board[nx][ny];        

            board[nx][ny] = 0;
        }

        int top = findDiceSurf({0, 0, 1});
        cout << dice[top] << "\n";

        x = nx;
        y = ny;
    }
    return 0;
}