#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int main () {
    int64_t a,b;
    cin >> a >> b;

    int64_t sqrtB = (int64_t)sqrt(b);
    vector<bool> isNotPrime(sqrtB+1, false);
    int64_t answer = 0;

    for (int i=2; (int64_t)i*i <= b; i++){
        if (isNotPrime[i]) continue;
        for (int j=i*2; (int64_t)j*j <= b; j += i){
            isNotPrime[j] = true;
        }
        int64_t pow = (int64_t)i*i;
        while (pow <= b){
            if (pow >= a){
                answer += 1;
            }
            if (pow > LLONG_MAX / i) break;
            pow *= i;
        }
    }
    cout << answer << endl;
}