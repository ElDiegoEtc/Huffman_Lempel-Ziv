#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "LZ77.h"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " <windowSize> <lookaheadBufferSize> <archivoEntrada> <archivoSalida>\n";
        return 1;
    }

    size_t windowSize = std::stoi(argv[1]);
    size_t lookaheadBufferSize = std::stoi(argv[2]);
    std::string inputFile = argv[3];
    std::string outputFile = argv[4];

    LZ77 lz77(windowSize, lookaheadBufferSize);
    try {
        lz77.compress(inputFile, outputFile);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}