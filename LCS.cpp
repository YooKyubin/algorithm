#include <iostream>
#include <string>
#include <vector>

using namespace std;

string line1;
string line2;
vector table(1001, vector<int>(1001, 0));

int main(){

    getline(cin, line1);
    getline(cin, line2);

    // table과 문자열의 인덱스를 맞추기 위해 억지로 0 번 인덱스는 비우기
    line1.insert(0, " ");
    line2.insert(0, " ");
    
    for (int i=0; i < line1.size(); i++){
        for(int j=0; j<line2.size(); j++){
            // 0을 참고해야 하기 때문에 0라인은 비워둡니다.
            if ( i == 0 || j == 0 ) continue;

            if ( line1[i] == line2[j] ) {
                table[i][j]  = table[i-1][j-1] + 1;
            }
            else{
                table[i][j] = max(table[i-1][j], table[i][j-1]);
            }
        }
    }
    cout << table[line1.size()-1][line2.size()-1] << endl;
    return 0;
}