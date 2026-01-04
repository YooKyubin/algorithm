#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());

    int left = 0;
    int right = 0;

    int minInterval = 0;
    // init minInterval
    // right를 움직여 left와의 간격을 벌림
    while (arr[right] - arr[left] < m)
    {
        ++right;
    }
    minInterval = arr[right] - arr[left];

    // two pointer main loop
    // left가 right를 넘지 않도록, right는 n까지 조사
    while (left <= right && right < n)
    {
        int interval = arr[right] - arr[left];
        
        if (interval < m)
        {
            ++right;
        }
        else
        {
            minInterval = min(minInterval, interval);
            ++left;
        }
    }
    // 문제의 해가 항상 존재하기 때문에( 항상 차이가 M이상인 두 수를 고를 수 있다. )
    // left > right 인 상황에서 다시 right -> n 까지 조사할 필요는 없다. 
    // ( left > right )인 상황이라면 이미 그 상태로 끝이다.( 아마 M == 0 ) 

    // 마무리 
    // left를 n 까지 움직이며 모든 경우의 수 조사
    while (left < n)
    {
        int interval = arr[n-1] - arr[left];
        if (interval >= m)
        {
            minInterval = min(minInterval, interval); 
        }
        ++left;
    }

    cout << minInterval << endl;

    return 0;
}