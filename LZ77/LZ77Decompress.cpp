#include <iostream>
#include <chrono>
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
    float tiempo_total = 0;
    
    LZ77 lz77(0, 0); // Los tamaños de ventana y buffer no son necesarios para la descompresión
    for (int i = 0; i <= 1; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        lz77.decompress(compressedFileName, decompressedFileName);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        tiempo_total += elapsed.count();
    }
    double avg_time = tiempo_total / 20;
    
    // Calcula tamaño de archivo input y output
    std::ifstream input_file(argv[1], std::ios::binary | std::ios::ate);
    std::ifstream output_file(argv[2], std::ios::binary | std::ios::ate);

    if (!input_file.is_open()) {
        std::cerr << "Error opening input file to calculate size" << std::endl;
        return 1;
    }
    if (!output_file.is_open()) {
        std::cerr << "Error opening output file to calculate size" << std::endl;
        return 1;
    }

    auto input_size = input_file.tellg();
    auto output_size = output_file.tellg();

    input_file.close();
    output_file.close();

    // guarda avg_time, input_size, and output_size en archivo CSV
    std::ofstream csv_file("resultados_decompress.csv", std::ios::app); // Abre en append mode para no sobreescribir datos anteriores
    if (!csv_file.is_open()) {
        std::cerr << "Error opening resultados_decompress.csv file" << std::endl;
        return 1;
    }

    // If the file is newly created, add headers
    csv_file.seekp(0, std::ios::end);
    if (csv_file.tellp() == 0) {
        csv_file << "Tiempo promedio(ms),Archivo Codificado(bytes),Archivo Descomprimido(bytes)" << std::endl;
    }

    csv_file << avg_time << "," << input_size << "," << output_size << std::endl;
    csv_file.close();

    std::cout << "Archivo descomprimido: " << decompressedFileName << std::endl;

    return 0;
}
