#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct Bucket
{
    int a;
    int b;
    int c;
};

void DFS(const Bucket& maxSize, Bucket curr, vector<vector<bool>>& visited)
{
    if (visited[curr.a][curr.b])
    {
        return;
    }
    visited[curr.a][curr.b] = true;

    static auto Pour = [](const int dstCapacity, int& src, int& dst) -> void
    {
        int total = src + dst;
        dst = min(total, dstCapacity);
        src = total - dst;
    };

    // a -> b
    {
        Bucket temp = curr;
        Pour(maxSize.b, temp.a, temp.b);
        DFS(maxSize, temp, visited);
    }
    // a -> c
    {
        Bucket temp = curr;
        Pour(maxSize.c, temp.a, temp.c);
        DFS(maxSize, temp, visited);
    }
    // b -> a
    {
        Bucket temp = curr;
        Pour(maxSize.a, temp.b, temp.a);
        DFS(maxSize, temp, visited);
    }
    // b -> c
    {
        Bucket temp = curr;
        Pour(maxSize.c, temp.b, temp.c);
        DFS(maxSize, temp, visited);
    }
    // c -> a
    {
        Bucket temp = curr;
        Pour(maxSize.a, temp.c, temp.a);
        DFS(maxSize, temp, visited);
    }
    // c -> b
    {
        Bucket temp = curr;
        Pour(maxSize.b, temp.c, temp.b);
        DFS(maxSize, temp, visited);
    }
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    Bucket maxCapacity;
    cin >> maxCapacity.a >> maxCapacity.b >> maxCapacity.c;

    constexpr int MAX = 201;
    vector<vector<bool>> visited(MAX, vector<bool>(MAX, false));
    DFS(maxCapacity, Bucket{ 0, 0, maxCapacity.c }, visited);

    vector<bool> validC (MAX, false);
    for (int i = MAX - 1; i >= 0; --i)
    {
        if (visited[0][i])
        {
            cout << maxCapacity.c - i << " ";
        }
    }

    return 0;
}