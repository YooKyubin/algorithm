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

    // 굳이 필요 없는 변수들이 있지만 이해를 위해서 굳이 굳이 이름을 달리해가며 변수로 저장했다
    int64_t curTime = lo;
    int64_t targetTime = curTime - 1;
    int64_t curChild = countChild(targetTime);
    int64_t remainedChild = n - curChild;
    for (int i=0; i<times.size(); i++){
        if (targetTime % times[i] == 0 && --remainedChild == 0){
            cout << i+1 << endl;
            break;
        }
    }

    return 0;
}

/*
x축 : 시간
y축 : 사람 수
*/