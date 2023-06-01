#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "ai.h"
#include "chesspiece.h"
#include "chesslogic.h"
#include "gamelogic.h"

bool validateMove(int fromColVal, int fromRowVal, int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard) {
    if(std::find(chessboard[fromRowVal][fromColVal].possibleMoves.begin(), chessboard[fromRowVal][fromColVal].possibleMoves.end(), std::make_pair(toRowVal,toColVal)) != chessboard[fromRowVal][fromColVal].possibleMoves.end()) {
        std::cout << "valid Move" << std::endl;
        return true;
    } else {
        return false;
    }
}

bool isValidMove(char fromCol, int fromRow, char toCol, int toRow, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard) {
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

    return validateMove(fromColVal, fromRowVal, toColVal, toRowVal, currentPlayer, chessboard);
}

void makeMove(int fromColVal, int fromRowVal, int toColVal, int toRowVal, char currentPlayer , std::vector<std::vector<ChessPiece>> &chessboard) {

    /*
    std::cout << "BEFORE" << std::endl;
    for(int i = 0; i < chessboard[fromRowVal][fromColVal].possibleMoves.size(); i++) {
        std::cout << chessboard[fromRowVal][fromColVal].possibleMoves[i].first << ", " << chessboard[fromRowVal][fromColVal].possibleMoves[i].second << std::endl;
    }
    */
    

    chessboard[toRowVal][toColVal] = chessboard[fromRowVal][fromColVal];
    chessboard[fromRowVal][fromColVal].symbol = '\0';
    chessboard[fromRowVal][fromColVal].name = "";
    chessboard[fromRowVal][fromColVal].player = '\0';

    //std::cout << "Board updated" << std::endl;

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            chessboard[i][j].possibleMoves = updateMoves(j,i, chessboard[i][j].player, chessboard);
        }
    }

    /*
    std::cout << "AFTER" << std::endl;
    for(int i = 0; i < chessboard[toRowVal][toColVal].possibleMoves.size(); i++) {
        std::cout << chessboard[toRowVal][toColVal].possibleMoves[i].first << ", " << chessboard[toRowVal][toColVal].possibleMoves[i].second << std::endl;
    }
    */
}

std::vector<std::pair<int,int>> pawnMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard) {
    std::vector<std::pair<int, int>> newMoves;
    if(currentPlayer == 'W') {
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
        //std::cout << toRowVal << ", " << toColVal << ": " << newMoves.size() << std::endl;
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
                if(chessboard[toRowVal+1][toColVal-1].symbol != '\0'  && chessboard[toRowVal+1][toColVal-1].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+1, toColVal-1));
                } else if(chessboard[toRowVal][toColVal-1].symbol != '\0'  && chessboard[toRowVal][toColVal-1].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+1, toColVal-1));
                }
            }

            //Move Right Diagonal
            if(toColVal+1 < BOARD_SIZE) {
                if(chessboard[toRowVal+1][toColVal+1].symbol != '\0'  && chessboard[toRowVal+1][toColVal+1].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+1, toColVal+1));
                } else if(chessboard[toRowVal][toColVal+1].symbol != '\0'  && chessboard[toRowVal][toColVal+1].player != currentPlayer) {
                    newMoves.push_back(std::make_pair(toRowVal+1, toColVal+1));
                }
            }
        }
        //std::cout << toRowVal << ", " << toColVal << ": " << newMoves.size() << std::endl;
        return newMoves;
    }
}

std::vector<std::pair<int,int>> rookMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard) {
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
    //std::cout << toRowVal << ", " << toColVal << ": " << newMoves.size() << std::endl;

    return newMoves;
}

std::vector<std::pair<int,int>> knightMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard) {
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

    //std::cout << toRowVal << ", " << toColVal << ": " << newMoves.size() << std::endl;
    return newMoves;
}

std::vector<std::pair<int,int>> bishopMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard) {
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
    //std::cout << toRowVal << ", " << toColVal << ": " << newMoves.size() << std::endl;
    return newMoves;
}

std::vector<std::pair<int, int>> kingMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard) {
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
    //std::cout << toRowVal << ", " << toColVal << ": " << newMoves.size() << std::endl;
    return newMoves;
}

std::vector<std::pair<int,int>> updateMoves(int ColVal, int RowVal,char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard) {
    
    std::vector<std::pair<int, int>> newMoves;
    //Pawn
    if(chessboard[RowVal][ColVal].name.compare("Pawn") == 0 ) {
        return pawnMoves(ColVal, RowVal, currentPlayer, chessboard);
    } 

    //Rook
    if(chessboard[RowVal][ColVal].name.compare("Rook") == 0) {
        return rookMoves(ColVal, RowVal, currentPlayer, chessboard);
    }

    
    //Knight
    if(chessboard[RowVal][ColVal].name.compare("Knight") == 0) {
        return knightMoves(ColVal, RowVal, currentPlayer, chessboard);
    }
    
    
    //Bishop
    if(chessboard[RowVal][ColVal].name.compare("Bishop") == 0) {
        return bishopMoves(ColVal, RowVal, currentPlayer, chessboard);
    }

    //Queen
    if(chessboard[RowVal][ColVal].name.compare("Queen") == 0) {
        std::vector<std::pair<int,int>> bMoves = bishopMoves(ColVal, RowVal, currentPlayer, chessboard);
        std::vector<std::pair<int,int>> rMoves = rookMoves(ColVal, RowVal, currentPlayer, chessboard);

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
        return kingMoves(ColVal, RowVal, currentPlayer, chessboard);
    }

    return chessboard[RowVal][ColVal].possibleMoves;

    

}