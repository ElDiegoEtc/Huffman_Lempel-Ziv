#include <iostream>
#include <chrono>
#include <fstream>
#include "huffman.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage:\n\t huffmanCoding inputfile outputfile" << endl;
        exit(1);
    }
    float tiempo_total = 0;

    for (int i = 1; i <= 20; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        huffman h(argv[1], argv[2]);
        h.create_pq();
        h.create_huffman_tree();
        h.calculate_huffman_codes();
        if (i == 20){
            h.coding_save();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        tiempo_total += elapsed.count();
    }
    double avg_time = tiempo_total / 20;

    // Calcula tamaño de archivo input y output
    ifstream input_file(argv[1], ios::binary | ios::ate);
    ifstream output_file(argv[2], ios::binary | ios::ate);

    if (!input_file.is_open()) {
        cerr << "Error opening input file to calculate size" << endl;
        return 1;
    }
    if (!output_file.is_open()) {
        cerr << "Error opening output file to calculate size" << endl;
        return 1;
    }

    auto input_size = input_file.tellg();
    auto output_size = output_file.tellg();

    input_file.close();
    output_file.close();

    // guarda avg_time, input_size, and output_size en archivo CSV
    ofstream csv_file("resultados_coding.csv", ios::app); // Abre en append mode para no sobreescribir datos anteriores
    if (!csv_file.is_open()) {
        cerr << "Error opening resultados_coding.csv file" << endl;
        return 1;
    }

    // If the file is newly created, add headers
    csv_file.seekp(0, ios::end);
    if (csv_file.tellp() == 0) {
        csv_file << "Tiempo promedio(milliseconds),Archivo Original(bytes),Archivo Codificado(bytes)" << endl;
    }

    csv_file << avg_time << "," << input_size << "," << output_size << endl;
    csv_file.close();

    return 0;
}