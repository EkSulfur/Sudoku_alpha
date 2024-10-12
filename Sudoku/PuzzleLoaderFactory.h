// PuzzleLoaderFactory.h
#ifndef PUZZLELOADERFACTORY_H
#define PUZZLELOADERFACTORY_H

#include <string>
#include "PuzzleLoader.h"

class PuzzleLoaderFactory {
public:
    static PuzzleLoader* createPuzzleLoader(const std::string& format);
};

#endif // PUZZLELOADERFACTORY_H
