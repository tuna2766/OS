#include <iostream>
#include <stdlib.h>

#define PAGE_SIZE 4096

int main(int argc, char **argv) {

    unsigned int address;
    unsigned int page_number;
    unsigned int offset;

    if(argc < 2) {
        std::cout << "Enter the address: ";
        return -1;
    }

    address = atoi(argv[1]);
    page_number = address / PAGE_SIZE;
    offset = address % PAGE_SIZE;

    std::cout << "The address = " << address << " contains:\nPage number = " << 
    page_number << "\noffset = " << offset << std::endl;

    return 0;
}