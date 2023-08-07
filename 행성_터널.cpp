#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge{
	int weight;
	int from;
	int to;

	bool operator<(Edge input){
		return this->weight < input.weight;
	}
};

int n;
vector<vector<pair<int, int>>> planets;
vector<Edge> edges;
vector<int> root;

int Find(int x){
	if (root[x] < 0) return x;
	else return root[x] = Find(root[x]);
}

void Union(int x, int y){
	x = Find(x);
	y = Find(y);

	if (x == y) return;

	if (x > y){
		root[x] = y;
	}
	else{
		root[y] = x;
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	planets.assign(3, vector<pair<int, int>>(n));
	root.assign(n, -1);
	for (int i=0; i<n; i++){
		int x, y, z;
		cin >> x >> y >> z;
		planets[0][i] = make_pair(x,i);
		planets[1][i] = make_pair(y,i);
		planets[2][i] = make_pair(z,i);
	}
	sort(planets[0].begin(), planets[0].end());
	sort(planets[1].begin(), planets[1].end());
	sort(planets[2].begin(), planets[2].end());

	for (int i=0; i<n-1; i++){
		for (int j=0; j<3; j++){
			Edge e;
			e.from = planets[j][i].second;
			e.to = planets[j][i+1].second;
			e.weight = planets[j][i+1].first - planets[j][i].first;

			edges.push_back(e);
		}
	}
	sort(edges.begin(), edges.end());
	
	int totalCost = 0;
	int cnt = 0;
	for (Edge e: edges){
		int to = Find(e.to);
		int from = Find(e.from);

		if (to == from) continue;

		totalCost += e.weight;
		Union(to, from);
		cnt++;
		if (cnt > n-1) break;
	}
	cout << totalCost << endl;
	return 0;
}