#include <iostream>
#include <cmath>

using namespace std;

int main() 
{
    int N;
    cin >> N;
    
    int dp[20001];
    dp[0] = dp[1] = 1;
    dp[2] = 2;
    dp[3] = 6;
    dp[4] = 4;

    for (int i = 5; i <= N; i++) {
        if (i % 5 == 0) 
        {
            int q = i / 5;
            dp[i] = ((int)pow(2, q % 4) * dp[q]) % 10; // 공식 사용.
        } 
        else 
        {
            int before = (i / 5) * 5; // i보다 작은 최대 5의 배수를 구함.
            int total = 1;
            for (int j = before+1; j <= i; j++) 
            {
                total *= (j % 10);
            }
            total *= dp[before];
            dp[i] = total % 10;
        }
    }

    cout << dp[N] << endl;
    return 0;
}