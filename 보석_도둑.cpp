#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Jewel
{
    int weight;
    int value;
};

bool operator<(const Jewel& a, const Jewel& b)
{
    return a.weight < b.weight;
}

int n, k;
vector<Jewel> jewels;
vector<int> bags;

int main()
{
    freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    jewels.resize(n);
    bags.resize(k);
    for(int i=0; i<n; ++i)
    {
        int m, v;
        cin >> m >> v;
        jewels[i] = {m, v};
    }

    for (int i=0; i<k; ++i)
    {
        int c;
        cin >> c;
        bags[i] = c;
    }
    sort(jewels.begin(), jewels.end(), less<Jewel>());
    sort(bags.begin(), bags.end());

    priority_queue<int> valueMinHeap;

    int idx = 0;
    int64_t answer = 0;
    for (int i=0; i<k; ++i)
    {
        while (idx < n)
        {
            if (jewels[idx].weight > bags[i])
                break;

            valueMinHeap.push(jewels[idx].value);
            ++idx;
        }

        if (!valueMinHeap.empty())
        {
            answer += valueMinHeap.top();
            valueMinHeap.pop();
        }
    }
    cout << answer << endl;

    return 0;
}