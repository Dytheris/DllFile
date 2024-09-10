// File: FileProcessorApp.cpp
#include <iostream>
#include <windows.h>
#include <string>

// Определим тип функции, которая загружается из библиотеки
typedef bool (*RemoveCharacterFunc)(const char*, const char*, char, int);

int main() {
    // Задаем фиксированный путь к DLL-файлу
    const std::wstring dllPath = L"C:\\Users\\dslud\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\x64\\Debug\\FileProcessorDLL.dll";

    // Запрашиваем у пользователя путь к входному файлу, выходному файлу, символ для удаления и количество символов для обработки
    std::wstring inputFilePath, outputFilePath;
    wchar_t charToRemove; // Используем wchar_t для считывания символов
    int charCount;

    std::wcout << L"Enter input file path: ";
    std::getline(std::wcin, inputFilePath);

    std::wcout << L"Enter output file path: ";
    std::getline(std::wcin, outputFilePath);

    std::wcout << L"Enter character to remove: ";
    std::wcin >> charToRemove;

    std::wcout << L"Enter number of characters to process: ";
    std::wcin >> charCount;

    // Преобразуем wchar_t в char
    char charToRemoveConverted = static_cast<char>(charToRemove);

    // Загружаем библиотеку из указанного пути
    HINSTANCE hDll = LoadLibraryW(dllPath.c_str());
    if (!hDll) {
        std::wcerr << L"Error: Could not load the DLL file from " << dllPath << std::endl;
        return 1;
    }

    // Получаем адрес функции из библиотеки
    RemoveCharacterFunc removeFunc = (RemoveCharacterFunc)GetProcAddress(hDll, "RemoveCharacter");
    if (!removeFunc) {
        std::wcerr << L"Error: Could not find the function in the DLL." << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    // Вызываем функцию для обработки файла
    bool result = removeFunc(
        std::string(inputFilePath.begin(), inputFilePath.end()).c_str(),
        std::string(outputFilePath.begin(), outputFilePath.end()).c_str(),
        charToRemoveConverted, // Передаем преобразованный символ
        charCount
    );

    if (!result) {
        std::wcerr << L"Error: Failed to process the file." << std::endl;
    }
    else {
        std::wcout << L"File processed successfully." << std::endl;
    }

    // Освобождаем библиотеку
    FreeLibrary(hDll);
    return 0;
}