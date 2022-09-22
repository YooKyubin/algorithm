#include <iostream>
#include <algorithm>

using namespace std;

int n, k;
int *temp;
int *sum;
int answer = -10000001;

int main(){
    cin >> n >> k;
    temp = (int*)malloc(sizeof(int) * (n+1));
    sum = (int*)malloc(sizeof(int) * (n - k));

    for(int i=1; i < n+1; i++){
        int t = 0;
        cin >> t;
        temp[i] = temp[i-1] + t;
    }

    for(int i=0; i < n-k+1; i++){
        sum[i] = temp[i+k] - temp[i];
    }

    for(int i=0; i < n-k+1; i++){
        answer = max(sum[i], answer);
    }

    cout << answer << '\n';
    free(sum);
    free(temp);

    return 0;
}