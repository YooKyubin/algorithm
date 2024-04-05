#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct node {
    int numberOfCards = 0; // 노드가 가지고 있는 카드 개수
    int target = 0; // 단순히 target 인덱스가 헷갈리는게 싫어서 타겟도 멤버변수로 넣으려 했으나 굳이 사용하진 않았다.
    queue<int> childNode; // 자식 노드들이 큐에 순서대로 저장되어 있음
    queue<int> orderOfCards;
};

// queue<int> getCardSequence(int target, int numberOfCards){
//     queue<int> ret;

//     // printf("target : %d, the number of cards: %d \n", target, numberOfCards);
//     while(numberOfCards--){
//         for (int number: vector({1,2,3})){
//             if (target - number > numberOfCards * 3) continue;
//             else if (target - number < numberOfCards) continue;

//             ret.push(number);
//             target -= number;
//             break;
//         }
//     }

//     return ret;
// }

unordered_map<int, unordered_map<int, queue<int>>> memo;

// chat GPT의 최적화 코드
queue<int> getCardSequence(int target, int numberOfCards){
    if (memo[target].count(numberOfCards)) {
        return memo[target][numberOfCards];
    }

    queue<int> ret;
    if (numberOfCards == 0) {
        memo[target][numberOfCards] = ret;
        return ret;
    }

    for (int number: vector({1,2,3})){
        if (target - number > numberOfCards * 3) continue;
        else if (target - number < numberOfCards) continue;

        queue<int> candidate = getCardSequence(target - number, numberOfCards - 1);
        if (!candidate.empty() || numberOfCards == 1) {
            ret.push(number);
            while (!candidate.empty()) {
                ret.push(candidate.front());
                candidate.pop();
            }
            memo[target][numberOfCards] = ret;
            return ret;
        }
    }

    memo[target][numberOfCards] = ret;
    return ret;
}

int dfs(int v, vector<node>& nodes){
    if (nodes[v].childNode.empty()){ // 리프노드 인 경우
        nodes[v].numberOfCards++;
        std::cout << "leaf node: " << v << endl;
        return v;
    }
    int n = nodes[v].childNode.front();
    nodes[v].childNode.pop();
    nodes[v].childNode.push(n);

    return dfs(n, nodes);
}

vector<int> solution(vector<vector<int>> edges, vector<int> target) {
    int n = target.size() + 1;
    vector<int> answer;
    vector<int> result; // 리프노드 방문 순서가 차례대로 들어갈거임
    vector<vector<int>> temp(n);

    vector<node> nodes(n);

    for (vector<int> edge : edges) {
        int par = edge[0];
        int chi = edge[1];

        temp[par].push_back(chi);
    }
    for (int i=0; i < n; i++){
        sort(temp[i].begin(), temp[i].end());
        // childNode[i] <- temp[i];
        for (int j: temp[i]){
            nodes[i].childNode.push(j);
        }
    } // temp에 잠깐 넣고 sort 해서 childNode에 넣어주는건 알겠는데 굳이 필요해? 굳이 필요한거같은데

    int cnt = 0;
    bool flag = true;
    while (flag){
        int leafNode = dfs(1, nodes);
        result.push_back(leafNode);
        std::cout << "cnt: "<< ++cnt << endl;

        if (target[leafNode-1] < nodes[leafNode].numberOfCards){
            // 방법이 없는 경우: 아직 카드가 부족한 노드가 있는데, 이미 카드가 넘쳐버린 노드가 있는 경우
            return { -1 };
        }

        // 여기서 확인해야 검사하는 코드가 필요한데.. 
        //모든 리프노드가 조건을 만족해야 while문이 멈춘다. => 하나라도 만족하지 않으면 while문은 계속 돈다...
        flag = false;
        for (int i =1; i < n; i++){

            if (target[i-1] > nodes[i].numberOfCards * 3){
                flag = true;
            }
        }
    }
    cout << "result: " ;
    for (int i: result){
        std::cout << i<< " ";
    }std::cout << endl;
    

    for (int i=1; i < n; i++){
        nodes[i].orderOfCards = getCardSequence(target[i-1], nodes[i].numberOfCards);
    }
    
    for (int i =1; i < n; i++){ // 단순 print 코드
        std::cout << i<< ": " << nodes[i].orderOfCards.size() << endl;
    }

    for(int i: result){
        int t = nodes[i].orderOfCards.front();
        nodes[i].orderOfCards.pop();
        answer.push_back(t);
    }

    return answer;
}

