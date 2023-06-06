#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> child_t;
int n;
vector<child_t> graph;

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    graph = vector<child_t>(n+1);
    for (int i=0; i<n; i++){
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].first = b;
        graph[a].second = c;
    }

    int lastNode = 1;
    int cnt = 0;
    while (graph[lastNode].second != -1) {
        cnt++;
        lastNode = graph[lastNode].second;
    }

    cout << (n -1) * 2 - cnt << endl;

}

/*
루트 노드에서 중위 순회의 마지막 노드까지의 거리만 안다면
총 간선의 개수 * 2 - (루트노드에서 중위순회 마지막 노드까지의 거리)로 계산할 수 있다.
*/