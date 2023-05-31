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
    std::vector<std::pair<int,int>> possibleMoves;
};

// Create a 2D array to represent the chessboard
std::vector<std::vector<ChessPiece>> chessboard(BOARD_SIZE, std::vector<ChessPiece>(BOARD_SIZE));

// Initialize the chessboard with the starting positions of the pieces
void initializeChessboard() {
    // Initialize pawns for both players
    std::vector<std::pair<int,int>> tempMoves;
    for (int col = 0; col < BOARD_SIZE; ++col) {
        tempMoves.push_back(std::make_pair(2, col));
        tempMoves.push_back(std::make_pair(3, col));
        chessboard[1][col] = { 'P', 'B',"Pawn", tempMoves};

        tempMoves.clear();
        tempMoves.push_back(std::make_pair(5, col));
        tempMoves.push_back(std::make_pair(4, col));
        chessboard[6][col] = { 'p', 'W',"Pawn", tempMoves };
    }

    tempMoves.clear();

    // Initialize remaining pieces for both players
    chessboard[0][0] = { 'R', 'B',"Rook", tempMoves};
    chessboard[0][7] = { 'R', 'B',"Rook",  tempMoves};
    chessboard[7][0] = { 'r', 'W',"Rook", tempMoves};
    chessboard[7][7] = { 'r', 'W',"Rook", tempMoves};

    tempMoves.push_back(std::make_pair(2,0));
    tempMoves.push_back(std::make_pair(2,2));

    chessboard[0][1] = { 'N', 'B',"Knight", tempMoves };

    tempMoves.clear();

    tempMoves.push_back(std::make_pair(2,5));
    tempMoves.push_back(std::make_pair(2,7));
    chessboard[0][6] = { 'N', 'B',"Knight", tempMoves };

    tempMoves.clear();
    tempMoves.push_back(std::make_pair(5,0));
    tempMoves.push_back(std::make_pair(5,2));
    chessboard[7][1] = { 'n', 'W',"Knight", tempMoves};

    tempMoves.clear();
    tempMoves.push_back(std::make_pair(5,5));
    tempMoves.push_back(std::make_pair(5,7));
    chessboard[7][6] = { 'n', 'W',"Knight", tempMoves };

    tempMoves.clear();

    chessboard[0][2] = { 'B', 'B',"Bishop", tempMoves };
    chessboard[0][5] = { 'B', 'B',"Bishop", tempMoves };
    chessboard[7][2] = { 'b', 'W',"Bishop", tempMoves };
    chessboard[7][5] = { 'b', 'W',"Bishop", tempMoves };

    chessboard[0][3] = { 'Q', 'B',"Queen", tempMoves };
    chessboard[0][4] = { 'K', 'B',"King", tempMoves };
    chessboard[7][3] = { 'q', 'W',"Queen", tempMoves };
    chessboard[7][4] = { 'k', 'W',"King", tempMoves };
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
                std::cout << 8-row << "|";
            }
            if (chessboard[row][col].symbol != '\0') {
                std::cout << chessboard[row][col].symbol << "|";
            } else {
                std::cout << "-|";
            }
        }

        std::cout << "\n";
    }
    
    std::cout << "\n";
}

