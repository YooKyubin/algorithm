#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i=0; i<n; ++i)
        cin >> arr[i];

    int x;
    cin >> x;

    sort(arr.begin(), arr.end());

    int cnt = 0;
    int left = 0;
    int right = n-1;
    while (left < right)
    {
        int compare = arr[left] + arr[right];
        if (compare == x)
        {
            ++cnt;
            ++left; // 서로 다른 양수
        }
        else if (compare > x)
            --right;
        else
            ++left;
        
    }
    cout << cnt << endl;
    return 0;
}