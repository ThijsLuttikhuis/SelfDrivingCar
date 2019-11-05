//
// Created by thijs on 05-11-19.
//

#include <fstream>
#include "FileReadWrite.h"

int FileReadWrite::readFile() {
    std::ifstream myfile("input.txt");
    int intermediate;
    int newState = -1;
    if (myfile.is_open()) {
        while (myfile >> intermediate) {
            newState = intermediate;
        }
        myfile.close();
    }
    return newState;
}

void FileReadWrite::clearFile() {
    std::ofstream file("input.txt", std::ios::trunc);
}

int FileReadWrite::writeFile(const char* input, int read, int readNew) {
    if (read != readNew) {
        std::ofstream fout;
        fout.open("log.txt", std::ios::trunc);
        fout << input;
        fout.close();
    }
    read = readNew;
    return read;
}

void FileReadWrite::writeControl(int input) {
    std::ofstream fout;
    fout.open("input.txt", std::ios::trunc);
    fout << input;
    fout.close();
}
