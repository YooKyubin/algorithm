#include <iostream>
#include <vector>

using namespace std;

int n;
int answer = 0;
vector<vector<bool>> walls;

struct Pos{
	int x;
	int y;

	bool operator==(Pos input){
		return input.x == this->x && input.y == this->y;
	}
	Pos operator+(Pos input){
		Pos ret;
		ret.x = input.x + this->x;
		ret.y = input.y + this->y;
		return ret;
	}
	Pos operator-(Pos input){
		Pos ret;
		ret.x = this->x - input.x;
		ret.y = this->y - input.y;
		return ret;
	}
};

bool OOB(Pos input){
	return input.x < 0 || input.x >= n || input.y < 0 || input.y >= n;
}
bool checkWall(Pos input){
	return walls[input.x][input.y];
}

void dfs(pair<Pos, Pos> cur){
	if (cur.second.x == n-1 && cur.second.y == n-1) { //if (cur.second == Pos{n, n}) {
		answer++;
		return;
	}
	
	if (cur.first.x == cur.second.x || cur.first.y == cur.second.y){ // 가로, 세로
		Pos dir = cur.second - cur.first;
		Pos next1 = cur.second + dir;
		Pos next2 = cur.second + Pos{1,1};

		if (!(OOB(next1) || checkWall(next1))){
			dfs({ cur.second, next1 });
		}
		if ( !( OOB(next2) || checkWall(next2) || checkWall(cur.second + Pos{1,0}) || checkWall(cur.second + Pos{0,1}) ) ){
			dfs({ cur.second, next2 });
		}
	}
	else { // 대각선
		Pos next1 = cur.second + Pos{1, 0};
		Pos next2 = cur.second + Pos{0, 1};
		Pos next3 = cur.second + Pos{1, 1};

		if (!(OOB(next1) || checkWall(next1))){
			dfs({ cur.second, next1 });
		}
		if (!(OOB(next2) || checkWall(next2))){
			dfs({ cur.second, next2 });
		}
		if ( !( OOB(next3) || checkWall(next3) || checkWall(cur.second + Pos{1,0}) || checkWall(cur.second + Pos{0,1}) )){
			dfs({ cur.second, next3 });
		}
	}
}

int main() {
	cin.tie(0);
	cin >> n;
	walls.assign(n, vector<bool>(n));
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			bool wall;
			cin >> wall;
			walls[i][j] = wall;
		}
	}
	dfs({{0,0}, {0,1}});
	cout << answer << endl;
	return 0;
}