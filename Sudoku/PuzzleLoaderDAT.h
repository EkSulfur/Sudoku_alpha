// PuzzleLoaderDAT.h
#ifndef PUZZLELOADERDAT_H
#define PUZZLELOADERDAT_H

#include "PuzzleLoader.h"
#include <string>

class PuzzleLoaderDAT : public PuzzleLoader {
public:
   
    PuzzleLoaderDAT()
        : filename("Puzzles.dat") {
    }
    bool loadPuzzle(PuzzleData& data) override;
    bool savePuzzle(const PuzzleData& data) override;

private:
    std::string filename;
};

#endif // PUZZLELOADERDAT_H
