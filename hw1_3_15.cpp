#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
using std::cout;
using std::cin;
using std::endl;
int main(int argc, char const *argv[])
{
    const std::string shareName = "Shared";
    int shareFd = shm_open(shareName.c_str(), O_CREAT|O_RDWR, 0);
    if(shareFd == -1)  cout << "Shm_open erro.r" << endl;

    int fTruncRes = ftruncate(shareFd, 64);
    if(fTruncRes == -1)  cout << "Ftruncate error." << endl;

    auto shMm = (int *) mmap(0, 64, PROT_READ|PROT_WRITE, MAP_SHARED, shareFd, 0);
    if(shMm == MAP_FAILED) cout << "Mmap error." << endl;
    pid_t pid = fork();
    if(pid < 0) cout << "Fork failed." << endl;
    else if(pid==0) {
        cout << "Child process start." << endl;
	    cout << "Enter a positive integer : " << endl;
        int n, i = 1;
	    cin >> n;
        shMm[0] = n;
        while(n > 1) {
	        if(n % 2 == 0) {
		        shMm[i] = n / 2;
		        n = n / 2;
		        i++;
	        }else {
		        shMm[i] = 3 * n + 1;
		        n = 3 * n + 1;
		        i++;
	        }
	    }
        shMm[i] = -1;
	    return 0;
    }else {
        wait(nullptr);
	    cout << "Child process finish. " << endl; 
	    cout << "Showing Collatz conjecture : " << endl;
	    int i = 0;
        while(shMm[i] != -1){
	        cout << shMm[i] << endl;
	        i++;
	    }

        int res = shm_unlink(shareName.c_str());
        if(res == 0)
	        cout << "Shared memory unlinked." << endl;
        else
	        cout << "Unlinking shared memory error." << endl;
    }
    return 0;
}
