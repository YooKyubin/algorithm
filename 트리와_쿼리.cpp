#include <iostream>
#include <vector>

using namespace std;

int n, r, q;
vector < vector<int>> graph;
// vector<vector<int>> tree;
vector<int> subNodes;

// void makeTree(int currentNode, int parrent) {
// 	for (auto Node : graph[currentNode]) {
// 		if (Node != parrent) {
// 			tree[currentNode].push_back(Node);
// 			makeTree(Node, currentNode);
// 		}
// 	}
// }

// void countSubtreeNodes(int currentNode) {
// 	for (auto Node : tree[currentNode]) {
// 		countSubtreeNodes(Node);
// 		subNodes[currentNode] += subNodes[Node];
// 	}
// }

void dfs(int currentNode, int parrent){
    for (auto Node : graph[currentNode]) {
		if (Node != parrent) {
			dfs(Node, currentNode);
		    subNodes[currentNode] += subNodes[Node];
		}
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> r >> q;
	graph.assign(n + 1, vector<int>());
	// tree.assign(n + 1, vector<int>());
	subNodes.assign(n + 1, 1);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	// makeTree(r, -1);
	// countSubtreeNodes(r);
    dfs(r, -1);

	cout << "nice!" << endl;

	for (int i = 0; i < q; i++) {
		int node;
		cin >> node;
		cout << subNodes[node] << "\n";
	}

	return 0;
}

/*
거기 문제집에서 나온대로 풀긴했지만 사실 이거 그냥 dfs로 풀어도 되네
어짜피 트리이고 루트를 알기때문에 dfs 순서가 그대로 트리 탐색이 가능해지네
심지어 메모이제이션도 필요가 없음
*/