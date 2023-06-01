#include <vector>
#include "ai.h"

int evaluateBoard(const std::vector<std::vector<ChessPiece>>& chessboard) {
    int score = 0;

    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            ChessPiece piece = chessboard[row][col];
            char symbol = piece.symbol;

            switch (symbol) {
                case 'P':
                    score += pawnVal;
                    score += pawnPositions[row][col];
                    break;
                case 'N':
                    score += knightVal;
                    score += knightPositions[row][col];
                    break;
                case 'B':
                    score += bishopVal;
                    score += bishopPositions[row][col];
                    break;
                case 'R':
                    score += rookVal;
                    score += rookPositions[row][col];
                    break;
                case 'Q':
                    score += queenVal;
                    score += queenPositions[row][col];
                    break;
                //need to incorporate end game check for diff point values later into game
                case 'K':
                    score += kingVal;
                    score += kingPositionsMid[row][col];
                    break;
                case 'p':
                    score -= pawnVal;
                    score -= pawnPositions[row][col];
                    break;
                case 'n':
                    score -= knightVal;
                    score -= knightPositions[row][col];
                    break;
                case 'b':
                    score -= bishopVal;
                    score -= bishopPositions[row][col];
                    break;
                case 'r':
                    score -= rookVal;
                    score -= rookPositions[row][col];
                    break;
                case 'q':
                    score -= queenVal;
                    score -= queenPositions[row][col];
                    break;
                case 'k':
                    score -= kingVal;
                    score -= kingPositionsMid[row][col];
                    break;
                default:
                    break;
            }
        }
    }
    return score;
}
