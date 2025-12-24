// 크루스칼
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Street
{
    int src;
    int dst;
    int weight;
};

int Find(int x, vector<int>& heads)
{
    if (heads[x] == x)
    {
        return x;
    }

    return heads[x] = Find(heads[x], heads);
}

void Union(int x, int y, vector<int>& heads)
{
    x = Find(x, heads);
    y = Find(y, heads);

    heads[x] = heads[y];
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    while (true)
    {
        int numHouses;
        int numStreets;
        cin >> numHouses >> numStreets;

        if (numHouses == 0 && numStreets == 0)
        {
            break;
        }

        int totalCost = 0;
        vector<Street> streets;
        streets.reserve(numStreets);
        for (int i = 0; i < numStreets; ++i)
        {
            int src, dst, weight;
            cin >> src >> dst >> weight;
            streets.push_back({ src, dst, weight });
            totalCost += weight;
        }
        sort(streets.begin(), streets.end(), [](auto& src, auto& dst) -> bool 
        {
            return src.weight < dst.weight;
        });

        vector<int> heads(numHouses);
        for (int i = 0; i < numHouses; ++i)
        {
            heads[i] = i;
        }

        int numMstEdge = 0;
        int cost = 0;
        for (const Street& street : streets)
        {
            if (numMstEdge == numHouses -1)
            {
                break;
            }

            if (Find(street.src, heads) == Find(street.dst, heads))
            {
                continue;
            }

            Union(street.src, street.dst, heads);
            cost += street.weight;
            ++numMstEdge;
        }

        cout << totalCost - cost << "\n";
    }

    return 0;
}

---

// 프림
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Street
{
    int to;
    int weight;

    bool operator>(const Street& other) const
    {
        return weight > other.weight;
    }
};

int main()
{
    // freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    while (true)
    {
        int numHouses;
        int numStreets;
        cin >> numHouses >> numStreets;

        if (numHouses == 0 && numStreets == 0)
        {
            break;
        }

        int totalCost = 0;
        vector<vector<Street>> graph(numHouses);
        for (int i = 0; i < numStreets; ++i)
        {
            int src, dst, weight;
            cin >> src >> dst >> weight;

            graph[src].push_back({ dst, weight });
            graph[dst].push_back({ src, weight });
            totalCost += weight;
        }

        priority_queue<Street, vector<Street>, greater<Street>> pq;
        vector<bool> visited(numHouses, false);
        pq.push({ 0, 0 });

        int mstCost = 0;
        int numMstNode = 0;

        while (!pq.empty())
        {
            int curr = pq.top().to;
            int currWeight = pq.top().weight;
            pq.pop();
            
            if (visited[curr])
            {
                continue;
            }
            
            visited[curr] = true;
            ++numMstNode;
            mstCost += currWeight;

            if (numMstNode == numHouses)
            {
                break;
            }

            for (const Street& nextNode : graph[curr])
            {
                int next = nextNode.to;

                // 없어도 되지만, 이걸 하면 메모리가 조금 아껴짐( 우선 순위 큐에 굳이 필요없는 노드를 삽입하지 않음 )
                if (visited[next])
                {
                    continue;
                }
                pq.push(nextNode);
            }
        }

        cout << totalCost - mstCost << "\n";
    }

    return 0;
}