std::vector<std::pair<int,int>> pawnMoves(int toColVal, int toRowVal, char currentPlayer) {
    std::vector<std::pair<int, int>> newMoves;
    if(chessboard[toRowVal][toColVal].player == currentPlayer) {
        if(toRowVal == 6) {
            if(chessboard[toRowVal-2][toColVal].symbol == '\0') {
                newMoves.push_back(std::make_pair(toRowVal-2, toColVal));
            }
        }
        //Can still move up
        if(toRowVal-1 >= 0) {
            //Move Straight
            if(chessboard[toRowVal-1][toColVal].symbol == '\0') {
                newMoves.push_back(std::make_pair(toRowVal-1, toColVal));
            }

            //Move Left Diagonal
            if(toColVal-1 >= 0) {
                if(chessboard[toRowVal-1][toColVal-1].symbol != '\0'  && chessboard[toRowVal-1][toColVal-1].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal-1, toColVal-1));
                } else if(chessboard[toRowVal][toColVal-1].symbol != '\0'  && chessboard[toRowVal][toColVal-1].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal-1, toColVal-1));
                }
            }

            //Move Right Diagonal
            if(toColVal+1 < BOARD_SIZE) {
                if(chessboard[toRowVal-1][toColVal+1].symbol != '\0'  && chessboard[toRowVal-1][toColVal+1].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal-1, toColVal+1));
                } else if(chessboard[toRowVal][toColVal+1].symbol != '\0'  && chessboard[toRowVal][toColVal+1].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal-1, toColVal+1));
                }
            }
        }
        return newMoves;
    } else {
        if(toRowVal == 1) {
            if(chessboard[toRowVal+2][toColVal].symbol == '\0') {
                newMoves.push_back(std::make_pair(toRowVal+2, toColVal));
            }
        }
        //Can still move up
        if(toRowVal+1 < BOARD_SIZE) {
            //Move Straight
            if(chessboard[toRowVal+1][toColVal].symbol == '\0') {
                newMoves.push_back(std::make_pair(toRowVal+1, toColVal));
            }

            //Move Left Diagonal
            if(toColVal-1 >= 0) {
                if(chessboard[toRowVal+1][toColVal-1].symbol != '\0'  && chessboard[toRowVal+1][toColVal-1].player == currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+1, toColVal-1));
                } else if(chessboard[toRowVal][toColVal-1].symbol != '\0'  && chessboard[toRowVal][toColVal-1].player == currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+1, toColVal-1));
                }
            }

            //Move Right Diagonal
            if(toColVal+1 < BOARD_SIZE) {
                if(chessboard[toRowVal+1][toColVal+1].symbol != '\0'  && chessboard[toRowVal+1][toColVal+1].player == currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+1, toColVal+1));
                } else if(chessboard[toRowVal][toColVal+1].symbol != '\0'  && chessboard[toRowVal][toColVal+1].player == currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+1, toColVal+1));
                }
            }
        }
        return newMoves;
    }
}

std::vector<std::pair<int,int>> rookMoves(int toColVal, int toRowVal, char currentPlayer) {
    std::vector<std::pair<int, int>> newMoves;
    for(int i = toRowVal-1; i >= 0; i--) {
        if(chessboard[i][toColVal].symbol == '\0') {
            newMoves.push_back(std::make_pair(i,toColVal));
        } else if(chessboard[i][toColVal].symbol != '\0' && chessboard[i][toColVal].player != currentPlayer) {
            newMoves.push_back(std::make_pair(i, toColVal));
            break;
        } else {
            break;
        }
    }

    for(int i = toRowVal+1; i < BOARD_SIZE; i++) {
        if(chessboard[i][toColVal].symbol == '\0') {
            newMoves.push_back(std::make_pair(i,toColVal));
        } else if(chessboard[i][toColVal].symbol != '\0' && chessboard[i][toColVal].player != currentPlayer) {
            newMoves.push_back(std::make_pair(i, toColVal));
            break;
        } else {
            break;
        }
    }

    for(int j = toColVal-1; j >= 0; j--) {
        if(chessboard[toRowVal][j].symbol == '\0') {
            newMoves.push_back(std::make_pair(toRowVal,j));
        } else if(chessboard[toRowVal][j].symbol != '\0' && chessboard[toRowVal][j].player != currentPlayer) {
            newMoves.push_back(std::make_pair(toRowVal, j));
            break;
        } else {
            break;
        }
    }

    for(int j = toColVal+1; j < BOARD_SIZE; j++) {
        if(chessboard[toRowVal][j].symbol == '\0') {
            newMoves.push_back(std::make_pair(toRowVal,j));
        } else if(chessboard[toRowVal][j].symbol != '\0' && chessboard[toRowVal][j].player != currentPlayer) {
            newMoves.push_back(std::make_pair(toRowVal, j));
            break;
        } else {
            break;
        }
    }

    return newMoves;
}

