#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> prices(n);
    vector<int> times(n);
    for (int i=0; i<n; ++i)
    {
        cin >> times[i] >> prices[i];
    }

    /*
        0 ~ n 까지 순회하는게 더 직관적으로 이해가 잘 되긴했지만
        코드가 좀 더 깔끔해지기 위해서는 역순으로 순회하는게 더 좋다.
    */
    vector<int> maxPriceByDay(n + 1, 0);
    for (int i=n-1; i >= 0; --i)
    {
        int time = times[i];
        int price = prices[i];

        if (time + i <= n)
        {
            maxPriceByDay[i] = max(maxPriceByDay[i + 1], price + maxPriceByDay[i + time]);
        }
        else
        {
            maxPriceByDay[i] = maxPriceByDay[i+1];
        }
    }

    cout << maxPriceByDay[0] << endl;

    return 0;
}