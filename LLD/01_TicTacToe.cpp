/*
================================================================================
                    LOW-LEVEL DESIGN: TIC TAC TOE
================================================================================

PROBLEM:
  Design a TicTacToe game for two players on an NxN board.
  A player wins by completing an entire row, column, or diagonal.

REQUIREMENTS:
  1. Support NxN board (default 3x3)
  2. Two players alternate turns (X and O)
  3. Validate moves (bounds, already occupied)
  4. Detect win in O(1) per move using row/col/diagonal sums
  5. Detect draw when board is full

DESIGN DECISIONS:
  - O(1) win check: Track sum per row, col, and both diagonals.
    Player X adds +1, Player O adds -1. If any sum reaches +N or -N, that
    player wins.
  - Single Responsibility: Board handles grid state, Game handles flow.
  - Extensible to NxN without changing win-check logic.

CLASSES:
  Player      - name, symbol (X/O)
  Board       - grid state, move placement, O(1) win detection
  TicTacToe   - game controller, turn management, input loop

================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;


enum class CellState { EMPTY, X, O };
enum class GameStatus { IN_PROGRESS, X_WINS, O_WINS, DRAW };


class Player {
    string name;
    CellState symbol;

public:
    Player(const string& name, CellState symbol) : name(name), symbol(symbol) {}

    string getName() const { return name; }
    CellState getSymbol() const { return symbol; }
};


class Board {
    int n;
    vector<vector<CellState>> grid;

    // O(1) win detection: track sums per row, col, and diagonals
    // X contributes +1, O contributes -1
    vector<int> rowSum, colSum;
    int diagSum, antiDiagSum;
    int moveCount;

public:
    Board(int size) : n(size), grid(size, vector<CellState>(size, CellState::EMPTY)),
                      rowSum(size, 0), colSum(size, 0),
                      diagSum(0), antiDiagSum(0), moveCount(0) {}

    int getSize() const { return n; }
    bool isFull() const { return moveCount == n * n; }

    bool isValidMove(int row, int col) const {
        if (row < 0 || row >= n || col < 0 || col >= n) return false;
        return grid[row][col] == CellState::EMPTY;
    }

    // Place a move and return true if this move wins the game
    bool makeMove(int row, int col, CellState symbol) {
        grid[row][col] = symbol;
        moveCount++;

        int delta = (symbol == CellState::X) ? 1 : -1;

        rowSum[row] += delta;
        colSum[col] += delta;
        if (row == col) diagSum += delta;
        if (row + col == n - 1) antiDiagSum += delta;

        // Check if any line reaches +N or -N
        return (abs(rowSum[row]) == n ||
                abs(colSum[col]) == n ||
                abs(diagSum) == n ||
                abs(antiDiagSum) == n);
    }

    void print() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char ch = '-';
                if (grid[i][j] == CellState::X) ch = 'X';
                if (grid[i][j] == CellState::O) ch = 'O';
                cout << " " << ch << " ";
                if (j < n - 1) cout << "|";
            }
            cout << "\n";
            if (i < n - 1) {
                for (int j = 0; j < n; j++) {
                    cout << "---";
                    if (j < n - 1) cout << "+";
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// TIC TAC TOE - GAME CONTROLLER
// ═══════════════════════════════════════════════════════════════════════════

class TicTacToe {
    Board board;
    Player player1, player2;
    GameStatus status;
    int currentTurn; // 0 = player1, 1 = player2

    Player& getCurrentPlayer() {
        return (currentTurn == 0) ? player1 : player2;
    }

public:
    TicTacToe(int boardSize = 3)
        : board(boardSize),
          player1("Player 1", CellState::X),
          player2("Player 2", CellState::O),
          status(GameStatus::IN_PROGRESS),
          currentTurn(0) {}

    TicTacToe(const string& name1, const string& name2, int boardSize = 3)
        : board(boardSize),
          player1(name1, CellState::X),
          player2(name2, CellState::O),
          status(GameStatus::IN_PROGRESS),
          currentTurn(0) {}

    GameStatus getStatus() const { return status; }

    // Returns true if the game is still in progress
    bool playMove(int row, int col) {
        if (status != GameStatus::IN_PROGRESS) {
            cout << "Game is already over!\n";
            return false;
        }

        if (!board.isValidMove(row, col)) {
            cout << "Invalid move! Try again.\n";
            return true; // Game continues, player retries
        }

        Player& player = getCurrentPlayer();
        bool won = board.makeMove(row, col, player.getSymbol());

        board.print();

        if (won) {
            status = (player.getSymbol() == CellState::X)
                     ? GameStatus::X_WINS : GameStatus::O_WINS;
            cout << player.getName() << " wins!\n";
            return false;
        }

        if (board.isFull()) {
            status = GameStatus::DRAW;
            cout << "It's a draw!\n";
            return false;
        }

        // Switch turn
        currentTurn = 1 - currentTurn;
        return true;
    }

    void play() {
        cout << "\n===== TIC TAC TOE =====\n\n";
        board.print();

        while (status == GameStatus::IN_PROGRESS) {
            Player& player = getCurrentPlayer();
            cout << player.getName() << " ("
                 << (player.getSymbol() == CellState::X ? "X" : "O")
                 << "), enter row and col (0-indexed): ";

            int row, col;
            cin >> row >> col;
            playMove(row, col);
        }
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Demo: Interactive game
    TicTacToe game("Alice", "Bob");
    game.play();

    return 0;
}

/*
================================================================================
                         DESIGN NOTES
================================================================================

O(1) WIN CHECK EXPLAINED:
  - Maintain rowSum[i], colSum[j], diagSum, antiDiagSum
  - X adds +1, O adds -1
  - If any sum reaches +N → X wins
  - If any sum reaches -N → O wins
  - No need to scan the board after each move

EXTENSIBILITY:
  - Change board size via constructor: TicTacToe game("A", "B", 5) for 5x5
  - Add AI player by subclassing Player with a strategy
  - Add undo by maintaining a move stack

RELATED PROBLEMS:
  - LeetCode 348: Design Tic-Tac-Toe
  - LeetCode 794: Valid Tic-Tac-Toe State

================================================================================
*/
