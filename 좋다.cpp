#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // freopen("../../input.txt", "r", stdin);

    int n;
    int ans = 0;
    cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; ++i)
    {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    for (int i=0; i<n; ++i)
    {
        int left = 0;
        int right = n-1;

        while (left < right)
        {
            if (left == i || arr[i] > arr[left] + arr[right])
            {
                ++left;
            }
            else if (right == i || arr[i] < arr[left] + arr[right])
            {
                --right;
            }
            else // ==
            { 
                ++ans;
                break;
            }
        }
    }

    cout << ans << endl;
    return 0;
}