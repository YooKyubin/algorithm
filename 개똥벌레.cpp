#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, h;
    cin >> n >> h;

    vector<int> ceil(h + 1);
    vector<int> floor(h + 1);
    for (int i = 0; i < n; ++i)
    {
        int length;
        cin >> length;
        if ( i  % 2 == 0)
        {
            ++floor[length];
        }
        else
        {
            ++ceil[length];
        }
    }

    vector<int> numObstacles(h, 0);
    numObstacles[0] = n / 2 - floor[0] + ceil[h-0];
    for (int i = 1; i < h; ++i)
    {
        numObstacles[i] = numObstacles[i-1] - floor[i] + ceil[h-i];
    }

    int minObstacles = n;
    int countMin = 0;
    for (int i : numObstacles)
    {
        if (minObstacles > i)
        {
            countMin = 1;
            minObstacles = i;
        }
        else if (minObstacles == i)
        {
            ++countMin;
        }
    }
    cout << minObstacles << " " << countMin << endl;

    return 0;
}