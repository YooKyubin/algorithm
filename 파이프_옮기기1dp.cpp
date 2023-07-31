#include <iostream>
#include <vector>

using namespace std;


int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<vector<bool>> walls(n, vector<bool>(n, false));
	vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(3, 0))); // 가로, 세로, 대각선

	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			bool wall;
			cin >> wall;
			walls[i][j] = wall;
		}
	}


	dp[0][1][0] = 1;
	for (int i=2; i<n; i++){
		if(!walls[0][i])
			dp[0][i][0] = dp[0][i-1][0];
	}
	for (int i=1; i<n; i++){
		for (int j=2; j<n; j++){
			if (!walls[i][j]){
				dp[i][j][0] = dp[i][j-1][0] + dp[i][j-1][2];
				dp[i][j][1] = dp[i-1][j][1] + dp[i-1][j][2];
			}
			if (!(walls[i][j] || walls[i][j-1] || walls[i-1][j])){
				dp[i][j][2] = dp[i-1][j-1][0] + dp[i-1][j-1][1] + dp[i-1][j-1][2];
			}
			// 벽이 있어서 파이프가 지나가지 못하는 구간은 dp 테이블을 0으로 초기화 했기 때문에 굳이 0으로 다시 대입할 필요없다.
		}
	}

	int answer = 0;
	for (int i : dp[n-1][n-1]) answer += i;
	cout << answer << endl;
	return 0;
}

// 현재 칸을 끝으로 하는 가로, 세로, 대각선 파이프의 개수