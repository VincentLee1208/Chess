#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include <string>

struct ChessPiece {
    char symbol;
    char player;
    std::string name;
    std::vector<std::pair<int,int>> possibleMoves;
};

#endif