#include "PuzzleLoaderDAT.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool PuzzleLoaderDAT::loadPuzzle(const std::string& filename, int gameID, std::vector<int>& board, std::string& difficulty) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    int currentID = 0;
    bool gameFound = false;

    while (std::getline(file, line)) {
        if (line.find("ID:") != std::string::npos) {
            std::stringstream ss(line);
            std::string prefix;
            ss >> prefix >> currentID;
            if (currentID == gameID) {
                gameFound = true;
            }
        }
        else if (line.find("Difficulty:") != std::string::npos && gameFound) {
            std::stringstream ss(line);
            std::string prefix;
            ss >> prefix >> difficulty;
        }
        else if (line.find("Board:") != std::string::npos && gameFound) {
            std::stringstream ss(line.substr(6)); // Remove "Board: " prefix
            int value;
            board.clear();  // Ensure board is empty before filling
            while (ss >> value) {
                board.push_back(value);
            }
            break; // We found the game, so we can stop here
        }
    }

    file.close();

    if (gameFound && board.size() == 9) {
        return true;
    }
    else {
        std::cerr << "Game ID " << gameID << " not found or board data is incomplete." << std::endl;
        return false;
    }
}

bool PuzzleLoaderDAT::savePuzzle(const std::string& filename, int gameID, const std::vector<int>& board, const std::string& difficulty) {
    std::ofstream file(filename, std::ios::app);  // Append mode to add new puzzle to the file
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    if (board.size() != 9) {
        std::cerr << "Invalid board size: must be 9 elements." << std::endl;
        return false;
    }

    file << "ID: " << gameID << std::endl;
    file << "Difficulty: " << difficulty << std::endl;
    file << "Board: ";
    for (size_t i = 0; i < board.size(); ++i) {
        file << board[i];
        if (i < board.size() - 1) {
            file << " ";
        }
    }
    file << std::endl;
    file << "---" << std::endl;  // Separator between puzzles

    file.close();
    return true;
}
