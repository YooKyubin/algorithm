#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int abs(int a) { return a < 0 ? -a : a; }

int main()
{
    // freopen("../../input.txt", "r", stdin);
    int n;
    cin >> n;
    vector<int64_t> arr(n);
    for (int i=0; i<n; ++i)
    {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());
    int64_t interval = 3'000'000'001;
    vector<int> answer(3, 0);

    for (int i=0; i<n; ++i)
    {
        int left = 0;
        int right = n-1;

        while (left < right)
        {
            if ( i == left || i == right)
                break;

            int64_t sum = arr[i] + arr[left] + arr[right];
            if (abs(sum) < interval)
            {
                answer[0] = arr[i];
                answer[1] = arr[left];
                answer[2] = arr[right];

                interval = abs(sum);
            }

            if (sum < 0)
                ++left;
            else
                --right;
        }
    }

    sort(answer.begin(), answer.end());

    cout << answer[0] << " " << answer[1] << " " << answer[2] << endl;
    return 0;
}