#include <bits/stdc++.h>
using namespace std;

/*

Objects:
1. two players
2. dice
3. board -> ladders, snake

Actions:
1. roll dice, if 6 then roll again
2. move player
3. check player gets ladder or snake
4. check player wins
*/

class Player {
private:
    int player1, player2;

    unordered_map<int, int> snakes;
    unordered_map<int, int> ladders;
    
    int rollDice(){
        return rand()%6 + 1;
    }

public:
    Player() {
        player1 = 0;
        player2 = 0;

        snakes[24] = 5;
        snakes[33] = 13;
        snakes[42] = 30;
        snakes[62] = 35;
        snakes[74] = 52;
        snakes[92] = 41;
        snakes[97] = 79;

        ladder[3] = 15;
        ladder[7] = 22;
        ladder[20] = 41;
        ladder[37] = 67;
        ladder[50] = 70;
        ladder[70] = 90;
        ladder[79] = 99;
    }



};

int main(){
    
    while(true){
        
    }
}