std::vector<std::pair<int,int>> knightMoves(int toColVal, int toRowVal, char currentPlayer) {
    std::vector<std::pair<int, int>> newMoves;
    if(toRowVal - 1 >= 0) {
        if(toColVal + 2 < BOARD_SIZE && (chessboard[toRowVal-1][toColVal+2].symbol == '\0' || chessboard[toRowVal-1][toColVal+2].player != currentPlayer)) {
            newMoves.push_back(std::make_pair(toRowVal-1, toColVal+2));
        }
        if(toColVal - 2 >= 0 && (chessboard[toRowVal-1][toColVal-2].symbol == '\0' || chessboard[toRowVal-1][toColVal-2].player != currentPlayer)) {
            newMoves.push_back(std::make_pair(toRowVal-1, toColVal-2));
        }
        if(toRowVal - 2 >= 0) {
            if(toColVal + 1 < BOARD_SIZE && (chessboard[toRowVal-2][toColVal+1].symbol == '\0' || chessboard[toRowVal-2][toColVal+1].player != currentPlayer)) {
                newMoves.push_back(std::make_pair(toRowVal-2, toColVal+1));
            }
            if(toColVal - 1 >= 0 && (chessboard[toRowVal-2][toColVal-1].symbol == '\0' || chessboard[toRowVal-2][toColVal-1].player != currentPlayer)) {
                newMoves.push_back(std::make_pair(toRowVal-2, toColVal-1));
            }
        }
    }

    if(toRowVal + 1 < BOARD_SIZE) {
        if(toColVal + 2 < BOARD_SIZE && (chessboard[toRowVal+1][toColVal+2].symbol == '\0' || chessboard[toRowVal+1][toColVal+2].player != currentPlayer)) {
            newMoves.push_back(std::make_pair(toRowVal+1, toColVal+2));
        }
        if(toColVal - 2 >= 0 && (chessboard[toRowVal+1][toColVal-2].symbol == '\0' || chessboard[toRowVal+1][toColVal-2].player != currentPlayer)) {
            newMoves.push_back(std::make_pair(toRowVal+1, toColVal-2));
        }
        if(toRowVal + 2 < BOARD_SIZE) {
            if(toColVal + 1 < BOARD_SIZE && (chessboard[toRowVal+2][toColVal+1].symbol == '\0' || chessboard[toRowVal+2][toColVal+1].player != currentPlayer)) {
                newMoves.push_back(std::make_pair(toRowVal+2, toColVal+1));
            }
            if(toColVal - 1 >= 0 && (chessboard[toRowVal+2][toColVal-1].symbol == '\0' || chessboard[toRowVal+2][toColVal-1].player != currentPlayer)) {
                newMoves.push_back(std::make_pair(toRowVal+2, toColVal-1));
            }
        }
    }

    return newMoves;
}

std::vector<std::pair<int,int>> bishopMoves(int toColVal, int toRowVal, char currentPlayer) {
    std::vector<std::pair<int, int>> newMoves;
    bool tleft = true;
    bool tright = true;
    bool bleft = true;
    bool bright = true;

    for(int i = 1; i < BOARD_SIZE; i++) {
        if(tleft) {
            if(toRowVal - i >= 0 && toColVal - i >= 0) {
                if(chessboard[toRowVal-i][toColVal-i].symbol == '\0') {
                    newMoves.push_back(std::make_pair(toRowVal-i,toColVal-i));
                } else if(chessboard[toRowVal-i][toColVal-i].symbol != '\0' && chessboard[toRowVal-i][toColVal-i].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal-i,toColVal-i));
                    tleft = false;
                } else {
                    tleft = false;
                }
            }
        }
        if(tright) {
            if(toRowVal - i >= 0 && toColVal + i < BOARD_SIZE) {
                if(chessboard[toRowVal-i][toColVal+i].symbol == '\0') {
                    newMoves.push_back(std::make_pair(toRowVal-i,toColVal+i));
                } else if(chessboard[toRowVal-i][toColVal+i].symbol != '\0' && chessboard[toRowVal-i][toColVal+i].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal-i,toColVal+i));
                    tright = false;
                } else {
                    tright = false;
                }
            }
        }
        if(bright) {
            if(toRowVal + i < BOARD_SIZE && toColVal + i < BOARD_SIZE) {
                if(chessboard[toRowVal+i][toColVal+i].symbol == '\0') {
                    newMoves.push_back(std::make_pair(toRowVal+i,toColVal+i));
                } else if(chessboard[toRowVal+i][toColVal+i].symbol != '\0' && chessboard[toRowVal+i][toColVal+i].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+i,toColVal+i));
                    bright = false;
                } else {
                    bright = false;
                }
            }
        }
        if(bleft) {
            if(toRowVal + i < BOARD_SIZE && toColVal - i >= 0) {
                if(chessboard[toRowVal+i][toColVal-i].symbol == '\0') {
                    newMoves.push_back(std::make_pair(toRowVal+i,toColVal-i));
                } else if(chessboard[toRowVal+i][toColVal-i].symbol != '\0' && chessboard[toRowVal+i][toColVal-i].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+i,toColVal-i));
                    bleft = false;
                } else {
                    bleft = false;
                }
            }
        }
    }

    return newMoves;
}

