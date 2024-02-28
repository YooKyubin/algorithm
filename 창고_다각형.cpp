#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pillars(1001, 0);
vector<int> leftOrder(1001, 0);
vector<int> rightOrder(1001, 0);

int main()
{   
    int n;
    cin >> n;
    for(int i=0; i<n; ++i)
    {
        int l, h;
        cin >> l >> h;
        pillars[l] = h;
    }

    int leftMax = 0;
    for (int i=0; i<1001; ++i)
    {
        leftMax = max(pillars[i], leftMax);
        leftOrder[i] = leftMax;
    }

    int rightMax = 0;
    for (int i=1000; i >= 0; --i)
    {
        rightMax = max(pillars[i], rightMax);
        rightOrder[i] = rightMax;
    }

    int cnt = 0;
    for(int i=0; i<1001; ++i)
    {
        int minVal = min(rightOrder[i], leftOrder[i]);
        cnt += minVal;
    }

    cout << cnt << endl;
    return 0;
}