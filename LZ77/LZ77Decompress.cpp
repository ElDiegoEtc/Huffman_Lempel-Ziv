#include <iostream>
#include "LZ77.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Uso: " << argv[0] << " <archivoComprimido> <archivoDescomprimido>" << std::endl;
        return 1;
    }

    std::string compressedFileName = argv[1];
    std::string decompressedFileName = argv[2];

    LZ77 lz77(0, 0); // Los tamaños de ventana y buffer no son necesarios para la descompresión
    lz77.decompress(compressedFileName, decompressedFileName);

    std::cout << "Archivo descomprimido: " << decompressedFileName << std::endl;

    return 0;
}
