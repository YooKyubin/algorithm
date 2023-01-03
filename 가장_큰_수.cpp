#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(string a, string b){
    return (a+b) > (b+a);
}

string solution(vector<int> numbers) {
    vector<string> strings;
    for(auto i : numbers){
        strings.push_back(to_string(i));
    }
    sort(strings.begin(), strings.end(), comp);
    string answer = "";
    for(auto i : strings){
        answer += i + " ";
    }
    if (answer[0] == '0'){
        answer = "0";
    }
    return answer;
}

int main(){

    // vector<int> test { 3, 30, 34, 5, 9, 33, 56, 54 };
    vector<int> test { 0,0,0,0 };
    cout << solution(test) << endl;
    string c = "012345";
    bool k = c.substr(2) < "";
    cout << k << true << endl;
    cout << c.substr(2) << endl;
    return 0;
}


/*
풀이 1
3, 34, 30을 비교할때
인덱스 0에서는 모두 같다.
인데스 1: 3을 33으로 간주하고 풀어야 한다.
    3과 비교를 하는 녀석들은 앞자리가 모두 3인 숫자들이다.
    그래서 3 다음 34가 와서 334가 될 수 있고, 3 다음 30이 와서 330이 될 수 있다.
    3보다 후 순위에 3으로 시작하는 수가 있다고 가정하면 결국 33으로 간주하고 크기 비교해도 무방하다.
    3의 두번째 인덱스는 3(같은 숫자)로 간주하고 크기 비교를 해야한다.
    따라서 큰 순서대로 정리하면 34, 3, 30 이 된다.
풀이2
두 문자열을 더한값을 서로 비교한다.
a + b 와 b + a를 비교하여 더 큰 값이 앞에 오도록하면 된다.
0이 맨 앞에 오는 경우는 항상 0이므로 answer[0] == '0' ? answer = "0" : answer 으로 처리한다.
*/