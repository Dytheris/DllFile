// File: FileProcessorDLL.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "pch.h"

extern "C" __declspec(dllexport) bool RemoveCharacter(const char* inputFilePath, const char* outputFilePath, char charToRemove, int charCount) {
    if (inputFilePath == nullptr || outputFilePath == nullptr || charCount <= 0) {
        std::cerr << "Invalid input parameters." << std::endl;
        return false;
    }

    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return false;
    }

    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create output file." << std::endl;
        inputFile.close();
        return false;
    }

    char ch;
    int count = 0;
    while (inputFile.get(ch) && count < charCount) {
        // Проверка, нужно ли удалять текущий символ
        if (ch != charToRemove) {
            outputFile.put(ch);
        }
        count++;
    }

    // Продолжаем записывать остаток файла, удаляя указанный символ
    while (inputFile.get(ch)) {
        if (ch != charToRemove) {
            outputFile.put(ch);
        }
    }

    inputFile.close();
    outputFile.close();
    return true;
}