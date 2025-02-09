#include<chrono>
using namespace std;
time_t get_current_time()
{
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);
        return currentTime;
}
 
