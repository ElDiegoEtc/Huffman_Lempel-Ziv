### Huffman_Lempel-Ziv
Proyecto semestral para estructura de datos sobre la comparacion de algoritmo para codificar vs algoritmo para comprimir utilizando Huffman y Lempel-Ziv

Integrantes: 
- Alejandro Neira Montero
- Camilo Tapia Correa
- Diego Oyarzo Navia

Instrucciones de ejecucion (windows):

#Huffman
1) Generar ejecutables decoding y coding
    g++ huffman.cpp huffmanCoding.cpp -o Coding
    g++ huffman.cpp huffmanDecoding.cpp -o Decoding

2) Para la codificacion, se ingresa el ejecutable para codificar .exe, archivo de entrada .txt y el archivo de salida codificado .huf
    ./Coding test.txt testC.huf

3) Para la decodificacion, se ingresa el ejecutable para decodificar .exe, archivo de entrada codificado .huf y el archivo de salida decodificado .txt
    ./Decoding testC.huf testD.txt


#Lempel-Ziv
1) Generar ejecutables Compress y Decompress
    g++ LZ77.cpp LZ77Compress.cpp -o Compress
    g++ LZ77.cpp LZ77Decompress.cpp -o Decompress

2) Para la compresion, se ingresa el ejecutable para comprimir, los valores de ventanas, los valores para el buffer, el archivo de entrada .txt y el archivo de salida comprimido .lz77
    (Usado para texting de archivos de 5MB)./Compress 32768 4096 dna.txt dnaC.lz77
    (Usado para texting de archivos de 10MB)./Compress 65536 8192 dna.txt dnaC.lz77

3) Para la Descompresion, se ingresa el ejecutable para Descomprimir, los valores de ventanas, los valores para el buffer, el archivo de entrada comprimido .lz77, el archivo de salida descomprimido .txt
    ./Decompress dnaC.lz77 dnaD.lz77
