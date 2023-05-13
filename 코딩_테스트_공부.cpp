#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int limitMax(int maxVal, int curVal){
    return maxVal < curVal ? maxVal : curVal;
}

int solution(int alp, int cop, vector<vector<int>> problems) {
    int answer = 0;
    vector<vector<int>> dp(151, vector<int>(151, 151 * 2 * 100 + 1));
    problems.push_back( {0, 0, 1, 0, 1} );
    problems.push_back( {0, 0, 0, 1, 1} );


    int max_alp_req = 0;
    int max_cop_req = 0;
    for (int i=0; i < problems.size(); i++){
        auto problem = problems[i];
        max_alp_req =  max( max_alp_req, problem[0] );
        max_cop_req = max( max_cop_req, problem[1] );
    }

    alp = limitMax(max_alp_req, alp);
    cop = limitMax(max_cop_req, cop);
    // if ( alp >= max_alp_req && cop >= max_cop_req){
    //     return answer;
    // }
    dp[alp][cop] = 0;

    for (int i=alp; i <= max_alp_req; i++){
        for (int j=cop; j <= max_cop_req; j++){

            for (auto problem: problems){
                int alp_req = problem[0];
                int cop_req = problem[1];
                if ( alp_req > i || cop_req > j ) continue;

                int alp_rwd = problem[2];
                int cop_rwd = problem[3];
                int cost = problem[4];
                
                int n_alp_rwd = limitMax(max_alp_req, i + alp_rwd);
                int n_cop_rwd = limitMax(max_cop_req, j + cop_rwd);
                dp[n_alp_rwd][n_cop_rwd] = min(dp[n_alp_rwd][n_cop_rwd], dp[i][j]+cost);

            }
        }
    }
    cout << "\t"; for (int i=alp; i <= max_alp_req; i++) cout << i << "\t";
    cout << endl << endl;
    for (int i=alp; i <= max_alp_req; i++){
        cout << i << "\t";
        for (int j=cop; j <= max_cop_req; j++){
            cout << dp[i][j] << "\t";
        }cout << endl;
    }
    
    answer = dp[max_alp_req][max_cop_req];
    return answer;
}

int main() {
    // int alp = 10;
    // int cop = 10;
    // vector<vector<int>> problems { {10,15,2,1,2}, {20,20,3,3,4} };
    int alp = 9;
    int cop = 12;
    vector<vector<int>> problems {{0,0,2,1,2},{4,5,3,1,2},{4,11,4,0,2},{10,4,0,4,2}};
    cout << solution(alp, cop, problems) << endl;
    return 0;
}