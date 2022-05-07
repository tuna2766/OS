#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
using std::cout;
using std::cin;
using std::endl;
int main(int argc, char const *argv[])
{
    std::string inputFile, outputFile, 
                inputName, outputName;
    const int bufferSize = 32768;         
    char buffer[bufferSize];
    int inputFD, outputFD;
    ssize_t bytesRd, bytesWr;
   
    cout << "Enter input file name: " << endl;
    cin >> inputName;

    cout << "Enter ouput file name: " << endl;
    cin >> outputName;

    inputFD = open(inputName.c_str(), O_RDONLY);    
    if (inputFD == -1) {
        perror ("Can not open Input File");
    }

    outputFD = open(outputName.c_str(), O_WRONLY | O_CREAT, 0644);
    if(outputFD == -1){
        perror("Can not open Output File");
    }

    while((bytesRd = read(inputFD, &buffer, bufferSize)) > 0){
        bytesWr = write(outputFD, &buffer, (ssize_t)bytesRd);
        if(bytesWr != bytesRd) {
            perror("Writ");
        }
        else {
          cout <<"The file has been copied correctly" << endl;
        } 
    }
    close (inputFD);
    close (outputFD);
    return 0;
}