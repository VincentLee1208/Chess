#include <iostream>
#include <vector>

// Define constants for the chessboard dimensions
const int BOARD_SIZE = 8;
bool gameStart = false;
bool singlePlayer = true;

// Define a structure to represent a chess piece
struct ChessPiece {
    char symbol;
    std::string name;
};

// Create a 2D array to represent the chessboard
std::vector<std::vector<ChessPiece>> chessboard(BOARD_SIZE, std::vector<ChessPiece>(BOARD_SIZE));

// Initialize the chessboard with the starting positions of the pieces
void initializeChessboard() {
    // Initialize pawns for both players
    for (int col = 0; col < BOARD_SIZE; ++col) {
        chessboard[1][col] = { 'P', "Pawn" };
        chessboard[6][col] = { 'p', "Pawn" };
    }

    // Initialize remaining pieces for both players
    chessboard[0][0] = { 'R', "Rook" };
    chessboard[0][7] = { 'R', "Rook" };
    chessboard[7][0] = { 'r', "Rook" };
    chessboard[7][7] = { 'r', "Rook" };

    chessboard[0][1] = { 'N', "Knight" };
    chessboard[0][6] = { 'N', "Knight" };
    chessboard[7][1] = { 'n', "Knight" };
    chessboard[7][6] = { 'n', "Knight" };

    chessboard[0][2] = { 'B', "Bishop" };
    chessboard[0][5] = { 'B', "Bishop" };
    chessboard[7][2] = { 'b', "Bishop" };
    chessboard[7][5] = { 'b', "Bishop" };

    chessboard[0][3] = { 'Q', "Queen" };
    chessboard[0][4] = { 'K', "King" };
    chessboard[7][3] = { 'q', "Queen" };
    chessboard[7][4] = { 'k', "King" };
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


void getPlayerMove(int& fromCol, int& fromRow, int& toCol, int& toRow) {
    std::cout << "Move: ";
    std::cin >> fromCol >> fromRow >> toCol >> toRow;
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

int main() {
    /*
    while(!gameStart) {
        gameStart = displayMenu();
    }
    */
    
    initializeChessboard();
    displayChessboard();

    return 0;
}