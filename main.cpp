#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

// Define constants for the chessboard dimensions
const int BOARD_SIZE = 8;
bool gameStart = false;
bool singlePlayer = true;

// Define a structure to represent a chess piece
struct ChessPiece {
    char symbol;
    char player;
    std::string name;
};

// Create a 2D array to represent the chessboard
std::vector<std::vector<ChessPiece>> chessboard(BOARD_SIZE, std::vector<ChessPiece>(BOARD_SIZE));

// Initialize the chessboard with the starting positions of the pieces
void initializeChessboard() {
    // Initialize pawns for both players
    for (int col = 0; col < BOARD_SIZE; ++col) {
        chessboard[1][col] = { 'P', 'B',"Pawn" };
        chessboard[6][col] = { 'p', 'W',"Pawn" };
    }

    // Initialize remaining pieces for both players
    chessboard[0][0] = { 'R', 'B',"Rook" };
    chessboard[0][7] = { 'R', 'B',"Rook" };
    chessboard[7][0] = { 'r', 'W',"Rook" };
    chessboard[7][7] = { 'r', 'W',"Rook" };

    chessboard[0][1] = { 'N', 'B',"Knight" };
    chessboard[0][6] = { 'N', 'B',"Knight" };
    chessboard[7][1] = { 'n', 'W',"Knight" };
    chessboard[7][6] = { 'n', 'W',"Knight" };

    chessboard[0][2] = { 'B', 'B',"Bishop" };
    chessboard[0][5] = { 'B', 'B',"Bishop" };
    chessboard[7][2] = { 'b', 'W',"Bishop" };
    chessboard[7][5] = { 'b', 'W',"Bishop" };

    chessboard[0][3] = { 'Q', 'B',"Queen" };
    chessboard[0][4] = { 'K', 'B',"King" };
    chessboard[7][3] = { 'q', 'W',"Queen" };
    chessboard[7][4] = { 'k', 'W',"King" };
}

// Display the current state of the chessboard
void displayChessboard() {
    std::cout << "  ";
    for(int i = 0; i < BOARD_SIZE; i++) {
        std::cout << (char)('a' + i) << " ";
    }
    std::cout << std::endl;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if(col == 0) {
                std::cout << 8-row << " ";
            }
            if (chessboard[row][col].symbol != '\0') {
                std::cout << chessboard[row][col].symbol << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << "\n";
    }
}

