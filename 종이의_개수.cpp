#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Vec3
{
    int x;
    int y;
    int z;

    Vec3 operator+(const Vec3& other) const
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    Vec3& operator+=(const Vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }
};

Vec3 CreateVec3(int id)
{
    switch (id)
    {
    case -1:
        return {1, 0, 0};
        break;
        
    case 0:
        return {0, 1, 0};
        break;
        
    case 1:
        return {0, 0, 1};
        break;
    default:
        return {0, 0, 0};
    }
}

Vec3 Count(
        int sx, int sy, int n, 
        const vector<vector<int>>& paper)
{
    // cout << "[LOG] sx: " << sx << ", sy: " << sy << ", n: " << n << endl; 
    int base = paper[sx][sy];
    bool isSame = true;

    for (int i = sx; i < sx + n; ++i)
    {
        for (int j = sy; j < sy + n; ++j)
        {
            if (paper[i][j] != base)
            {
                isSame = false;
            }
        }
    }

    if (!isSame)
    {
        Vec3 vec3{};
        int n3 = n / 3;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                vec3 += Count(sx + i * n3, sy + j * n3, n3, paper);
            }
        }

        return vec3;
    }
    else
    {
        return CreateVec3( paper[sx][sy] );
    }

}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<vector<int>> paper(n, vector<int>( n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> paper[i][j];
        }
    }

    Vec3 result = Count(0, 0, n, paper);
    cout << result.x << endl;
    cout << result.y << endl;
    cout << result.z << endl;

    return 0;
}

