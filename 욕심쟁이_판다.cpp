#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> forest;
vector<vector<int>> dp;

vector<pair<int, int>> dir = { {0,1}, {1,0}, {0,-1}, {-1,0} };

int max(int a, int b) { return a > b ? a : b; }
bool OOB(int x, int y) { return x < 0 || y < 0 || x >= n || y >= n; }

void dfs(int x, int y){
	int ret = 0;
	for (auto d : dir){
		int nx = x + d.first;
		int ny = y + d.second;
		if (OOB(nx, ny)) continue;
		if (forest[x][y] >= forest[nx][ny]) continue;

		if (dp[nx][ny] == 0){
			dfs(nx, ny);
		}
		ret = max(ret, dp[nx][ny]);
	}

	dp[x][y] = ret+1;

}

int main () {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	forest.assign(n, vector<int>(n, 0));
	dp.assign(n, vector<int>(n, 0));
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			cin >> forest[i][j];
		}
	}
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			dfs(i, j);
		}
	}
	
	int answer = 0;
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			answer = max(answer, dp[i][j]);
		}
	}
	cout << answer << endl;
	return 0;
}

// 아니 왜 판다가 가만히 있는거도 1로 세는 거임 판다 이동한 칸 수 아니였어? 가만히 있으면 0 아님? 판다가 대나무를 먹은 지역의 수라고 하는게 더 정확할거같은데