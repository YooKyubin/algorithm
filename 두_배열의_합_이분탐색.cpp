#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int t, n ,m;
    vector<int64_t> sumA;
    vector<int64_t> sumB;
    vector<int> a {0};
    vector<int> b {0};

    // 입력
    cin >> t;
    cin >> n;
    for (int i=0; i<n; ++i)
    {
        int temp;
        cin >> temp;
        a.push_back(temp + a[i]);
    }
    cin >> m;
    for (int i=0; i<m; ++i)
    {
        int temp;
        cin >> temp;
        b.push_back(temp + b[i]);
    }

    // 누적합 계산
    for (int i=0; i<n+1; ++i)
        for (int j=0; j<i; ++j)
            sumA.push_back(a[i] - a[j]);

    for (int i=0; i<m+1; ++i)
        for (int j=0; j<i; ++j)
            sumB.push_back(b[i] - b[j]);
    
    // 정렬
    sort(sumA.begin(), sumA.end());
    sort(sumB.begin(), sumB.end());

    // 이분탐색
    int64_t cnt = 0;
    for (auto A : sumA)
    {
        int lowerBound;
        {
            int lo = 0;
            int hi = sumB.size()-1;
            while (lo <= hi)
            {
                int mid = (lo + hi) / 2;

                if (t - A <= sumB[mid])
                    hi = mid - 1;

                else
                    lo = mid + 1;
            }
            lowerBound = lo;
        }

        int upperBound;
        {
            int lo = 0;
            int hi = sumB.size()-1;
            while (lo <= hi)
            {
                int mid = (lo + hi) / 2;

                if (t - A < sumB[mid])
                    hi = mid - 1;

                else
                    lo = mid + 1;
            }
            upperBound = lo;
        }

        cnt += upperBound - lowerBound;
    }

    cout << cnt << endl;
    return 0;
}