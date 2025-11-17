#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
3 5
S###.
.....
###E#

OUTPUT: 5
Steps required to reach from 'S' to 'E'?
*/

// https://open.kattis.com/problems/dungeon

int shortest_path(vector<vector<char>> path, pair<int, int> src, int r, int c) {
    // variables to keep track of no of steps taken
    bool reached_end = false;
    int move_count = 0;
    int nodes_left_in_layer = 1;
    int nodes_in_next_layer = 0;
    
    // to keep track of visited cells
    vector<vector<bool>> visited(r, vector<bool>(c, false));
    
    // define 4 directions to move: up, down, right, left
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    queue<pair<int, int>> q;
    q.push(src);
    visited[src.first][src.second] = true;

    while(!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if(path[row][col] == 'E') {
            reached_end = true;
            break;
        }

        // exploring neighbours
        for(int i = 0; i < 4; i++) {
            int new_row = row + directions[i].first;
            int new_col = col + directions[i].second;

            // skip out of bounds locations
            if(new_row < 0 || new_col < 0) continue;
            if(new_row >= r || new_col >= c) continue;

            // skip visited or blocked locations
            if(visited[new_row][new_col]) continue;
            if(path[new_row][new_col] == '#') continue;

            q.push({new_row, new_col});
            visited[new_row][new_col] = true;
            nodes_in_next_layer++;
        }
        
        nodes_left_in_layer--;
        if(nodes_left_in_layer == 0) {
            nodes_left_in_layer = nodes_in_next_layer;
            nodes_in_next_layer = 0;
            move_count++;
        }
    }
    
    if(reached_end) {
        return move_count;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int r, c;
    cin >> r >> c;
    
    vector<vector<char>> path;
    pair<int, int> src;
    
    for(int i = 0; i < r; i++) {
        vector<char> row;
        for(int j = 0; j < c; j++) {
            char ch;
            cin >> ch;
            if(ch == 'S') {
                src.first = i;
                src.second = j;
            }
            row.push_back(ch);
        }
        path.push_back(row);
    }

    int length = shortest_path(path, src, r, c);
    
    if(length < 0) {
        cout << "Trapped!";
    } else {
        cout << "Escaped in " << length << " minute(s).";
    }
    return 0;
}