#include <iostream>
#include <string>
#include <vector>

using namespace std;

string line1;
string line2;
vector table(1001, vector<int>(1001, 0));

int main(){

    getline(cin, line1);
    getline(cin, line2);

    // table과 문자열의 인덱스를 맞추기 위해 억지로 0 번 인덱스는 비우기
    line1.insert(0, " ");
    line2.insert(0, " ");
    
    for (int i=0; i < line1.size(); i++){
        for(int j=0; j<line2.size(); j++){
            // 0을 참고해야 하기 때문에 0라인은 비워둡니다.
            if ( i == 0 || j == 0 ) continue;

            if ( line1[i] == line2[j] ) {
                table[i][j]  = table[i-1][j-1] + 1;
            }
            else{
                table[i][j] = max(table[i-1][j], table[i][j-1]);
            }
        }
    }
    cout << table[line1.size()-1][line2.size()-1] << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string src, dst;
    cin >> src;
    cin >> dst;

    // dp[i][j] = src: i, dst: j까지 있다고 가정했을 때 확인
    vector<vector<int>> dp(src.size(), vector<int>(dst.size(), 0));

    // dp init
    dp[0][0] = src[0] == dst[0] ? 1 : 0;
    for (size_t i = 1; i < dst.size(); ++i)
    {
        dp[0][i] = max(dp[0][i-1], src[0] == dst[i] ? 1 : 0);
    }
    for (size_t i = 1; i < src.size(); ++i)
    {
        dp[i][0] = max(dp[i-1][0], dst[0] == src[i] ? 1 : 0);
    }

    // dp loop
    for (size_t i = 1; i < src.size(); ++i)
    {
        for (size_t j = 1; j < dst.size(); ++j)
        {
            if ( src[i] == dst[j] )
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
            {
                dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }
    cout << dp[src.size() - 1][dst.size() - 1] << endl;

    return 0;
}