bool isValidMove(char fromCol, int fromRow, char toCol, int toRow, char currentPlayer) {
    int fromColVal = fromCol - 'a';
    int toColVal = toCol - 'a';
    int fromRowVal = 8 - fromRow;
    int toRowVal = 8 - toRow;

    std::cout << fromRowVal << std::endl;
    std::cout << fromColVal << std::endl;
    std::cout << toRowVal << std::endl;
    std::cout << toColVal << std::endl;

    //Out of bounds
    if(fromColVal < 0 || fromRowVal < 0 || toColVal < 0 || toRowVal < 0 || 
    fromColVal >= BOARD_SIZE || fromRowVal >= BOARD_SIZE || toColVal >= BOARD_SIZE || toRowVal >= BOARD_SIZE) {
        std::cout << "Invalid Move. Out of Bounds.\n";
        return false;
    }

    //No piece selected
    if(chessboard[fromRowVal][fromColVal].symbol == '\0') {
        std::cout << "Invalid Move. No piece at source cell\n";
        return false;
    }

    //Moving enemy piece
    if(chessboard[fromRowVal][fromColVal].player != currentPlayer) {
        std::cout << "Invalid Move. Piece owned by other player\n";
        return false;
    }

    //Player's piece already in destination
    if(chessboard[toRowVal][toColVal].player == currentPlayer) {
        std::cout << "Invalid Move. Piece already in destination\n";
        return false;
    }

    //Inputted same destination as start
    if(toRowVal == fromRowVal && toColVal == fromColVal) {
        std::cout << "Invalid Move.\n";
        return false;
    }

    //Pawn
    if(chessboard[fromRowVal][fromColVal].name.compare("Pawn") == 0) {
        //if pawn moving in straight line
        if(fromColVal == toColVal) {
            //in starting position can move one or two blocks
            if(fromRowVal == 6) {
                if(fromRowVal - toRowVal <= 2) {
                    return true;
                } else {
                    std::cout << "Invalid Move. Pawn cannot go there\n";
                    return false;
                }
            } else {
                if(fromRowVal - toRowVal == 1) {
                    return true;
                } else {
                    std::cout << "Invalid Move. Pawn cannot go there\n";
                    return false;
                }
            }
        }

        //if pawn moving diagonal
        if(fromColVal != toColVal) {
            //if diagonally moves more than one space
            if(abs(toColVal - fromColVal) != 1 || fromRowVal - toRowVal != 1) {
                std::cout << "Invalid Move. Pawn cannot go there\n";
                return false;
            } 
            
            //capturing enemy piece
            if(chessboard[toRowVal][toColVal].symbol != '\0' && chessboard[toRowVal][toColVal].symbol != currentPlayer) {
                return true;
            //en passant
            } else if(chessboard[toRowVal+1][toColVal].name.compare("Pawn") == 0 && chessboard[toRowVal+1][toColVal].symbol != currentPlayer) {
                return true;
            } else {
                std::cout << "Invalid Move. Pawn cannot go there\n";
                return false;
            }
        }

        std::cout << "Invalid Move. Pawn cannot go there\n";
        return false;
    }

    //Rook
    if(chessboard[fromRowVal][fromColVal].name.compare("Rook") == 0) {
        if(fromRowVal != toRowVal && fromColVal != toColVal) {
            std::cout << "Invalid Move. Rook cannot go there\n";
            return false;
        }

        //Moving vertically
        if(fromColVal == toColVal) {
            //Up
            if(fromRowVal > toRowVal) {
                for(int i = fromRowVal-1; i > toRowVal; i--) {
                    //Piece in the way
                    if(chessboard[i][toColVal].symbol != '\0') {
                        return false;
                    }
                }
            }
            //Down
            if(fromRowVal < toRowVal) {
                for(int i = fromRowVal+1; i < toRowVal; i++) {
                    //Piece in the way
                    if(chessboard[i][toColVal].symbol != '\0') {
                        return false;
                    }
                }
            }
        }

        if(fromRowVal == toRowVal) {
            //Left
            if(fromColVal > toColVal) {
                for(int i = fromColVal-1; i > toColVal; i--) {
                    //Piece in the way
                    if(chessboard[toRowVal][i].symbol != '\0') {
                        return false;
                    }
                }
            }

            //Right
            if(fromColVal < toColVal) {
                for(int i = fromColVal+1; i < toColVal; i++) {
                    //Piece in the way
                    if(chessboard[toRowVal][i].symbol != '\0') {
                        return false;
                    }
                }
            }
        }

        //Ending position is empty or contains opponent piece
        if(chessboard[toRowVal][toColVal].symbol == '\0' || chessboard[toRowVal][toColVal].player != currentPlayer) {
            return true;
        }

        return false;
    }
    
    //Knight
    if(chessboard[fromRowVal][fromColVal].name.compare("Knight") == 0) {
        std::vector<std::pair<int, int>> validPos;
        if(fromRowVal - 2 >= 0) {
            if(fromColVal + 1 < BOARD_SIZE) {
                validPos.push_back(std::make_pair(fromRowVal-2, fromColVal+1));
            }
            if(fromColVal-1 >= 0) {
                validPos.push_back(std::make_pair(fromRowVal-2, fromColVal-1));
            }
        }
        if(fromRowVal - 1 >= 0) {
            if(fromColVal + 2 < BOARD_SIZE) {
                validPos.push_back(std::make_pair(fromRowVal-1, fromColVal+2));
            }
            if(fromColVal-2 >= 0) {
                validPos.push_back(std::make_pair(fromRowVal-1, fromColVal-2));
            }
        }
        if(fromRowVal + 2 < BOARD_SIZE) {
            if(fromColVal + 1 < BOARD_SIZE) {
                validPos.push_back(std::make_pair(fromRowVal+2, fromColVal+1));
            }
            if(fromColVal - 1 < BOARD_SIZE) {
                validPos.push_back(std::make_pair(fromRowVal+2, fromColVal-1));
            }
        }
        if(fromRowVal + 1 < BOARD_SIZE) {
            if(fromColVal + 2 < BOARD_SIZE) {
                validPos.push_back(std::make_pair(fromRowVal+1, fromColVal+2));
            }
            if(fromColVal-2 >= 0) {
                validPos.push_back(std::make_pair(fromRowVal+1, fromColVal-2));
            }
        }

        //possible destination spot
        if(std::find(validPos.begin(), validPos.end(), std::make_pair(toRowVal,toColVal)) != validPos.end()) {
            if(chessboard[toRowVal][toColVal].player != currentPlayer) {
                return true;
            }
        }

        return false;
    }

    //Bishop
    if(chessboard[fromRowVal][fromColVal].name.compare("Bishop") == 0) {
        int colDiff = abs(toColVal - fromColVal);
        int rowDiff = abs(toRowVal - fromRowVal);

        if(colDiff != rowDiff) {
            return false;
        }

        //Down right
        if(toColVal > fromColVal && toRowVal > fromRowVal) {
            for(int i = 1; i < colDiff; i++) {
                if(chessboard[fromRowVal + i][fromColVal + i].symbol != '\0') {
                    return false;
                }
            }
            if(chessboard[fromRowVal + rowDiff][fromColVal + colDiff].symbol == '\0' || chessboard[fromRowVal + rowDiff][fromColVal + colDiff].player != currentPlayer) {
                return true;
            } 
        } //Down left
        else if(toColVal < fromColVal && toRowVal > fromRowVal) {
            for(int i = 1; i < colDiff; i++) {
                if(chessboard[fromRowVal + i][fromColVal - i].symbol != '\0') {
                    return false;
                }
            }

            if(chessboard[fromRowVal + rowDiff][fromColVal - colDiff].symbol == '\0' || chessboard[fromRowVal + rowDiff][fromColVal - colDiff].player != currentPlayer) {
                return true;
            }
        } //Up left
        else if(toColVal < fromColVal && toRowVal < fromRowVal) {
            for(int i = 1; i < colDiff; i++) {
                if(chessboard[fromRowVal - i][fromColVal - i].symbol != '\0') {
                    return false;
                }
            }
            if(chessboard[fromRowVal - rowDiff][fromColVal - colDiff].symbol == '\0' || chessboard[fromRowVal - rowDiff][fromColVal - colDiff].player != currentPlayer) {
                return true;
            }
        } //Up right
        else if(toColVal > fromColVal && toRowVal < fromRowVal) {
            for(int i = 1; i < colDiff; i++) {
                if(chessboard[fromRowVal - i][fromColVal + i].symbol != '\0') {
                    return false;
                }
            }
            if(chessboard[fromRowVal - rowDiff][fromColVal + colDiff].symbol == '\0' || chessboard[fromRowVal - rowDiff][fromColVal + colDiff].player != currentPlayer) {
                return true;
            }
        }

        return false;
    }
}

