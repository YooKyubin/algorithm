# include<iostream>
#include <string>
#include <vector>

using namespace std;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;
    
    int pre_deli = 0;
    int pre_pick = 0;
    for (int i = n-1; i > -1; i--){
        int count = 0;
        
        deliveries[i] += pre_deli;
        pickups[i] += pre_pick;
        while (deliveries[i] > 0 || pickups[i] > 0){
            deliveries[i] -= cap;
            pickups[i] -= cap;

            count++;
        }
        pre_deli = deliveries[i];
        pre_pick = pickups[i];
        
        answer += count * (i+1) * 2;
    }

    return answer;
}

int main() {
    // int cap = 2;
    // int n = 7;
    // vector<int> deliveries  {1, 0, 2, 0, 1, 0, 2};
    // vector<int> pickups     {0, 2, 0, 1, 0, 2, 0};
    int cap = 2;
    int n = 2;
    vector<int> deliveries {0, 0};
    vector<int> pickups {0, 4};
    cout << solution(cap, n, deliveries, pickups) << endl;
    return 0;
}