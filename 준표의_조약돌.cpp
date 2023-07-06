#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }

int main () {
    int n, w, b;
    string road;
    vector<int> dist;
    vector<int> cumsum;
    int answer = 0;
    int numRealBlack = 0;
    cin >> n >> b >> w;
    cin >> road;
    int cntW = 0;
    for (auto c: road){
        if (c == 'B'){
            dist.push_back(cntW);
            cntW = 0;
        }
        else {
            cntW++;
        }
    }
    dist.push_back(cntW);
    numRealBlack = dist.size()-1;
    cumsum.assign(dist.size()+1, 0);
    cumsum[1] = dist[0];
    for (int i=1; i < cumsum.size(); i++){
        cumsum[i] = dist[i-1] + cumsum[i-1];
    }
    if (b >= numRealBlack){
        answer = cumsum.back() + numRealBlack;
        b = numRealBlack;
    }
    else{
        for (int i=0; i < cumsum.size()-b-1; i++){
            int j = i + b+1;
            answer = max(answer, cumsum[j] - cumsum[i] + b);
        }
    }
    if (answer - b >= w){
        cout << answer << endl;
    }
    else {
        cout << 0 << endl;
    }
    return 0;
}

/*
B의 왼쪽의 W의 개수를 저장, 마지막B의 오른쪽에 W가 있다면 이건 포함 시켜도 될듯
새로운 배열이 만들어지면 그 배열에 대해서 개수가 B개, 그 합이 최대가 되는 부분 배열을 찾는 문제가 된다.
최대합이 W를 넘지 않으면 0을 출력
누적합으로 요소가 B개인 배열의 합을 구하기

알고보니 투 포인터로 구하면 훨씬 쉽게 문제를 해결할 수 있었음
*/