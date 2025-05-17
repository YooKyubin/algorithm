#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NUM 1'000'000'000

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int numCities;
    cin >> numCities;

    vector<int> distances(numCities - 1);
    for (int i=0; i<numCities - 1; ++i)
    {
        cin >> distances[i];
    }

    vector<int> oilPrices(numCities);
    for (int i=0; i<numCities; ++i)
    {
        cin >> oilPrices[i];

        if (i > 0)
        {
            oilPrices[i] = min(oilPrices[i], oilPrices[i-1]);
        }
    }

    uint64_t minCost = 0;
    for (int i=0; i<numCities-1; ++i)
    {
        minCost += (uint64_t)oilPrices[i] * (uint64_t)distances[i];
    }
    cout << minCost << "\n";

    return 0;
}