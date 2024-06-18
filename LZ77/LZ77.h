#ifndef LZ77_H
#define LZ77_H

#include <string>
#include <vector>
#include <fstream>

class LZ77
{
private:
    int windowSize;
    int lookaheadBufferSize;
    std::ifstream in_file;
    std::ofstream out_file;
    std::string in_file_name, out_file_name;

    struct Match
    {
        int offset;
        int length;
        char nextChar;
    };

    Match findLongestMatch(const std::string& data, int currentPosition);

public:
    LZ77(int windowSize, int lookaheadBufferSize);
    void compress(const std::string& inputFile, const std::string& outputFile);
    void decompress(const std::string& inputFile, const std::string& outputFile);
};

#endif
