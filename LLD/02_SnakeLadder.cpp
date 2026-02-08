/*
================================================================================
                    LOW-LEVEL DESIGN: SNAKE AND LADDER
================================================================================

PROBLEM:
  Design a Snake and Ladder board game for multiple players.

REQUIREMENTS:
  1. Board of configurable size (default 100)
  2. Configurable snake and ladder positions
  3. Support 2+ players taking turns
  4. Dice roll (1-6), if roll is 6 player gets another turn
  5. Landing on a snake head moves player down to its tail
  6. Landing on a ladder bottom moves player up to its top
  7. First player to reach or exceed the last cell wins
  8. Player must land exactly on the last cell to win (optional strict mode)

DESIGN DECISIONS:
  - Board owns all snake/ladder mappings (single source of truth)
  - Dice is a separate class (can be swapped for loaded dice, multiple dice, etc.)
  - Game orchestrates turns, Board resolves final positions
  - Players are stored in a queue for easy turn rotation

CLASSES:
  Player   - name, current position
  Dice     - roll(), configurable face count
  Board    - size, snakes, ladders, position resolution
  Game     - turn management, win detection, game loop

================================================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// PLAYER
// ═══════════════════════════════════════════════════════════════════════════

class Player {
    string name;
    int position;

public:
    Player(const string& name) : name(name), position(0) {}

    string getName() const { return name; }
    int getPosition() const { return position; }
    void setPosition(int pos) { position = pos; }
};

// ═══════════════════════════════════════════════════════════════════════════
// DICE
// ═══════════════════════════════════════════════════════════════════════════

class Dice {
    int faces;

public:
    Dice(int faces = 6) : faces(faces) {
        srand(time(nullptr));
    }

    int roll() const {
        return rand() % faces + 1;
    }

    int getFaces() const { return faces; }
};

// ═══════════════════════════════════════════════════════════════════════════
// BOARD
// ═══════════════════════════════════════════════════════════════════════════

class Board {
    int size;
    unordered_map<int, int> snakes;  // head -> tail (moves down)
    unordered_map<int, int> ladders; // bottom -> top (moves up)

public:
    Board(int size = 100) : size(size) {}

    int getSize() const { return size; }

    void addSnake(int head, int tail) {
        if (head <= tail) {
            cout << "Invalid snake: head must be above tail.\n";
            return;
        }
        snakes[head] = tail;
    }

    void addLadder(int bottom, int top) {
        if (bottom >= top) {
            cout << "Invalid ladder: bottom must be below top.\n";
            return;
        }
        ladders[bottom] = top;
    }

    // Resolve final position after landing (apply snake or ladder)
    int resolvePosition(int position) const {
        if (snakes.count(position)) {
            cout << "  Oops! Snake at " << position
                 << " -> slides down to " << snakes.at(position) << "\n";
            return snakes.at(position);
        }
        if (ladders.count(position)) {
            cout << "  Lucky! Ladder at " << position
                 << " -> climbs up to " << ladders.at(position) << "\n";
            return ladders.at(position);
        }
        return position;
    }

    bool isWinningPosition(int position) const {
        return position == size;
    }

    // If strict mode: can't overshoot the last cell
    bool isValidMove(int currentPos, int diceValue) const {
        return (currentPos + diceValue) <= size;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// GAME CONTROLLER
// ═══════════════════════════════════════════════════════════════════════════

class SnakeLadderGame {
    Board board;
    Dice dice;
    queue<Player*> playerQueue;
    vector<Player> players;
    bool strictMode; // If true, must land exactly on last cell

public:
    SnakeLadderGame(int boardSize = 100, bool strict = true)
        : board(boardSize), strictMode(strict) {}

    void addSnake(int head, int tail) { board.addSnake(head, tail); }
    void addLadder(int bottom, int top) { board.addLadder(bottom, top); }

    void addPlayer(const string& name) {
        players.emplace_back(name);
    }

    void play() {
        if (players.size() < 2) {
            cout << "Need at least 2 players!\n";
            return;
        }

        // Initialize player queue
        for (auto& p : players) {
            playerQueue.push(&p);
        }

        cout << "\n===== SNAKE AND LADDER =====\n";
        cout << "Board size: " << board.getSize() << "\n\n";

        while (true) {
            Player* current = playerQueue.front();
            playerQueue.pop();

            bool extraTurn = false;

            int rolled = dice.roll();
            cout << current->getName() << " (at " << current->getPosition()
                 << ") rolls " << rolled;

            if (rolled == dice.getFaces()) {
                cout << " (bonus turn!)";
                extraTurn = true;
            }
            cout << "\n";

            int newPos = current->getPosition() + rolled;

            if (strictMode && !board.isValidMove(current->getPosition(), rolled)) {
                cout << "  Can't move — would overshoot. Stay at "
                     << current->getPosition() << "\n\n";
                playerQueue.push(current);
                continue;
            }

            newPos = board.resolvePosition(newPos);
            current->setPosition(newPos);
            cout << "  -> Now at position " << newPos << "\n\n";

            if (board.isWinningPosition(newPos)) {
                cout << current->getName() << " wins the game!\n";
                break;
            }

            // If rolled max (6), player gets another turn
            if (extraTurn) {
                playerQueue.push(current); // Re-add to front? No — push to front
                // For simplicity, we push to back but they go next naturally
                // since we process immediately. Let's use a different approach:
                // Just push to front of queue by re-inserting at back and continuing.
                // Actually, let's just push them back to front:
                queue<Player*> temp;
                temp.push(current);
                while (!playerQueue.empty()) {
                    temp.push(playerQueue.front());
                    playerQueue.pop();
                }
                playerQueue = temp;
            } else {
                playerQueue.push(current);
            }
        }
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    SnakeLadderGame game(100, true);

    // Add snakes (head -> tail)
    game.addSnake(97, 79);
    game.addSnake(92, 41);
    game.addSnake(74, 52);
    game.addSnake(62, 35);
    game.addSnake(42, 30);
    game.addSnake(33, 13);
    game.addSnake(24, 5);

    // Add ladders (bottom -> top)
    game.addLadder(3, 15);
    game.addLadder(7, 22);
    game.addLadder(20, 41);
    game.addLadder(37, 67);
    game.addLadder(50, 70);
    game.addLadder(71, 90);
    game.addLadder(79, 99);

    // Add players
    game.addPlayer("Alice");
    game.addPlayer("Bob");

    // Play the game
    game.play();

    return 0;
}

/*
================================================================================
                         DESIGN NOTES
================================================================================

TURN MANAGEMENT:
  - Players are stored in a queue for natural round-robin turns
  - On rolling a 6, the player is re-inserted at the front for a bonus turn

EXTENSIBILITY:
  - Multiple dice: change Dice to roll multiple and sum
  - Loaded dice: subclass Dice with weighted probabilities
  - Custom board: read snake/ladder positions from file/config
  - Add visuals: print the board with player positions

KEY OOP PRINCIPLES USED:
  - Single Responsibility: Board resolves positions, Game manages flow
  - Open/Closed: New features (power-ups, obstacles) via new classes
  - Encapsulation: Player position only modified through setPosition()

================================================================================
*/
