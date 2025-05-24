#include <iostream>
#include <vector>

using namespace std;

struct RgbCost
{
    RgbCost() = default;
    RgbCost(int _r, int _g, int _b)
        : r(_r)
        , g(_g)
        , b(_b)
    {}
    int r{0};
    int g{0};
    int b{0};

    int Min()
    {
        return min(r, min(g, b));
    }
};

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<RgbCost> costs;
    costs.reserve(n);
    for (int i=0; i < n; ++i)
    {
        RgbCost cost;
        cin >> cost.r >> cost.g >> cost.b;
        costs.push_back(cost);
    }

    vector<RgbCost> dp(n);
    dp[0] = costs[0];
    for (int i = 1; i < n; ++i)
    {
        RgbCost currentCostByRGB;
        currentCostByRGB.r = costs[i].r + min(dp[i-1].g, dp[i-1].b);
        currentCostByRGB.g = costs[i].g + min(dp[i-1].b, dp[i-1].r);
        currentCostByRGB.b = costs[i].b + min(dp[i-1].r, dp[i-1].g);

        dp[i] = currentCostByRGB;
    }

    cout << dp.back().Min() << endl;
    
    return 0;
}