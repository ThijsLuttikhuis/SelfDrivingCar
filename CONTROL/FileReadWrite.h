//
// Created by thijs on 05-11-19.
//

#ifndef SELFDRIVINGCAR_FILEREADWRITE_H
#define SELFDRIVINGCAR_FILEREADWRITE_H


class FileReadWrite {
public:
    static int readFile();

    static void clearFile();

    static int writeFile(const char*, int, int);

    static void writeControl(int input);
};


#endif //SELFDRIVINGCAR_FILEREADWRITE_H
