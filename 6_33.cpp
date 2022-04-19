#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

using std::cin;
using std::cout;
using std::endl;

int points_num = 0;
int threads_num = 0;
int total_pts = 0;
std::vector<pthread_t> threads;
void *count(void *X)
{ 
    int *threadID = (int*) thread_ID;   
    long cir_threads_num = 0;    
    for (size_t i = 0; i < threads_num; i++) {
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        if (x * x + y * y < 1) {
            cir_threads_num++;  
        }
    }

    double pi = (4.0 * (double)cir_threads_num) / ((double)numPointsPerThreads * 1);
    cout << "The number of points in circule : " << tcir_threads_num << endl; 
    cout << "The approximate value of pi for the desired amount of points: " << threadID << "is: " << pi << endl;
    pthread_mutex_lock(&mutex); 
    total_pts += cir_threads_num;
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

void createThreads(){
    do {
      cout << "Enter a positive number for the amount of points generate: \n";
      cin >> points_num;     
      cout << "Enter a positive number for the amount of threads generate: \n";
      cin >> threads_num;
    } while (points_num <= 0 || threads_num <=0); 
    
    int s;
    threads.resize(threads_num);
    pthread_attr_t attr; 
    pthread_attr_init(&attr); 
    cout << "---------------------" << endl;
    for (size_t = 0; i < threads_num; i++) {
        s = pthread_create(&threads[i], &attr, monteCarloPi,  (void *) i);
    }
    cout << "Created" << threads_num << "threads" << endl; 
}

void joinThreads(){
    int s;
    for (size_t i = 0; i < threads_num; i++) {
        s = pthread_join(threads[i], nullptr);
    }
    pthread_mutex_destroy(&mutex);
    threads.resize(0);
}



int main(int argc, char const *argv[])
{
    double pi; 
    createThreads(); 
    joinThreads(); 
    pi = (4.0 * (double)total_pts) / ((double)(points_num/threads_num) * threads_num);
    cout << "The approximate value of pi: " << pi << endl; 
    cout << "---------------------" << endl;
    return 0;
}
