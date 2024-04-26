#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int a;
    int b;
    int wieght;
};

bool operator<(const Edge& a, const Edge& b)
{
    return a.wieght < b.wieght;
}

int n, m;
vector<int> head;

void Init()
{
    for (int i=0; i<=n; ++i)
    {
        head[i] = i;
    }
}

int Find(int x)
{
    if ( head[x] == x)
        return x;

    return head[x] = Find(head[x]);
}

void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if (x == y)
        return;

    head[x] = y;
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin >> n >> m;
    head.resize(n+1);
    vector<Edge> edges;
    edges.reserve(m);

    Init();

    for (int i=0; i<m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;

        edges.push_back({a, b, c});
    }

    sort(edges.begin(), edges.end());

    int answer = 0;
    int preIdx = 0;
    for (int i=0; i<m; ++i)
    {
        int a = edges[i].a;
        int b = edges[i].b;
        if (Find(a) == Find(b))
            continue;

        Union(a, b);
        answer += edges[i].wieght;
        preIdx = i;
    }

    answer -= edges[preIdx].wieght;
    
    cout << answer << endl;
    return 0;
}

// 유니온 파인드 - 크루스칼 [x]
// 우선순위 큐 - 프림 [] 