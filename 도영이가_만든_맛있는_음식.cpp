#include <iostream>
#include <vector>

using namespace std;

long long ComputeMinInterval(int curr, int selected, const vector<pair<int, int>>& foods)
{
    int n = (int)foods.size();
    if (curr == n)
    {
        if (selected == 0)
        {
            return INT64_MAX;
        }

        long long sour = 1;
        long long bitter = 0;
        for (int i = 0; i < n; ++i)
        {
            if (selected & (1 << i))
            {
                sour *= (long long)foods[i].first;
                bitter += (long long)foods[i].second;
            }
        }

        return abs(sour - bitter);
    }

    long long included = ComputeMinInterval(curr + 1, selected | (1 << curr), foods);
    long long excluded = ComputeMinInterval(curr + 1, selected, foods);

    return min(included, excluded);
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<pair<int, int>> foods(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> foods[i].first >> foods[i].second;
    }

    cout << ComputeMinInterval(0, 0, foods) << endl;

    return 0;
}