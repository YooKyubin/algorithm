#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<int> cookie) {
    int answer = 0;
    const int n = (int)cookie.size();
    
    // [left, right)
    vector<int> cookieAcc(n+1, 0);
    for (int i = 1; i < n+1; ++i)
    {
        cookieAcc[i] = cookieAcc[i-1] + cookie[i-1];
    }

    for (int i = 0; i < n; ++i)
    {
        int left = 0;
        int right = n;
        int leftCookie = cookieAcc[i] - cookieAcc[left];  // 0 ~ i-1
        int rightCookie = cookieAcc[right] - cookieAcc[i]; // i ~ n-1

        while (left < i && i <= right)
        {
            if (leftCookie < rightCookie)
            {
                --right;
                rightCookie = cookieAcc[right] - cookieAcc[i];
            }
            else if (leftCookie == rightCookie)
            {
                answer = max(answer, leftCookie);
                break;
            }
            else
            {
                ++left;
                leftCookie = cookieAcc[i] - cookieAcc[left];
            }
        }
    }

    return answer;
}

int main()
{
    freopen("output.txt", "w", stdout);

    vector<int> cookie{ 1, 1, 2, 3 };
    cout << solution(cookie) << endl;
    return 0;
}