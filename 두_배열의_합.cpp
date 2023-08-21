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

    // 투포인터 탐색
    int left = 0;
    int right = sumB.size()-1;
    int64_t cnt = 0;
    while (0 <= right && left < sumA.size())
    {
        if (sumA[left] + sumB[right] > t)
            --right;
        
        else if (sumA[left] + sumB[right] < t)
            ++left;
        
        else
        {
            int64_t tempA = sumA[left];
            int64_t tempB = sumB[right];
            int64_t cntA = 0;
            int64_t cntB = 0;

            while (tempA == sumA[left] && left < sumA.size())
            {
                ++left;
                ++cntA; 
            }

            while (tempB == sumB[right] && 0 <= right)
            {
                --right;
                ++cntB;
            }
            cnt += cntA * cntB;
        }
    }

    cout << cnt << endl;
    return 0;
}