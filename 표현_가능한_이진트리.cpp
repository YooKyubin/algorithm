#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool dfs(long long v, const vector<bool>& number, int32_t level){
    if (v % 2 == 1){ // 리프노드는 true 반환;
        cout << "v : " << v;
        cout << " return true" << endl;
        return true;
    }
    
    long long pow = 1 << level;
    
    int left = v - pow/2;
    int right = v + pow/2;

    bool left_ret = dfs(left, number, level-1);
    bool right_ret = dfs(right, number, level-1);
    bool child = left_ret && right_ret;
    
    if (!child) { // 자식 둘 중 하나라도 false 라면
        cout << "v : " << v;
        cout << " return false" << endl;
        return false;
    }

    if (!number[v-1]){

        bool left_res = number[left-1];
        bool right_res = number[right-1];

        // 둘 다 0 이여야함
        cout << "v : " << v;
        printf(" return !(%s || %s) \n", left_res ? "true": "false", right_res ? "true": "false");
        return !(left_res || right_res);
        // if (left_res)
        //     return false;
        // if (right_res)
        //     return false;
    }
    cout << "v : " << v;
    cout << " return true (final)" << endl;
    return true;
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    for (auto n : numbers){
        long long pow = 1;
        int length = 0;
        long long root = 1;
        int level = 0;

        while (n > pow){
            pow *= 2;
            length += 1;

        }

        while (length >= root * 2){
            root *= 2;
            level += 1;
        }

        vector<bool> boolNum(root * 2, false);
        for (int i=0; i <= length; i++) {
            boolNum[i] = n % 2;
            n /= 2;
        }

        cout << "length: " << length << endl;
        cout << "pow: " << pow << endl;
        cout << "root: " << root << endl;
        cout << "level: " << level << endl;
        cout << endl;

        answer.push_back(dfs(root, boolNum, level));
    }

    return answer;
}

int main(){
    // vector<int64_t> numbers {7, 42, 5, 63, 111, 95};
    vector<int64_t> numbers {140187732541439};
    // vector<int64_t> numbers {15};
    // vector<int64_t> numbers {65535};
    // vector<int64_t> numbers {8585215};
    // vector<int64_t> numbers {4294967295};
    // vector<int64_t> numbers {95};


    for (auto i: solution(numbers)){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

/*
홀수는 무조건 리프 노드, 종료 조건
left = value - 2 ** level
right = value + 2** level

dfs : 
자식 dfs 결과가 false라면 나도 false리턴
그게 아니라면 (내 자식들은 문제 없다는 소리, 자신이 문제가 있는지를 검)
자신이 1이라면 true 리턴
자신이 0이라면 자식 노드 검사, 자식 둘중 하나라도 1이라면 false리턴

비트 마스킹으로 가능할듯
- 비트마스킹으로 하느라 인덱싱이 꼬엿음
- int64_t의 비트 저장 방식을 이해하지 못하겟음 왜 32 비트 이후로 다 1로 초기화 되어 있는거임?
*/