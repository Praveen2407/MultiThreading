/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
//input -10
//t1 - 13579
//t2 - 246810


#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

/*mutex m;
bool flag = true;
void printData(int x, bool){
    m.lock();
    while(x){

        if(  (x%2 == 0) && (flag) ){
                cout << x << " ";
            if(x == 2){
                x =1;
                flag = false;
            }
        }
        else if(x%2 != 0 && (!flag)){
            cout << x << " ";
             if(x == 1)
                flag = false;
        }
        x--;
    }
    cout << "\n";
    m.unlock();
}
int main()
{

    thread t1(printData,50,flag);
    thread t2(printData,50,flag);
    t1.join();
    t2.join();

    return 0;
}
*/

#include <condition_variable>

std::mutex mu;
std::condition_variable cond;
int count = 1;

void PrintOdd(int x)
{
    for(; count < x;)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker,[](){ return (count%2 == 1); });
        std::cout << "From Odd:    " << count << std::endl;
        count++;
        locker.unlock();
        cond.notify_all();
    }

}

void PrintEven(int x)
{
    for(; count < x;)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker,[](){ return (count%2 == 0); });
        std::cout << "From Even: " << count << std::endl;
        count++;
        locker.unlock();
        cond.notify_all();
    }
}

int main()
{
    std::thread t1(PrintOdd,100);
    std::thread t2(PrintEven,100);
    t1.join();
    t2.join();
    return 0;
}