std::vector<std::pair<int, int>> kingMoves(int toColVal, int toRowVal, char currentPlayer) {
    std::vector<std::pair<int, int>> newMoves;
    if(toRowVal - 1 >= 0) {
        if(chessboard[toRowVal-1][toColVal].symbol == '\0' || chessboard[toRowVal-1][toColVal].player != currentPlayer) {
            newMoves.push_back(std::make_pair(toRowVal-1, toColVal));
        }
        if(toColVal - 1 >= 0) {
            if(chessboard[toRowVal-1][toColVal-1].symbol == '\0' || chessboard[toRowVal-1][toColVal-1].player != currentPlayer) {
                newMoves.push_back(std::make_pair(toRowVal-1, toColVal-1));
            }
        }
        if(toColVal + 1 < BOARD_SIZE) {
            if(chessboard[toRowVal-1][toColVal+1].symbol == '\0' || chessboard[toRowVal-1][toColVal+1].player != currentPlayer) {
                newMoves.push_back(std::make_pair(toRowVal-1, toColVal+1));
            }
        }
    }
    if(toColVal - 1 >= 0) {
        if(chessboard[toRowVal][toColVal-1].symbol == '\0' || chessboard[toRowVal][toColVal-1].player != currentPlayer) {
            newMoves.push_back(std::make_pair(toRowVal, toColVal-1));
        }
    }
    if(toColVal + 1 < BOARD_SIZE) {
        if(chessboard[toRowVal][toColVal+1].symbol == '\0' || chessboard[toRowVal][toColVal+1].player != currentPlayer) {
            newMoves.push_back(std::make_pair(toRowVal, toColVal+1));
        }
    }
    if(toRowVal + 1 < BOARD_SIZE) {
        if(chessboard[toRowVal+1][toColVal].symbol == '\0' || chessboard[toRowVal+1][toColVal].player != currentPlayer) {
            newMoves.push_back(std::make_pair(toRowVal+1, toColVal));
        }
        if(toColVal - 1 >= 0) {
            if(chessboard[toRowVal+1][toColVal-1].symbol == '\0' || chessboard[toRowVal+1][toColVal-1].player != currentPlayer) {
                newMoves.push_back(std::make_pair(toRowVal+1, toColVal-1));
            }
        }
        if(toColVal + 1 < BOARD_SIZE) {
            if(chessboard[toRowVal+1][toColVal+1].symbol == '\0' || chessboard[toRowVal+1][toColVal+1].player != currentPlayer) {
                newMoves.push_back(std::make_pair(toRowVal+1, toColVal+1));
            }
        }
    }

    return newMoves;
}

