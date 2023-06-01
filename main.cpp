#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "ai.h"
#include "chesspiece.h"
#include "chesslogic.h"

// Define constants for the chessboard dimensions
bool gameStart = false;
bool singlePlayer = true;

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
        int score = 0;

        while(!validMove) {
            displayChessboard();
            if(getPlayerMove(fromCol, fromRow, toCol, toRow)) {
                validMove = isValidMove(fromCol, fromRow, toCol, toRow, currentPlayer, chessboard);
            }
        }

        makeMove(fromCol, fromRow, toCol, toRow, currentPlayer, chessboard);
        score = evaluateBoard(chessboard);
        std::cout << "AI score: " << score << std::endl;
        displayChessboard();
        gameState = kingDead();
    }

    return 0;
}