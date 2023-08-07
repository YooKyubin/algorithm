#include <iostream>
#include <string>
#include <vector>

using namespace std;

int r1, c1, r2, c2;
int maxVal = 0;
vector<vector<int>> nums;

int max(int a, int b) { return a > b ? a : b; }

void makeSpiral(){
    int x = 0;
    int y = 0;
    vector<int> dx = {0, -1, 0, 1};
    vector<int> dy = {1, 0, -1, 0};

    int val = 1;
    int cnt = 1;
    int dist = 1;
    if (r1 <= x && x <= r2 && c1 <= y && y <= c2){
        nums[x-r1][y-c1] = val; // nums[][] = 1;
        ++cnt;
    }
    int maxCnt = (r2 - r1 +1 ) * (c2 - c1 + 1);
    while (cnt <= maxCnt){
        for (int i=0; i<4; i++){
            if (i == 2)  dist++;
            for (int d=0; d<dist; d++){
                x += dx[i];
                y += dy[i];
                ++val;
                if (r1 <= x && x <= r2 && c1 <= y && y <= c2){
                    nums[x-r1][y-c1] = val;
                    maxVal = max(val, maxVal);
                    cnt++;
                }
            }
        }
        dist++;
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin >> r1 >> c1 >> r2 >> c2;
    nums.assign(r2 - r1 + 1, vector<int>(c2 - c1 + 1, 0));

    makeSpiral();

    int maxLen = to_string(maxVal).length();
    vector<string> answer;
    for (int i=0; i<r2-r1+1; i++){
        string line="";
        for (int j=0; j<c2-c1+1; j++){
            string temp = to_string(nums[i][j]);
            for (int blank=0; blank < maxLen - temp.length(); blank++){
                line += " ";
            }
            line += temp + " ";
        }
        answer.push_back(line);
    }

    for (auto ans : answer){
        cout << ans << "\n";
    }
    return 0;
}