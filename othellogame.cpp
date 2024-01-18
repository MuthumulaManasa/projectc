#include <iostream>
using namespace std;
const int SIZE = 8;
enum CellState { EMPTY, BLACK, WHITE };
class OthelloGame {
private:
    CellState board[SIZE][SIZE];
    CellState currentPlayer;
public:
    OthelloGame() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                board[i][j] = EMPTY;
            }
        }
        board[SIZE / 2 - 1][SIZE / 2 - 1] = WHITE;
        board[SIZE / 2][SIZE / 2] = WHITE;
        board[SIZE / 2 - 1][SIZE / 2] = BLACK;
        board[SIZE / 2][SIZE / 2 - 1] = BLACK;
        currentPlayer = BLACK;
    }
    void printBoard() const {
        cout << "  ";
        for (int i = 0; i < SIZE; ++i) {
            cout << i << " ";
        }
        cout << endl;

        for (int i = 0; i < SIZE; ++i) {
            cout << i << " ";
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == EMPTY) cout << ". ";
                else if (board[i][j] == BLACK) cout << "B ";
                else cout << "W ";
            }
            cout << endl;
        }
    }

    bool isValidMove(int row, int col) const {
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != EMPTY) {
            return false;
        }

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                if (isValidDirection(row, col, i, j)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool isValidDirection(int row, int col, int rowDir, int colDir) const {
        int opponent = (currentPlayer == BLACK) ? WHITE : BLACK;

        int r = row + rowDir;
        int c = col + colDir;

        while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == opponent) {
            r += rowDir;
            c += colDir;
        }

        return r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == currentPlayer;
    }

    void makeMove(int row, int col) {
        if (!isValidMove(row, col)) {
            cout << "Invalid move! Try again." << endl;
            return;
        }

        board[row][col] = currentPlayer;

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                flipDirection(row, col, i, j);
            }
        }


        currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
    }

    void flipDirection(int row, int col, int rowDir, int colDir) {
        int opponent = (currentPlayer == BLACK) ? WHITE : BLACK;

        int r = row + rowDir;
        int c = col + colDir;

        while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == opponent) {
            r += rowDir;
            c += colDir;
        }

        if (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == currentPlayer) {
            r = row + rowDir;
            c = col + colDir;

            while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == opponent) {
                board[r][c] = currentPlayer;
                r += rowDir;
                c += colDir;
            }
        }
    }

    bool isBoardFull() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == EMPTY) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isGameOver() const {
        return isBoardFull() || !hasValidMove();
    }

    bool hasValidMove() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (isValidMove(i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

    CellState getWinner() const {
        int blackCount = 0;
        int whiteCount = 0;

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == BLACK) blackCount++;
                else if (board[i][j] == WHITE) whiteCount++;
            }
        }

        if (blackCount > whiteCount) return BLACK;
        else if (whiteCount > blackCount) return WHITE;
        else return EMPTY;
    }

    void playGame() {
        while (!isGameOver()) {
            printBoard();
            cout << "Current player: " << ((currentPlayer == BLACK) ? "Black" : "White") << endl;

            if (currentPlayer == BLACK) {

                int row, col;
                cout << "Enter your move (row and column, separated by a space): ";
                cin >> row >> col;

                makeMove(row, col);
            } else {

                cout << "Computer is making a move..." << endl;

                int row, col;
                do {
                    row = rand() % SIZE;
                    col = rand() % SIZE;
                } while (!isValidMove(row, col));

                makeMove(row, col);
            }
        }

        printBoard();

        CellState winner = getWinner();
        if (winner == EMPTY) {
            cout << "It's a draw!" << endl;
        } else {
            cout << "Player " << ((winner == BLACK) ? "Black" : "White") << " wins!" << endl;
        }
    }
};
int main() {
    OthelloGame game;
    game.playGame();
    return 0;
    }

