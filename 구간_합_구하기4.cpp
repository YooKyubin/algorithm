#include <iostream>
#include <vector>


using namespace std;

int N, M;
int i, j;
int answer[100001];
int arr[100001];

int main(){
    int temp = 0;
    arr[0] = 0;
    cin >> N >> M;

    for(int a = 0; a < N; a++){
        cin >> temp;
        arr[a+1] = temp + arr[a];
    }

    for(int a = 0; a < M; a++){
        scanf("%d %d", &i, &j);
        answer[a] = arr[j] - arr[i-1];
        printf("%d\n", answer[a]);
    }

    return 0;

}