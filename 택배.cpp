#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Delivery
{
    int from;
    int to;
    int box;

    bool operator<(Delivery input)
    {
        if (this->to == input.to)
            return this->from < input.from;
        else
            return this->to < input.to;
    }
};

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n, m, capacity;

    cin >> n >> capacity;
    cin >> m;

    vector<int> sizes(n+1, capacity);
    vector<Delivery> delivery(m);

    for (int i=0; i<m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        delivery[i] = {a, b, c};
    }
    sort(delivery.begin(), delivery.end());

    int answer = 0;
    for (auto del : delivery)
    {
        int minSize = INT32_MAX; // 각 마을 중 가장 용량이 적게남은 
        for (int i=del.from; i<del.to; ++i)
            minSize = min(minSize, sizes[i]);

        int curBox = min(minSize, del.box);
        for (int i=del.from; i<del.to; ++i)
            sizes[i] -= curBox;
            
        answer += curBox;
    }

    cout << answer << endl;
}