int main() {
    vector<vector<int>> edges {{2, 4}, {1, 2}, {6, 8}, {1, 3}, {5, 7}, {2, 5}, {3, 6}, {6, 10}, {6, 9}};
    vector<int> target {0, 0, 0, 3, 0, 0, 5, 1, 2, 3};
    // vector<vector<int>> edges {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}};
    // vector<int> target {0, 0, 0, 3, 0, 3};
    // vector<vector<int>> edges {{1, 2}, {1, 3}};
    // vector<int> target {0, 7, 3};
    for (auto i: solution(edges, target)){
        std::cout << i << " ";
    }std::cout << endl;
    return 0;
}

/*
target에 있는 녀석들 중 가장 큰 수(maxTarget)를 하나 가져와서 해당 리프노드에 
maxTarget % 3 == 0 ? maxTarget / 3 : maxTarget / 3 + 1 만큼 블럭이 쌓일 때 까지 트리 탐색을 해야한다.
- 아니야 이게 아니야 이건 올바르지 못한 알고리즘이야

루트부터 리프까지 탐색하는데 만약 노드가 리프 노드라면 노드의 이름을 순서대로 push_back 해둘 저장소 만들기

가장 짧고 사전 순으로 빠른걸 원하니까 card3부터 꾸역 꾸역 그리드로 넣으면 그 순서를 뒤집었을 때 가장 짧은 사전 순이 나오지 않을까?

자식 노드를 탐색할 때 dfs 호출 하고 그 다음에 자식 노드의 순서가 있는 큐의 queue.front()를 queue.back() 위치로 넣는 작업을 해야함

---

루트부터 리프까지 탐색 - 만약 노드가 리프 노드라면 노드의 이름을 순서대로 childNode.push_back() 해두기
while 종료는 타겟이 가장 큰 노드가 가지고 있는 카드의 수로 타켓을 만들 수 있을 때, 즉 maxTarget / 3 혹은 ()+ 1 
dfs가 호출 되면 탐색된 노드의 자식 노드 순서를 업데이트한다. (맨 앞이 맨 뒤로가서 줄서기)
만약 리프 노드라면 위에서 말한대로 push_back하고,
자신의 카드 수(numerOfCards)를 +1 한다. (마지막에 자신의 target을 자신의 카드 수로 만들 수 있는지 확인해야함)

answer 는 가장 짧고 사전순이어야 한다.............
각 node에 대한 getCardSequence가 사전순이어야 한다.
    (2,2) 보다는 (1,3)을 원한다.
target과 카드 개수로 어떻게 카드 넘버를 알 수 있을까??????????
    target > number of cards * 3 : 카드가 적은 경우
    target < number of cards : 카드가 많은 경우


지금 문제는 repeat 을 정하기 위해 maxTarget을 구하는데 여기서 target의 크기가 같은 경우 노드의 숫자가 더 작은 노드가 채택된다.
그래서 뒤에 있는 노드는 target이 큰데도 카드를 모자르게 받고 while이 끝난다.
- 그래서 while 돌때마다 모든 leaf node(사실 굳이 리프노드가 아닌 모든 노드를 탐색해도 크게 차이가 없을 듯)를 확인해야한다. 확인하면서
    - 하나라도 카드 수가 target 보다 많은 경우: 그냥 아예 불가능, -1 리턴
    - 모든 노드에서 각 노드의 카드 수 * 3 이 target 보다 작은 경우: 지금이야 송태섭 뚫어!

*/