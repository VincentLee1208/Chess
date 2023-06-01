#ifndef CHESSLOGIC_H
#define CHSSLOGIC_H

#include <vector>
#include "chesspiece.h"

const int BOARD_SIZE = 8;

void makeMove(char fromCol, int fromRow, char toCol, int toRow, char currentPlayer , std::vector<std::vector<ChessPiece>> &chessboard);

std::vector<std::pair<int,int>> pawnMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard);
std::vector<std::pair<int,int>> rookMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard);
std::vector<std::pair<int,int>> knightMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard);
std::vector<std::pair<int,int>> bishopMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard);
std::vector<std::pair<int, int>> kingMoves(int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard);

std::vector<std::pair<int,int>> updateMoves(int ColVal, int RowVal,char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard);

bool validateMove(int fromColVal, int fromRowVal, int toColVal, int toRowVal, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard);
bool isValidMove(char fromCol, int fromRow, char toCol, int toRow, char currentPlayer, std::vector<std::vector<ChessPiece>> &chessboard);

#endif