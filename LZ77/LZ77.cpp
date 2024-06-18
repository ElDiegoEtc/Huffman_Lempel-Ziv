#include "LZ77.h"
#include <iostream>
#include <sstream>

LZ77::LZ77(int windowSize, int lookaheadBufferSize)
    : windowSize(windowSize), lookaheadBufferSize(lookaheadBufferSize) {}

LZ77::Match LZ77::findLongestMatch(const std::string& data, int currentPosition)
{
    Match match;
    match.offset = 0;
    match.length = 0;
    match.nextChar = data[currentPosition];

    int endOfBuffer = std::min(currentPosition + lookaheadBufferSize, static_cast<int>(data.size()));
    for (int i = std::max(0, currentPosition - windowSize); i < currentPosition; i++)
    {
        int length = 0;
        while (length < lookaheadBufferSize && currentPosition + length < data.size() && data[i + length] == data[currentPosition + length])
        {
            length++;
        }
        if (length > match.length)
        {
            match.length = length;
            match.offset = currentPosition - i;
            if (currentPosition + length < data.size())
            {
                match.nextChar = data[currentPosition + length];
            }
        }
    }
    return match;
}

void LZ77::compress(const std::string& inputFile, const std::string& outputFile)
{
    in_file.open(inputFile, std::ios::in);
    out_file.open(outputFile, std::ios::out | std::ios::binary);

    if (!in_file.is_open())
    {
        std::cerr << "Error al abrir el archivo de entrada: " << inputFile << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << in_file.rdbuf();
    std::string data = buffer.str();

    int currentPosition = 0;
    while (currentPosition < data.size())
    {
        Match match = findLongestMatch(data, currentPosition);
        out_file.write(reinterpret_cast<const char*>(&match.offset), sizeof(match.offset));
        out_file.write(reinterpret_cast<const char*>(&match.length), sizeof(match.length));
        out_file.write(reinterpret_cast<const char*>(&match.nextChar), sizeof(match.nextChar));
        currentPosition += match.length + 1;
    }

    in_file.close();
    out_file.close();
}

void LZ77::decompress(const std::string& inputFile, const std::string& outputFile)
{
    in_file.open(inputFile, std::ios::in | std::ios::binary);
    out_file.open(outputFile, std::ios::out);

    if (!in_file.is_open())
    {
        std::cerr << "Error al abrir el archivo de entrada: " << inputFile << std::endl;
        return;
    }

    std::vector<char> decompressedData;
    int offset, length;
    char nextChar;

    while (in_file.read(reinterpret_cast<char*>(&offset), sizeof(offset)))
    {
        in_file.read(reinterpret_cast<char*>(&length), sizeof(length));
        in_file.read(reinterpret_cast<char*>(&nextChar), sizeof(nextChar));
        
        int currentPosition = decompressedData.size();
        for (int i = 0; i < length; i++)
        {
            decompressedData.push_back(decompressedData[currentPosition - offset + i]);
        }
        decompressedData.push_back(nextChar);
    }

    for (char c : decompressedData)
    {
        out_file.put(c);
    }

    in_file.close();
    out_file.close();
}
