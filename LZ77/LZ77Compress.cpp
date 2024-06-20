#include <iostream>
#include <chrono>
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
    float tiempo_total = 0;

    LZ77 lz77(windowSize, lookaheadBufferSize);
    for (int i = 1; i <= 1; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        try {
            lz77.compress(inputFile, outputFile);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        tiempo_total += elapsed.count();
    }
    double avg_time = tiempo_total / 20;

    // Calcula tamaño de archivo input y output
    std::ifstream input_file(argv[3], std::ios::binary | std::ios::ate);
    std::ifstream output_file(argv[4], std::ios::binary | std::ios::ate);

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
    std::ofstream csv_file("resultados_compress.csv", std::ios::app); // Abre en append mode para no sobreescribir datos anteriores
    if (!csv_file.is_open()) {
        std::cerr << "Error opening resultados_compress.csv file" << std::endl;
        return 1;
    }

    // If the file is newly created, add headers
    csv_file.seekp(0, std::ios::end);
    if (csv_file.tellp() == 0) {
        csv_file << "Tiempo promedio(milliseconds),Archivo Original(bytes),Archivo Codificado(bytes)" << std::endl;
    }

    csv_file << avg_time << "," << input_size << "," << output_size << std::endl;
    csv_file.close();
    
    

    return 0;
}