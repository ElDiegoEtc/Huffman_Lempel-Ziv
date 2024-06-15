#include <iostream>
#include "huffman.h"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Usage:\n\t huffmanDecoding inputfile outputfile" << endl;
		exit(1);
	}
	float tiempo_total = 0;

	for (int i = 1; i <= 10; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		huffman h(argv[1], argv[2]);
		h.recreate_huffman_tree();
		if (i==10){
			h.decoding_save();
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		tiempo_total += elapsed.count();
	}
	float avg_time = tiempo_total/20;
	cout << "Tiempo promedio (20 iteraciones): " << avg_time << "nanoseg.";
	cout << endl;
	return 0;
}
