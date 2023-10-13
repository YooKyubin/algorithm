#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Tree
{
    int x;
    int y;
    int age;
};

int n, m, k;
vector<vector<vector<int>>> trees;
vector<vector<int>> nourishments;
vector<vector<int>> addNourishments;
vector<pair<int, int>> dir { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= n;
}

vector<Tree> Spring()
{
    vector<Tree> dead;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            for (auto& t : trees[i][j])
            {
                int cnt = 0;
                if (nourishments[i][j] >= t)
                {
                    nourishments[i][j] -= t;
                    ++t; // 나무 나이 먹는다
                }
                else
                {
                    ++cnt;
                    dead.push_back({i, j, t});
                }
                
                while(cnt--)
                    trees[i][j].pop_back();
            }
        }
    }

    return dead;
}

void Summer(vector<Tree>& dead)
{
    for (auto t : dead)
    {
        nourishments[t.x][t.y] += t.age / 2;
    }
}

void Autumn()
{
    vector<pair<int, int>> reproduction;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            for (auto age : trees[i][j])
            {
                if (age % 5 == 0)
                    reproduction.push_back({i, j});
            }
        }
    }
    for (auto t : reproduction)
    {

        for (auto d : dir)
        {
            int x = t.first + d.first;
            int y = t.second + d.second;
            
            if (OOB(x, y))
                continue;

            trees[x][y].push_back(1);
        }
    }
}

void Winter()
{
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            nourishments[i][j] += addNourishments[i][j];
        }
    }
}

void sortTree()
{
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            sort(trees[i][j].begin(), trees[i][j].end());
        }
    }
}

int main()
{
    cin >> n >> m >> k;
    trees.resize(n, vector<vector<int>>(n));
    nourishments.resize(n, vector<int>(n, 5));
    addNourishments.resize(n, vector<int>(n));

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
            cin >> addNourishments[i][j];

    }
    for (int i=0; i<m; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        trees[x-1][y-1].push_back(z);
    }

    while (k--)
    {
        sortTree();

        vector<Tree> dead = Spring();
        Summer(dead);
        Autumn();
        Winter();
    }

    int cntTrees = 0;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cntTrees += trees[i][j].size();
        }
    }

    cout << cntTrees << endl;
    return 0;
}

// sort 할 필요가 없도록 만들면 더 빨라질 것 같다.

/*
봄
    양분 먹고 증가, 혹은 죽음

여름 
    죽은 나무 양분으로 변환

가을
    번식

겨울 
    A[][] 만큼의 양분 추가
*/