#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b){
    return a > b ? a : b;
}

struct Pos {
    int x;
    int y;

    bool operator==(Pos input){
        return x == input.x && y == input.y;
    }
    Pos operator+(Pos input){
        Pos res;
        res.x = this->x + input.x;
        res.y = this->y + input.y;
        return res;
    }
};

int n, m;
vector<string> board;
vector<int> visited(26, 0);
int answer = 0;

vector<Pos> dir = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

bool OOB(Pos input){
    return input.x < 0 || input.x >= n || input.y < 0 || input.y >= m;
}

void dfs(Pos cur, int depth){
    int curVal = board[cur.x][cur.y] - 'A';
    // visited[(int)curVal] = true;
    answer = max(answer, depth);
    
    for (Pos d : dir){
        Pos next = cur + d;
        if ( OOB(next) ) continue;
        int nextVal = board[next.x][next.y] - 'A';
        if ( visited[(int)nextVal] != 0 ) continue;

        visited[nextVal]++;
        dfs(next, depth+1);
        visited[nextVal]--;
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i=0; i < n; i++){
        string input;
        cin >> input;
        board.push_back(input);
    }

    Pos start = {0, 0};
    visited[board[start.x][start.y]- 'A'] += 1;
    dfs(start, 1);
    
    cout << answer << endl;

    return 0;
}
