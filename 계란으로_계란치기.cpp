#include <iostream>
#include <vector>

using namespace std;

struct Egg{
	int durability;
	int weight;
};

int n;
int answer = 0;
vector<Egg> eggs;

int max(int a, int b) { return a > b ? a : b; }

void dfs(int cur, int cnt){
	answer = max(answer, cnt);
	if (cur == n) {
		// answer = max(answer, cnt);
		return;
	}
	if (eggs[cur].durability <= 0) { // 들고 있는 계란이 이미 깨진 경우
		dfs(cur+1, cnt);
		return;
	}
	// bool flag = true;
	for (int i=0; i<n; i++){
		if (i == cur) continue;
		if (eggs[i].durability <= 0) continue;
		// flag = false;
		int newCnt = 0;
		eggs[cur].durability -= eggs[i].weight;
		eggs[i].durability -= eggs[cur].weight;
		if (eggs[cur].durability <= 0) newCnt += 1;
		if (eggs[i].durability <= 0) newCnt += 1;
		dfs(cur+1, cnt + newCnt);
		eggs[cur].durability += eggs[i].weight;
		eggs[i].durability += eggs[cur].weight;
	}
	// if (flag) {
	// 	answer = max(answer, cnt);
	// }
}

int main() {
	cin >> n;

	for (int i=0; i<n; i++){
		int weight, durability;
		cin >> durability >> weight;
		eggs.push_back({durability, weight});
	}
	dfs(0, 0);

	cout << answer << endl;

	return 0;
}