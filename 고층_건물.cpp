#include <iostream>
#include <vector>

using namespace std;

int max (int a, int b) { return a > b ? a : b; }

int main()
{
    freopen("../../input.txt", "r", stdin);
    int n;
    cin >> n;
    vector<int> buildings(n);
    vector<int> visibleCnt(n, 0);
    for (int i=0; i<n; ++i)
    {
        cin >> buildings[i];
    }

    for (int i=0; i<n; ++i)
    {
        int x = i;
        int y = buildings[i];

        int64_t maxGradientDx = 0;
        int64_t maxGradientDy = -INT32_MAX;
        for (int j=i+1; j<n; ++j)
        {
            int nx = j;
            int ny = buildings[j];

            int64_t dx = nx - x;
            int64_t dy = ny - y;

            if (maxGradientDy * dx < dy * maxGradientDx) // 보임
            {
                ++visibleCnt[i];
                // printf("%d can see %d\n", i, j);
                // printf("maxGradientDy : %d, dx : %d, dy : %d, maxGradientDx : %d\n\n", maxGradientDy, dx, dy, maxGradientDx);
                maxGradientDx = dx;
                maxGradientDy = dy;
            }

        }
    }

    for (int i = n-1; i >= 0; --i)
    {
        int x = i;
        int y = buildings[i];

        int64_t maxGradientDx = 1;
        int64_t maxGradientDy = -INT32_MAX;
        for (int j=i-1; j>=0; --j)
        {
            int nx = j;
            int ny = buildings[j];

            int64_t dx = nx - x;
            int64_t dy = ny - y;
            dx = -dx;

            if (maxGradientDy * dx < dy * maxGradientDx) // 보임
            {
                ++visibleCnt[i];
                // printf("%d can see %d\n", i, j);
                // printf("maxGradientDy : %d, dx : %d, dy : %d, maxGradientDx : %d\n\n", maxGradientDy, dx, dy, maxGradientDx);

                maxGradientDx = dx;
                maxGradientDy = dy;
            }
        }
    }

    
    int answer = 0;
    for (int i=0; i<n; ++i)
    {
        // cout << " i : " << i << ", cnt : " << visibleCnt[i] << endl;
        answer = max(answer, visibleCnt[i]);
    }

    cout << answer << endl;    

    return 0;
}