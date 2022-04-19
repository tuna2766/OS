#include <iostream>
#include <thread>
#include <cmath>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
std::vector<int> f;

void *child(void *param);

int Fibonacci(int n){
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return Fibonacci(n-1) + Fibonacci(n-2);
}

void *child(void *param) {
	f.resize(num);
    for (auto &x : f) {
        x = Fibonacci(i);
    }
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    int how_many_fib;
    std::cout << "Enter the number of Fibonaccis you wish to generate\n";
    std::cin >> how_many_fib;
    std::thread t1(child, how_many_fibonacci);
    t1.join();
    for(const auto &x : f) {
        std::cout << x << ' ';
        if(i % 10 == 0 && i != 0) {
            std::cout << '\n';
        }
    }
    return 0;
}
