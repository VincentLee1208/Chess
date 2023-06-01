#include <iostream>
#include <vector>

#include "gamelogic.h"
#include "chesspiece.h"
#include "chesslogic.h"

void displayChessboard(std::vector<std::vector<ChessPiece>> &chessboard) {
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