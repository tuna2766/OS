#include <cstring>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const *argv[])
{
    int n = 0;
    pid_t pid;

	cout << "Enter a positive integer : " << endl;
    while(cin >> n && n <= 0) {
        cout << "Enter a positive integer : " << endl;
    }
    pid = fork();
    if (pid == 0) {
        cout << "Child process start..." << endl;
	    cout << n << endl;

        while (n != 1) {
            if (n % 2 == 0) {
                 n = n / 2;
            } else if (n % 2 == 1) {
                n = 3 * (n) + 1;
            }	
            cout << n << endl;
        }
        cout << "Child process finish." << endl;
    }else {
        cout << "Parent process is waiting on child process..." << endl;
	    wait(nullptr);
	    cout << "Parent process finish." << endl;
    }
    return 0;
}
