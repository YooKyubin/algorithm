#include <iostream>
#include <vector>

using namespace std;

int n, s;
vector<int> seq;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int answer = 0;

    cin >> n >> s;
    seq.reserve(n);
    for (int i=0; i<n; i++){
        cin >> seq[i];
    }
    for (int i=1; i< (1<<n); i++){
        int number = 0;
        for(int j=0; j < n; j++){
            if ( i & 1<<j ) number += seq[j];
        }
        if (number == s) answer++;
    }

    cout << answer << "\n";
    return 0;
}