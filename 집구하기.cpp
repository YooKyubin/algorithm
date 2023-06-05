#include <iostream>
#include <vector>
#include <queue>

#define Node pair<int, int>
#define INF 100000001

using namespace std;

int v, e;
int macCnt, starCnt;
int macMinLimit;
int starMinLimit;
vector<int> distFromMac;
vector<int> distFromStar;
vector<int> isMac;
vector<int> isStar;
vector<bool> isHouse;
vector<vector<Node>> graph;

// vector<int> dijkstar(vector<int>& start){
void dijkstar(vector<int>& start, vector<int>& dist){
    priority_queue<Node> pq;
    // vector<int> dist(v+1, INF);
    dist.assign(v+1, INF);
    for (auto s: start){
        dist[s] = 0;
        pq.push({0, s});
    }
    while (!pq.empty()){
        int cur = pq.top().second;
        int weight = - pq.top().first;
        pq.pop();

        if (dist[cur] < weight) continue;
        for (auto edge : graph[cur]){
            int next = edge.second;
            int nextWeight = weight + edge.first;

            if( nextWeight < dist[next] ){
                dist[next] = nextWeight;
                pq.push({ -nextWeight, next });
            }
        }
    }
    // return dist;
}

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> v >> e;
    // isMac = vector<bool>(v, false);
    // isStar = vector<bool>(v, false);
    isHouse = vector<bool>(v+1, true);
    graph.assign(v+1, vector<Node>());
    while (e--){
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({w, b});
        graph[b].push_back({w, a});
    }

    cin >> macCnt >> macMinLimit;
    for (int i=0; i<macCnt; i++){
        int mac;
        cin >> mac;
        isHouse[mac] = false;
        isMac.push_back(mac);
    }

    cin >> starCnt >> starMinLimit;
    for (int i=0; i<starCnt; i++){
        int star;
        cin >> star;
        isHouse[star] = false;
        isStar.push_back(star);
    }

    // distFromMac = dijkstar(isMac);
    // distFromStar = dijkstar(isStar);
    dijkstar(isMac, distFromMac);
    dijkstar(isStar, distFromStar);
    
    int minDist = INF;
    for (int i=1; i<v+1; i++){
        if (!isHouse[i]) continue;
        if (distFromMac[i] > macMinLimit || distFromStar[i] > starMinLimit) continue;
        // cout << distFromMac[i] << ", " << distFromStar[i] << endl;
        if (minDist > distFromMac[i] + distFromStar[i]){
            minDist = distFromMac[i] + distFromStar[i];
        }
    }
    if (minDist == INF) minDist = -1;
    cout << minDist << endl;

    return 0;
}