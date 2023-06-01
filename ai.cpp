#include <vector>
#include <limits>
#include <iostream>

#include "ai.h"
#include "chesslogic.h"
#include "gamelogic.h"


const int MAX_DEPTH = 1;
std::pair<int, int> bestMove;

void aiTurn(const std::vector<std::vector<ChessPiece>>& chessboard, char aiPlayer) {
    std::cout << "Calculating AI Move\n";
    minimax(chessboard, MAX_DEPTH, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), true, aiPlayer);
    std::cout << "AI Move: " << bestMove.first << ", " << bestMove.second << std::endl;
}

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

int minimax(const std::vector<std::vector<ChessPiece>>& chessboard, int depth, int alpha, int beta, bool maxmizingPlayer, char player) {
    if(depth == 0) {
        return evaluateBoard(chessboard);
    }

    if(maxmizingPlayer) {
        //make maxScore the lowest possible int
        int maxScore = std::numeric_limits<int>::min();

        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                if(chessboard[row][col].player == player) {
                    std::vector<std::pair<int, int>> moves = chessboard[row][col].possibleMoves;
                    for(int i = 0; i < moves.size(); i++){
                        std::vector<std::vector<ChessPiece>> copyChessboard = chessboard;
                        std::cout << "Testing: " << row << ", " << col << " to " << moves[i].first << ", " << moves[i].second << std::endl;
                        if(player == 'W') {

                            makeMove(col, 8-row, moves[i].second, moves[i].first, player, copyChessboard);
                            
                            std::cout << "COPY\n";
                            displayChessboard(copyChessboard);
                            std::cout << "COPY\n";

                            int score = minimax(copyChessboard, depth-1, alpha, beta, false, 'B');
                            maxScore = std::max(maxScore,score);

                            if(score > maxScore) {
                                bestMove = moves[i];
                            }

                            alpha = std::max(alpha, maxScore);
                        } else {
                            makeMove(col, row, moves[i].second, moves[i].first, player, copyChessboard);

                            std::cout << "COPY\n";
                            displayChessboard(copyChessboard);
                            std::cout << "COPY\n";

                            int score = minimax(copyChessboard, depth-1, alpha, beta, false, 'W');
                            maxScore = std::max(maxScore,score);
                            if(score > maxScore) {
                                bestMove = moves[i];
                            }
                            alpha = std::max(alpha, maxScore);
                        }

                        if(beta <= alpha) {
                            break;
                        }

                    }
                }
            }
        }
        return maxScore;

    } else {
        int minScore = std::numeric_limits<int>::max();
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                if(chessboard[row][col].player == player) {
                    std::vector<std::pair<int, int>> moves = chessboard[row][col].possibleMoves;
                    for(int i = 0; i < moves.size(); i++){
                        std::vector<std::vector<ChessPiece>> copyChessboard = chessboard;
                        if(player == 'W') {
                            makeMove(col, row, moves[i].second, moves[i].first, player, copyChessboard);
                            int score = minimax(copyChessboard, depth-1, alpha, beta, true, 'B');
                            minScore = std::min(minScore,score);
                            beta = std::min(beta, minScore);
                        } else {
                            makeMove(col, row, moves[i].second, moves[i].first, player, copyChessboard);
                            int score = minimax(copyChessboard, depth-1, alpha, beta, true, 'W');
                            minScore = std::min(minScore,score);
                            beta = std::min(beta, minScore);
                        }

                        if(beta <= alpha) {
                            break;
                        }

                    }
                }
            }
        }
        return minScore;
    }
}
