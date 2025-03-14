#include <bits/stdc++.h>
using namespace std;

class Battleship{
private:
	string teamName;
	int SectorX;
	int SectorY;
public:
	void setInfo(string _teamName, int _x, int _y){
		this->teamName = _teamName;
		this->SectorX = _x;
		this->SectorY = _y;
	}

	string getTeamName(){
		return this->teamName;
	}
	pair<int,int> getPosition(){
		return {this->SectorX, this->SectorY};
	}
};

class Board {
	int row = 5000, col = 5000;
	vector<vector<string>> board;
public:
	Board(int _row, int _col){
		this->row = _row;
		this->col = _col;
		board.resize(row+1, vector<string>(col+1, " "));
	}

	void setBattleships(vector<Battleship>& teams){
		int n = teams.size();
		for(int i=0; i<n; i++){
			string teamName = teams[i].getTeamName();
			int xi = teams[i].getPosition().first;
			int yi = teams[i].getPosition().second;

			board[col-yi+1][xi] = teamName;
		}
	}

	void printBoard(){
		cout << "\n    <<----Battlefield---->>\n";
		for(int j=1; j<=row; j++){
			if(j==1) cout << " +";
			cout << "---+";
		}
		cout << endl;
		
		for(int i=1; i<=row; i++){
			for(int j=1; j<=row; j++){
				cout << " | ";
				cout << board[i][j];
			}
			cout << " | " << row-i+1 << endl;

			for(int j=1; j<=row; j++){
				if(j==1) cout << " +";
				cout << "---+";
			}
			cout << endl;
		}

		for(int i=1; i<=col; i++){
			if(i == 1) cout << "  ";
			cout << " " << i << "  ";
		}
		cout << endl;
	}

	void checkAdjacent(){
		vector<pair<int, int>> dir = {{0,1}, {1, 0},{-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
		
		for(int i=1; i<=row; i++){
			for(int j=1; j<=col; j++){
				string curTeam = board[i][j];
				if(curTeam == " ") continue;

				transform(curTeam.begin(), curTeam.end(), curTeam.begin(), ::tolower);

				for(auto& d : dir){
					int newx = i + d.first;
					int newy = j + d.second;

					if(newx < 1 || newy < 1 || newx > row || newy > col) 
						continue;
					
					string newTeam = board[newx][newy];
					if(newTeam == " ") continue;

					transform(newTeam.begin(), newTeam.end(), newTeam.begin(), ::tolower);
					if(curTeam != newTeam){
						board[i][j] = curTeam;
						board[newx][newy] = newTeam;
					}
				}
			}
		}
	}
};

int main()
{
	vector<Battleship> teams(6);
	teams[0].setInfo("A", 3, 5);
	teams[1].setInfo("Z", 7, 1);
	teams[2].setInfo("Z", 4, 4);
	teams[3].setInfo("A", 2, 6);
	teams[4].setInfo("A", 1, 7);
	teams[5].setInfo("z", 2, 5);

	Board game(10, 10);
	game.setBattleships(teams);
	game.printBoard(); // initial board
	game.checkAdjacent();
	game.printBoard(); // final board
	return 0;
}

/*
   <<----Battlefield---->>
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 10
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 9
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 8
 +---+---+---+---+---+---+---+---+---+---+
 | A |   |   |   |   |   |   |   |   |   | 7
 +---+---+---+---+---+---+---+---+---+---+
 |   | A |   |   |   |   |   |   |   |   | 6        
 +---+---+---+---+---+---+---+---+---+---+
 |   | z | A |   |   |   |   |   |   |   | 5        
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   | Z |   |   |   |   |   |   | 4        
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 3        
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 2        
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   | Z |   |   |   | 1        
 +---+---+---+---+---+---+---+---+---+---+
   1   2   3   4   5   6   7   8   9   10

    <<----Battlefield---->>
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 10       
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 9        
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 8        
 +---+---+---+---+---+---+---+---+---+---+
 | A |   |   |   |   |   |   |   |   |   | 7        
 +---+---+---+---+---+---+---+---+---+---+
 |   | a |   |   |   |   |   |   |   |   | 6        
 +---+---+---+---+---+---+---+---+---+---+
 |   | z | a |   |   |   |   |   |   |   | 5        
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   | z |   |   |   |   |   |   | 4        
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 3        
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   |   |   |   |   | 2        
 +---+---+---+---+---+---+---+---+---+---+
 |   |   |   |   |   |   | Z |   |   |   | 1        
 +---+---+---+---+---+---+---+---+---+---+
   1   2   3   4   5   6   7   8   9   10
*/