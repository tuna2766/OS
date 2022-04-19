#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

int i = 0;	
int num = 0;
int total_pts = 0;

void *count(void *X)
{ 
    for (i = 0; i < num; i++)
    {	
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;
        
        if (((X * X) + (Y * Y)) <= 1)
        {
            total_pts++;
        }
    }
    return nullptr;
}

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    cout << "\n\nHI!\n\n";
    srand(time(nullptr));
    pthread_t thread;

    do
	{
        cout << "Enter a positive number for the amount of points generate: \n";
        cin >> num;  	
	}while (num <= 0);
  
    pthread_create(&thread, nullptr, &count, nullptr);
    pthread_join(thread, nullptr);
    
    double pi = (4.0 * total_pts) / num;
    cout << "The number of points that occcur within circule : " << total_pts << endl; 
    cout << "The approximate value of pi for the desired amount of points " << num << "is: " << pi << endl;
    return 0;
 }
