#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b){ return a > b ? a : b; }
int min(int a, int b){ return a < b ? a : b; }

vector<vector<bool>> spelling(26, vector<bool>(26, false));

bool spellCheck(char submit, char answer){
    int A = submit - 'a';
    int B = answer - 'a';
    return spelling[A][B];
}

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n, m;
    string submit;
    string answer;
    cin >> n >> m;
    cin >> submit;
    cin >> answer;
    for (char i = 'a'; i <= 'z'; i++){
        int idx = i - 'a';
        spelling[idx][idx] = true;
    }
    spelling['i'-'a']['j'-'a'] = true;
    spelling['i'-'a']['l'-'a'] = true;
    spelling['v'-'a']['w'-'a'] = true;
    
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for (int i=0; i < n+1; i++){
        dp[i][0] = i;
    }
    for (int i=0; i < m+1; i++){
        dp[0][i] = i;
    }

    for (int i=1; i<n+1; i++){
        for (int j=1; j<m+1; j++){
            if (spellCheck(submit[i-1], answer[j-1])){
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                int temp = min(dp[i-1][j], dp[i][j-1]);
                dp[i][j] = min(dp[i-1][j-1], temp) +1;
            }
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}