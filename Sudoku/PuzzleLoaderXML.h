// PuzzleLoaderXML.h
#ifndef PUZZLELOADERXML_H
#define PUZZLELOADERXML_H

#include "PuzzleLoader.h"

class PuzzleLoaderXML : public PuzzleLoader {
public:
    bool loadPuzzle(PuzzleData& data) override;
    bool savePuzzle(const PuzzleData& data) override;
};

#endif // PUZZLELOADERXML_H
