#ifndef PUZZLE_LOADER_H
#define PUZZLE_LOADER_H

#include <vector>
#include <string>

class PuzzleLoader {
public:
    virtual ~PuzzleLoader() = default;

    virtual bool loadPuzzle(const std::string& filename, int gameID, std::vector<int>& board, std::string& difficulty) = 0;
    virtual bool savePuzzle(const std::string& filename, int gameID, const std::vector<int>& board, const std::string& difficulty) = 0;
};

#endif // PUZZLE_LOADER_H
