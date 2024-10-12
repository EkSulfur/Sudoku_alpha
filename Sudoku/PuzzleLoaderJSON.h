// PuzzleLoaderJSON.h
#ifndef PUZZLELOADERJSON_H
#define PUZZLELOADERJSON_H

#include "PuzzleLoader.h"

class PuzzleLoaderJSON : public PuzzleLoader {
public:
    bool loadPuzzle(PuzzleData& data) override;
    bool savePuzzle(const PuzzleData& data) override;
};

#endif // PUZZLELOADERJSON_H
