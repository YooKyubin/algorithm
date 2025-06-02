#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Solution()
{
    int n;
    cin >> n;

    vector<int> stockPrices(n);
    for (int i=0; i<n; ++i)
    {
        cin >> stockPrices[i];
    }

    int maxStock = 0;
    long long sumProfit = 0;
    while (!stockPrices.empty())
    {
        int stock = stockPrices.back();
        stockPrices.pop_back();

        if (maxStock < stock)
        {
            maxStock = stock;
        }
        else
        {
            sumProfit += maxStock - stock;
        }
    }

    cout << sumProfit << endl;
}

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    int numTest = 0 ;
    cin >> numTest;

    while (numTest--)
    {
        Solution();
    }

    return 0;
}