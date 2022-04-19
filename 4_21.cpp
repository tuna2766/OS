#include <iostream>
#include <thread>
#include <cmath>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
std::vector<int> f;
int how_many_fib;

int Fibonacci(int n){
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return Fibonacci(n-1) + Fibonacci(n-2);
}

void child(int num) {
	//f.resize(how_many_fib);
    for (int i = 0; i < num; i++) {
        f.emplace_back(Fibonacci(i));
    }
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    std::cout << "Enter the number of Fibonaccis you wish to generate\n";
    std::cin >> how_many_fib;
    std::thread t1(child, how_many_fib);
    t1.join();
    for(const auto &x : f) {
        std::cout << x << ' ';
    }
    cout << endl;
    return 0;
}
