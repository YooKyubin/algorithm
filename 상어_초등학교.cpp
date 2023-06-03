#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n;
vector<int> dx {1, -1, 0, 0};
vector<int> dy {0, 0, -1, 1};
vector<int> studentSequece;
vector<vector<int>> favoriteStudents;
vector<vector<int>> table;
// void printTable();

bool OOB(int x, int y){
    return x < 0 || x >= n || y < 0 || y >= n;
}
int pow(int a, int x){
    int ret = 1;
    for (int i = 0; i < x; i++) ret *= a;
    return ret; 
}

struct Seat {
    int number = 0;
    int favoriteCount = 0;
    int emptyCount = 4;
    int order;

    void init(int x, int y){
        if (x == 0 || x == n-1) this->emptyCount -= 1;
        if (y == 0 || y == n-1) this->emptyCount -= 1;
        this->order = x * n + y;
    }

    void CalPriority(int number){
        int x = this->order / n;
        int y = this->order % n;
        vector<int>& favorStu = favoriteStudents[number];

        for (int i=0; i < 4; i++){
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            if ( OOB(nextX, nextY) ) continue;

            if ( find(favorStu.begin(), favorStu.end(), table[nextX][nextY]) != favorStu.end()){
                this->favoriteCount++;
            }
            if ( table[nextX][nextY] != 0 ) this->emptyCount -= 1;

        }
    }
};

struct cmp{
    bool operator()(const Seat a, const Seat b){
        /*
        2. favoriteCount가 높아야 한다. 같다면 3번 조건으로
        3. emptyCount가 높아야 한다. 같다면 4번 조건
        4. 좌석의 순서가 작은게 높다.
        */
        if (a.favoriteCount == b.favoriteCount){
            if ( a.emptyCount == b.emptyCount ){
                return a.order > b.order;
            }
            else{
                return a.emptyCount < b.emptyCount;
            }
        }
        else{
            return a.favoriteCount < b.favoriteCount;
        }
    }
};

int calSatisfaction(){
    int res = 0;
    for (int x=0; x < n; x++){
        for (int y=0; y < n; y++){

            int cnt = 0;
            for (int i = 0; i < 4; i++){
                int nextX = x + dx[i];
                int nextY = y + dy[i];
                if (OOB(nextX, nextY)) continue;
                
                int number = table[x][y];
                vector<int>& favorStu = favoriteStudents[number];
                if ( find(favorStu.begin(), favorStu.end(), table[nextX][nextY]) != favorStu.end()){
                    cnt++;
                }
            }
            if (cnt != 0) res += pow(10, cnt-1); 
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    studentSequece.assign(n*n, 0);
    favoriteStudents.assign(n*n + 1, vector<int>(4));
    table.assign(n*n + 1, vector<int>(n*n +1, 0));

    for (int i=0; i < n * n; i++){
        int stu = 0;
        cin >> stu;
        studentSequece[i] = stu;
        for (int j=0; j < 4; j++){
            int input;
            cin >> input;
            favoriteStudents[stu][j] = input;
        }
    }

    for (auto number: studentSequece){
        priority_queue<Seat, vector<Seat>, cmp> pq;
        for (int i=0; i < n; i++){
            for (int j=0; j<n; j++){
                if (table[i][j] != 0) continue;
                Seat seat;
                seat.init(i, j);
                seat.CalPriority(number);
                pq.push(seat);
            }
        }
        int x = pq.top().order / n;
        int y = pq.top().order % n;
        table[x][y] = number;
        // cout << "emptyCount: " << pq.top().emptyCount << endl;
        // cout << "favoriteCount: " << pq.top().favoriteCount << endl;
        // printTable();
    }

    for (int x=0; x < n; x++){
        for (int y=0; y < n; y++){

            for (int i = 0; i < 4; i++){
                int nextX = x + dx[i];
                int nextY = y + dy[i];
                if (OOB(nextX, nextY)) continue;

            }
        }
    }
    cout << calSatisfaction() << endl;

    return 0;
}


// void printTable(){
//     cout << "Print Table " << endl;
//     for (int i=0; i < n; i++){
//         for (int j=0; j < n; j++){
//             cout << table[i][j] << " ";
//         }cout << endl;
//     }
// }