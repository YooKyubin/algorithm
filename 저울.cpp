#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i]; 
    }
    sort(arr.begin(), arr.end());

    vector<int> acc;
    acc.reserve(n+1);
    acc.push_back(0);
    for (int i = 0; i < n; ++i)
    {
        if (acc[i] + 1 < arr[i])
        {
            break;
        }
        acc.push_back(acc[i] + arr[i]);
    }
    cout << acc.back() + 1 << endl;


    return 0;
}
