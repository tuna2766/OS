#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

const int BUFFER_SIZE = 32768;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const *argv[])
{
    int fdone[2];
    int fileOpenName = open(argv[1], 0);
    int targetFileName = open(argv[2], O_RDWR|O_CREAT|O_APPEND, 0666);
    pid_t pid;
    char buffer[BUFFER_SIZE];
    
    pipe(fdone);
    if(argc != 3) {
        cout << "ERROR : at least 2 argument." << endl;
        exit(1);
    }

    if (fileOpenName == -1 || targetFileName == -1) {
        cout << "Opening file error" << endl;
        exit(1);
    }
    
    pid = fork();

    if (pid == 0) {
        close(fdone[1]);
        while (read(fdone[0], buffer, sizeof(buffer)) > 0) {
            write(targetFileName, buffer, strlen(buffer) - 1);
        }

        close(fdone[0]);
        close(targetFileName);
    }else {
        close(fdone[0]);
        while (read(fileOpenName, buffer, sizeof(buffer)) > 0) {
            write(fdone[1], buffer, sizeof(buffer));
            memset(buffer, 0, BUFFER_SIZE);
        }

        close(fdone[1]);
        close(fileOpenName);
        wait(nullptr);
    }
    return 0;
}
