#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

int64_t n, m;
vector<int> times;

int64_t countChild(int64_t currentTime){
    int64_t child = 0;
    for (int i=0; i < times.size(); i++){
        currentTime % times[i] == 0 
        ? child += currentTime / times[i]
        : child += currentTime / times[i] + 1;
    }
    return child;
}

bool check(int64_t mid){
    return countChild(mid) >= n;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    times = vector<int>(m);
    for (int i=0; i < m; i++) { cin >> times[i]; }
    
    int64_t lo = 0;
    int64_t hi = n * 30;
    while (lo<=hi){
        // cout << lo << " " << hi << endl;
        int64_t mid = (lo + hi) / 2;
        if (check(mid)){
            hi = mid-1;
        }
        else {
            lo = mid+1;
        }
    }

    int64_t curTime = lo;
    int64_t targetTime = curTime - 1;
    int64_t curChild = countChild(targetTime);
    for (int i=0; i<times.size(); i++){
        if ((targetTime) % times[i] == 0 && ++curChild == n){
            cout << i+1 << endl;
            break;
        }
    }

    return 0;
}

/*
x축 : 시간
y축 : 사람 수

어떤 특정 시간에 사람의 수가 n보다 작거나 같다면: 사람 수 <= n : 중 최대값
n보다 작거나 같을 수 있는 시간중 최대값에서의 사람 수와 실제 총 사람의 수를 비교하여 그 차이만큼 
그 시간에 남는 놀이 기구에 넣는다.
*/