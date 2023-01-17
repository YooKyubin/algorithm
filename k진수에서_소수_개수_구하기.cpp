#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime(uint64_t n) {
    
    if (n == 2)
        return (true);
    if (n <= 1)
        return (false);

    for (uint64_t i=2; i*i < n+1; i++){
        if (n % i == 0){
            return false;
        } 
    }

    return (true);
}

int solution(int n, int k) {
    int answer = 0;

    vector<int> number;
    while (n / k > 0) {
        number.push_back(n % k);
        n = n / k;
    } number.push_back(n % k);
    
    string strNum;
    for (int i = number.size()-1; i >=0 ; i--){
        strNum += to_string(number[i]);
    }

    vector<uint64_t> intToken;
    size_t pos;
    while ((pos = strNum.find("0")) != string::npos){
        string token = (strNum.substr(0, pos));
        if (token.length() > 0)
            intToken.push_back(stoul(token));
        strNum.erase(0,pos+1);
    }
    if (strNum.substr(0, pos).length()>0)
        intToken.push_back(stoul(strNum.substr(0, pos)));

    // uint64_t maxN = *max_element(intToken.begin(), intToken.end());
    
    // vector<bool> Eratos(maxN+1, true);
    // Eratos[0] = false;
    // Eratos[1] = false;
    // for (uint64_t i=2; i < (uint64_t)sqrt(maxN)+1; i++){
    //     if (Eratos[i]) {
    //         for (uint64_t j=i*2; j < maxN+1; j+=i){
    //             Eratos[j] = false;
    //         }
    //     }
    // }
    // for (auto i: intToken){
    //     if (Eratos[i]){
    //         answer++;
    //     }
    // }
    for (auto n: intToken){
        if (isPrime(n))
            answer ++;
    }

    return answer;
}

int main() {
    // int n = 130000;
    // int k = 10;
    int n = 437674;
    int k = 3;
    cout << solution(n, k) << endl;
    return 0;
}

// 판별하려는 수가 너무나도 크다면 에라토스테네스의 체가 오히려 비효율적이다. 메모리 측면에서, 시간 측면에서는?
// sting 토큰화 하는 법을 배움
// 수가 굉장히 큰 경우를 따져볼것