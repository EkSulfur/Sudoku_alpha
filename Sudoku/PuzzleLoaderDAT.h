#ifndef PUZZLELOADERDAT_H
#define PUZZLELOADERDAT_H

#include <vector>
#include <string>
#include "PuzzleLoader.h"

class PuzzleLoaderDAT : public PuzzleLoader {
public:
    bool loadPuzzle(const std::string& filename, int gameID, std::vector<std::vector<int>>& board, std::string& difficulty) override;
    bool savePuzzle(const std::string& filename, int gameID, const std::vector<std::vector<int>>& board, const std::string& difficulty) override;
};

#endif // PUZZLELOADERDAT_H
