#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    unordered_map<string, int> hash;
    for (auto cloth: clothes){
        if(hash.find(cloth[1]) == hash.end()){
            hash.insert({cloth[1], 1});
        }
        else{
            hash[cloth[1]] += 1;
        }
    }
    int answer = 1;
    for(pair<string, int> i: hash){
        cout << i.first << ", " << i.second << endl;
        answer *= i.second+1;
    }
    return answer - 1;
}

int main(){
    vector<vector<string>> test {{"yellow_hat", "headgear"}, {"blue_sunglasses", "eyewear"}, {"green_turban", "headgear"}};
    cout << solution(test) << endl;
    return 0;
}

/*
경우의 수 문제
옷의 종류당 (옷의 개수 + 1(옷을 입지 않은 경우)) 만큼의 경우의 수를 가짐
따라서 각각을 곱해주면 모든 경우의 수가 계산됨.
단, [스파이는 하루에 최소 한 개의 의상은 입습니다.] 라는 조건 때문에 전체 경우의 수에서 -1 해야 한다.
*/
