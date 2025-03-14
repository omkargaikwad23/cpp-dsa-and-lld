#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;

class TicTakToe{
private:
    vector<vector<char>> grid;
    vector<vector<bool>>filled;

    bool checkLine(int x, int y, vector<pii> &dir){
        int cnt = 1;
        char ch = grid[x][y];
        int visited[3][3];
        memset(visited, false, sizeof(visited));
        queue<pair<int, int>>q;
        q.push({x, y});
        visited[x][y] = true;

        while(!q.empty()){
            x = q.front().first;
            y = q.front().second;
            q.pop();
            
            for(auto d : dir){
                int newx = x + d.first;
                int newy = y + d.second;
                
                if(newx < 0 || newy < 0) continue;
                if(newx>=3 || newy >= 3) continue;
                if(visited[newx][newy]) continue;
                
                if(grid[newx][newy] == ch){
                    // cout << newx << " " << newy << endl;
                    q.push({newx, newy});
                    visited[newx][newy] = true;
                    cnt++;
                }
                if(cnt >= 3) break;
            }
        }
        return (cnt>=3);
    }
public:
    TicTakToe(){
        grid.resize(3, vector<char>(3, '-'));
        filled.resize(3, vector<bool>(3, false));
    }

    void setMove(int x, int y, bool turn){
        if(turn){
            grid[x][y] = 'X';
        }else{
            grid[x][y] = 'O';
        }
        filled[x][y] = true;
    }

    bool isGridFilled(int x, int y){
        return filled[x][y];
    }

    void printGrid(){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << "\n";
    }
    
    bool isGameEnded(int x, int y){
        vector<pii> vectHorizontal = {{0, 1}, {0, -1}};
        vector<pii> vectVertical = {{1, 0}, {-1, 0}};
        vector<pii> vectDiagonal = {{1, 1}, {-1, -1}};
        vector<pii> vectDiagonal2 = {{1, -1}, {-1, 1}};

        if(checkLine(x, y, vectHorizontal)) return true;
        if(checkLine(x, y, vectVertical)) return true;
        if(checkLine(x, y, vectDiagonal)) return true;
        if(checkLine(x, y, vectDiagonal2)) return true;

        return false;
    }
};

bool isValid(int x, int y){
    if(x < 0 || y < 0) return false;
    if(x > 2 || y > 2) return false;
    return true;
}

int main(){
    TicTakToe t;
    int x, y, totalMoves = 9;
    bool firstPlayerTurn = true, nooneWins = true;

    cout << "\n<<------TIC-TAK-TOE----->>\n";
    t.printGrid();

    while(totalMoves--){
        if(firstPlayerTurn){
            cout << "Enter coordinates Player 1: ";
        } else {
            cout << "Enter coordinates Player 2: ";
        }
        cin >> x >> y;

        if(!isValid(x, y)){
            cout << "Provided position is not valid.\n\n";
            continue;
        }
        if(t.isGridFilled(x, y)){
            cout << "Position is already occupied.\n\n";
            continue;
        }
        t.setMove(x, y, firstPlayerTurn);
        t.printGrid();

        if(t.isGameEnded(x, y)){
            cout << (firstPlayerTurn ? "First " : "Second ") << " player won the game!";
            nooneWins = false;
            break;
        }
        firstPlayerTurn = !firstPlayerTurn;
    }

    if(nooneWins){
        cout << "Noone could win the game!";
    }
}