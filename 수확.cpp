#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b){
    if (a > b) return a;
    else return b;
}

// 1000 * 2001 * 1000 < 2,147,483,648(int 최대값)

int main () {
    int n;
    cin >> n;
    vector<int> rices(n+2, 0); 
    for (int i=1; i<n+1; i++){ // 1 ~ n+1
        cin >> rices[i]; // 0, input... , 0
    }
    vector<vector<int>> dp(n+2, vector<int>(n+2, 0)); // dp[left][right] => rices에서 left, right까지 수확을 완료한 상태
    dp[0][n+1] = 0; // 초기 값
    for (int i=1; i < n+1; i++){
        int cnt = i;
        dp[i][n+1] = dp[i-1][n+1] + rices[i] * cnt;
    }
    for (int j=n; j > 0; j--){
        int cnt = n+1 - j;
        dp[0][j] = dp[0][j+1] + rices[j] * cnt;
    }

    for (int i=1; i<n+2; i++){
        for (int j=n; j>i; j--){
            int cnt = (i - 0) + (n+1 - j);
            dp[i][j] = max( dp[i-1][j] + rices[i] * cnt, dp[i][j+1] + rices[j] * cnt );
        }
    }
    
    int answer=0;
    for (int i=0; i < n+1; i++){
        answer = max(answer, dp[i][i+1]);
    }

    cout << answer << endl;
    // for (auto i: dp){
    //     for (auto j: i){
    //         cout << j << "\t";
    //     }cout << endl;
    // }

    return 0;
}

/*
dp 로 풀어야 하는 이유:
- 1 2 3 4 5 6 7 8 1 1 1 1 ... 1 1 1 9 1 처럼 주어졌을 때 나의 풀이로는 당장의 바로 뒤 값만을 보고 큰 그림을 못 본다.
- 9 * 2000 < 2 * 1900 + 3 * 1901 + 4 * 1902 + 5 * 1903 + ... + 8 * 1907
*/