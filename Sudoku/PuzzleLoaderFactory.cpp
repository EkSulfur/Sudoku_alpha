// PuzzleLoaderFactory.cpp
#include "PuzzleLoaderFactory.h"
#include "PuzzleLoaderDAT.h"
#include "PuzzleLoaderJSON.h"
#include "PuzzleLoaderXML.h"

PuzzleLoader* PuzzleLoaderFactory::createPuzzleLoader(const std::string& format) {
    if (format == "DAT") {
        return new PuzzleLoaderDAT();
    }
    else if (format == "JSON") {
        return new PuzzleLoaderJSON();
    }
    else if (format == "XML") {
        return new PuzzleLoaderXML();
    }
    else {
        return nullptr;
    }
}
