#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n; 
    cin >> n;
    vector<int> houses(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> houses[i];
    }
    sort(houses.begin(), houses.end());

    int numLeft = 0;
    int numRight = n;

    int dist = 0;
    for (int i = 0; i <n; ++i)
    {
        dist += houses[i] - houses[0];
    }

    int answer = houses[0];
    for (int i = 1; i < n; ++i)
    {
        int preInterval = houses[i] - houses[i-1];
        int newDist = dist - (preInterval * (n-i)) + (preInterval * i);
        if (dist > newDist)
        {
            answer = houses[i];
            dist = newDist;
        }
    }
    cout << answer << endl;

    return 0;
}