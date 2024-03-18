#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; ++i)
    {
        cin >> arr[i];
    }

    vector<bool> visited(100001, false);

    int64_t answer = 0;
    int right = 0;
    int left = 0;

    while (left < n)
    {
        while ( right < n && !visited[ arr[right] ] )
        {
            visited[ arr[right] ] = true;
            ++right;
        }

        answer += right - left;
        visited[ arr[left] ] = false;
        ++left;
    }

    cout << answer << endl;

    return 0;
}