#include <iostream>

using namespace std;

char board[3][3];
char current_marker;
int current_player;

void resetBoard() {
    int num = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '0' + num;
            num++;
        }
    }
}

void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return true;
    }
    return false;
}

int winner() {
    // Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return current_player;
        }
    }
    // Columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return current_player;
        }
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return current_player;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return current_player;
    }
    return 0;
}

void swapPlayerAndMarker() {
    if (current_marker == 'X') {
        current_marker = 'O';
    } else {
        current_marker = 'X';
    }

    current_player = (current_player == 1) ? 2 : 1;
}

void playSingleRound() {
    resetBoard();
    drawBoard();

    int player_won = 0;
    for (int i = 0; i < 9; i++) {
        cout << "It's player " << current_player << "'s turn. Enter your slot: ";
        int slot;
        cin >> slot;

        if (slot < 1 || slot > 9) {
            cout << "Invalid slot! Try again." << endl;
            i--;
            continue;
        }

        if (!placeMarker(slot)) {
            cout << "Slot already occupied! Try again." << endl;
            i--;
            continue;
        }

        drawBoard();

        player_won = winner();
        if (player_won == 1) {
            cout << "Player 1 wins this round!" << endl;
            break;
        } else if (player_won == 2) {
            cout << "Player 2 wins this round!" << endl;
            break;
        }

        swapPlayerAndMarker();
    }

    if (player_won == 0) {
        cout << "This round is a tie!" << endl;
    }
}

void game() {
    cout << "Player 1, choose your marker (X or O): ";
    char marker_p1;
    cin >> marker_p1;

    current_player = 1;
    current_marker = marker_p1;

    int player1_wins = 0;
    int player2_wins = 0;

    for (int round = 1; round <= 5; round++) {
        cout << "Round " << round << " begins!" << endl;
        playSingleRound();

        int winner_of_round = winner();
        if (winner_of_round == 1) {
            player1_wins++;
        } else if (winner_of_round == 2) {
            player2_wins++;
        }

        // Check if any player has won 3 rounds
        if (player1_wins == 3) {
            cout << "Player 1 wins the game!" << endl;
            return;
        } else if (player2_wins == 3) {
            cout << "Player 2 wins the game!" << endl;
            return;
        }
    }

    // If no player has won 3 rounds after 5 rounds, check who won more rounds
    if (player1_wins > player2_wins) {
        cout << "Player 1 wins the game!" << endl;
    } else if (player2_wins > player1_wins) {
        cout << "Player 2 wins the game!" << endl;
    } else {
        cout << "The game ends in a tie!" << endl;
    }
}

void showRules() {
    cout << "\nTic-Tac-Toe Rules:\n";
    cout << "1. The game is played on a 3x3 grid.\n";
    cout << "2. Players take turns to place their marker (X or O) in one of the slots (1-9).\n";
    cout << "3. The first player to align three of their markers horizontally, vertically, or diagonally wins.\n";
    cout << "4. If all 9 slots are filled and no player has won, the game ends in a tie.\n\n";
}

void menu() {
    int choice;
    do {
        cout << "=============================\n";
        cout << "      Tic-Tac-Toe Menu        \n";
        cout << "=============================\n";
        cout << "1. Play Tic-Tac-Toe\n";
        cout << "2. Show Rules\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                game();
                break;
            case 2:
                showRules();
                break;
            case 3:
                cout << "Thank you for playing! Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please select again.\n";
        }
    } while (choice != 3);
}

int main() {
    menu();
    return 0;
}
