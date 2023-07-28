#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int maxDepth;
int n, m;
vector<vector<int>> parent;
vector<int> depth;
vector<vector<int>> graph;

void dfs(int v){
	for (int next: graph[v]){
		if (depth[next] != -1) continue;
		parent[next][0] = v;
		depth[next] = depth[v] + 1;
		dfs(next);
	}
}

void setParent(){
	for (int level=1; level <= maxDepth; level++){
		for (int node=1; node <= n; node++){
			if (parent[node][level-1] == -1) continue;
			parent[node][level] = parent[parent[node][level-1]][level-1];
			// 점화식, level 모르는 값을 정의하기 위해 아는 값 level-1에서 유도해낸다.
		}
	}
}

int LCA(int a, int b){
	if (depth[a] < depth[b]) { swap(a,b); } // 깊이가 더 깊은 노드를 a로 설정

	// 두 노드의 깊이를 같도록 이동
	int gap = depth[a] - depth[b];
	{
		int i = 0;
		while (gap != 0){
			if (gap % 2 == 1){
				a = parent[a][i];
			}
			gap /= 2;
			i++;
		}
		
	}

	if (a == b) return a;

	// 최소 공통 조상 노드 바로 자식까지 이동
	for (int i=maxDepth; i >=0; i--){
		if (parent[a][i] == -1) continue;
		if (parent[a][i] != parent[b][i]) {
			a = parent[a][i];
			b = parent[b][i];
		}
	}
	return parent[a][0]; // 최소 공통 조상 노드의 바로 자식에서 한 단계 부모 = 최소 공통 조상 노드
	
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n;
	maxDepth = ceil(log2(n));
	parent.assign(n+1, vector<int>(maxDepth+1, -1));
	depth.assign(n+1, -1);
	graph.assign(n+1, vector<int>());
	for (int i=0; i<n-1; i++){
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	depth[1] = 0;
	dfs(1);
	setParent();

	cin >> m;
	while (m--){
		int a, b;
		cin >> a >> b;
		cout << LCA(a, b) << "\n";
	}

	return 0;
}