std::vector<std::pair<int,int>> updateMoves(int ColVal, int RowVal,char currentPlayer) {
    
    std::vector<std::pair<int, int>> newMoves;
    //Pawn
    if(chessboard[RowVal][ColVal].name.compare("Pawn") == 0 ) {
        return pawnMoves(ColVal, RowVal, currentPlayer);
    } 

    //Rook
    if(chessboard[RowVal][ColVal].name.compare("Rook") == 0) {
        return rookMoves(ColVal, RowVal, currentPlayer);
    }

    
    //Knight
    if(chessboard[RowVal][ColVal].name.compare("Knight") == 0) {
        return knightMoves(ColVal, RowVal, currentPlayer);
    }
    
    
    //Bishop
    if(chessboard[RowVal][ColVal].name.compare("Bishop") == 0) {
        return bishopMoves(ColVal, RowVal, currentPlayer);
    }

    //Queen
    if(chessboard[RowVal][ColVal].name.compare("Queen") == 0) {
        std::vector<std::pair<int,int>> bMoves = bishopMoves(ColVal, RowVal, currentPlayer);
        std::vector<std::pair<int,int>> rMoves = rookMoves(ColVal, RowVal, currentPlayer);

        if(bMoves.size() >= rMoves.size()) {
            bMoves.insert(bMoves.end(), rMoves.begin(), rMoves.end());
            return bMoves;
        } else {
            rMoves.insert(rMoves.end(), bMoves.begin(), bMoves.end());
            return rMoves;
        }
    }

    //King
    if(chessboard[RowVal][ColVal].name.compare("King") == 0) {
        return kingMoves(ColVal, RowVal, currentPlayer);
    }

    return chessboard[RowVal][ColVal].possibleMoves;

    

}

bool validateMove(int fromColVal, int fromRowVal, int toColVal, int toRowVal, char currentPlayer) {
    if(std::find(chessboard[fromRowVal][fromColVal].possibleMoves.begin(), chessboard[fromRowVal][fromColVal].possibleMoves.end(), std::make_pair(toRowVal,toColVal)) != chessboard[fromRowVal][fromColVal].possibleMoves.end()) {
        std::cout << "valid Move" << std::endl;
        return true;
    } else {
        return false;
    }
}

bool isValidMove(char fromCol, int fromRow, char toCol, int toRow, char currentPlayer) {
    int fromColVal = fromCol - 'a';
    int toColVal = toCol - 'a';
    int fromRowVal = 8 - fromRow;
    int toRowVal = 8 - toRow;

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

    return validateMove(fromColVal, fromRowVal, toColVal, toRowVal, currentPlayer);
}


void makeMove(char fromCol, int fromRow, char toCol, int toRow, char currentPlayer) {
    int fromColVal = fromCol - 'a';
    int toColVal = toCol - 'a';
    int fromRowVal = 8 - fromRow;
    int toRowVal = 8 - toRow;

    std::cout << "BEFORE" << std::endl;
    for(int i = 0; i < chessboard[fromRowVal][fromColVal].possibleMoves.size(); i++) {
        std::cout << chessboard[fromRowVal][fromColVal].possibleMoves[i].first << ", " << chessboard[fromRowVal][fromColVal].possibleMoves[i].second << std::endl;
    }

    chessboard[toRowVal][toColVal] = chessboard[fromRowVal][fromColVal];
    chessboard[fromRowVal][fromColVal].symbol = '\0';
    chessboard[fromRowVal][fromColVal].name = "";
    chessboard[fromRowVal][fromColVal].player = '\0';

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            chessboard[i][j].possibleMoves = updateMoves(j,i, currentPlayer);
        }
    }

    std::cout << "AFTER" << std::endl;
    for(int i = 0; i < chessboard[toRowVal][toColVal].possibleMoves.size(); i++) {
        std::cout << chessboard[toRowVal][toColVal].possibleMoves[i].first << ", " << chessboard[toRowVal][toColVal].possibleMoves[i].second << std::endl;
    }
}


bool getPlayerMove(char& fromCol, int& fromRow, char& toCol, int& toRow) {
    std::string from = "";
    std::string to = "";

    std::cout << "From: " << std::endl;
    std::cin >> from;

    std::cout << "To: " << std::endl;
    std::cin >> to;

    if(from.length() != 2 || to.length() != 2) {
        std::cout << "Invalid input. Try again" << std::endl; 
        return false;
    } else {
        fromCol = from.at(0);
        fromRow = from.at(1) - '0';
        toCol = to.at(0);
        toRow = to.at(1) - '0';
        return true;
    }

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
            if(getPlayerMove(fromCol, fromRow, toCol, toRow)) {
                validMove = isValidMove(fromCol, fromRow, toCol, toRow, currentPlayer);
            }
        }

        makeMove(fromCol, fromRow, toCol, toRow, currentPlayer);
        displayChessboard();
        gameState = kingDead();
    }

    return 0;
}