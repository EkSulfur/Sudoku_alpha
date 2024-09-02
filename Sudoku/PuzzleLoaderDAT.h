#ifndef PUZZLE_LOADER_DAT_H
#define PUZZLE_LOADER_DAT_H

#include "PuzzleLoader.h"

class PuzzleLoaderDAT : public PuzzleLoader {
public:
    bool loadPuzzle(const std::string& filename, int gameID, std::vector<int>& board, std::string& difficulty) override;
    bool savePuzzle(const std::string& filename, int gameID, const std::vector<int>& board, const std::string& difficulty) override;
};

#endif // PUZZLE_LOADER_DAT_H