void makeMove(char fromCol, int fromRow, char toCol, int toRow) {
    int fromColVal = fromCol - 'a';
    int toColVal = toCol - 'a';
    int fromRowVal = 8 - fromRow;
    int toRowVal = 8 - toRow;

    chessboard[toRowVal][toColVal] = chessboard[fromRowVal][fromColVal];

    chessboard[fromRowVal][fromColVal].symbol = '\0';
    chessboard[fromRowVal][fromColVal].name = "";
    chessboard[fromRowVal][fromColVal].player = '\0';
    
}


void getPlayerMove(char& fromCol, int& fromRow, char& toCol, int& toRow) {
    std::cout << "From: " << std::endl;

    std::cin >> fromCol >> fromRow;
    std::cout << "To: " << std::endl;

    std::cin >> toCol >> toRow;
}

bool displayMenu() {
    std::cout << "CHESS" << std::endl;
    std::cout << "To see instructions, enter 'HELP'" << std::endl;
    std::cout << "To start the game, press enter" << std::endl;

    std::cout << "Command: ";

    std::string command = "";
    std::cin >> command;

    if(command.compare("") == 0) {
        return true;
    }

    
    if(command.compare("HELP") == 0) {
        std::cout << "INSTRUCTIONS: \n Players can choose SinglePlayer to play against an AI bot or \n choose Multiplayer to play with a friend" << std::endl;
        std::cout << " Players will then take turns inputting moves in the format of \n (source column, source row, destination column, destination row)" << std::endl; 
        std::cout << "For example, [d2d3]/[D2D3] will cause pawn D2 to move to D3\n" << std::endl;
    } else {
        std::cout << "Unknown command, please try again" << std::endl;
    }
        
    return false;
}

/*
check if kings are still alive on the board
Returns 0 if both alive
Returns 1 if player king dead
returns 2 if other king dead
*/
int kingDead() {
    bool otherKing = false;
    bool myKing = false;
    for(int row = 0; row < BOARD_SIZE; row++) {
        for(int col = 0; col < BOARD_SIZE; col++) {
            if(chessboard[row][col].symbol == 'K') {
                myKing = true;
            }
            if(chessboard[row][col].symbol == 'k') {
                otherKing = true;
            }

            if(myKing && otherKing) {
                return 0;
            }
        }
    }

    if(!myKing) {
        return 1;
    } else {
        return 2;
    }
}
 
int main() {
    /*
    while(!gameStart) {
        gameStart = displayMenu();
    }
    */
    char currentPlayer = 'W';
    int gameState = 0;
    
    initializeChessboard();
    //displayChessboard();


    while(gameState == 0) {
        char fromCol, toCol;
        int fromRow, toRow = 9;
        bool validMove = false;

        while(!validMove) {
            displayChessboard();
            getPlayerMove(fromCol, fromRow, toCol, toRow);

            validMove = isValidMove(fromCol, fromRow, toCol, toRow, currentPlayer);
        }

        makeMove(fromCol, fromRow, toCol, toRow);
        displayChessboard();
        gameState = kingDead();
    }

    return 0;
}