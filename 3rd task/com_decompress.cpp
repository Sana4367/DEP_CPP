#include <iostream>
#include <fstream>
#include <string>

// Function to compress the file using Run-Length Encoding
void compressFile(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile || !outFile) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    char currentChar, nextChar;
    int count;

    while (inFile.get(currentChar)) {
        count = 1;
        while (inFile.get(nextChar) && currentChar == nextChar) {
            count++;
            if (count == 255) {
                break;
            }
        }

        outFile.put(currentChar);
        outFile.put(static_cast<char>(count));

        if (currentChar != nextChar) {
            inFile.putback(nextChar);
        }
    }

    inFile.close();
    outFile.close();
}

// Function to decompress the file using Run-Length Encoding
void decompressFile(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile || !outFile) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    char currentChar, countChar;
    int count;

    while (inFile.get(currentChar) && inFile.get(countChar)) {
        count = static_cast<unsigned char>(countChar);
        for (int i = 0; i < count; ++i) {
            outFile.put(currentChar);
        }
    }

    inFile.close();
    outFile.close();
}

int main() {
    std::string inputFile, compressedFile, decompressedFile;
    
    std::cout << "Enter the name of the file to compress: ";
    std::cin >> inputFile;
    
    compressedFile = inputFile + ".rle";
    decompressedFile = "decompressed_" + inputFile;

    compressFile(inputFile, compressedFile);
    decompressFile(compressedFile, decompressedFile);

    std::cout << "File compressed to: " << compressedFile << std::endl;
    std::cout << "File decompressed to: " << decompressedFile << std::endl;

    return 0;
}
