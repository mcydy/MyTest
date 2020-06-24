#include <thread>
#include <mutex>
#include <stdio.h>
#include <unistd.h>

int g_i = 0;
std::mutex g_i_mutex;  // protects g_i
 
void safe_increment()
{
	printf("00000\n");
    std::lock_guard<std::mutex> lock(g_i_mutex);
	char *p = (char *)malloc(100000);
    while(1){
    ++g_i;
 	printf("+++++++++%d------\n",g_i);
    // g_i_mutex is automatically released when lock
    // goes out of scope
   
    sleep(10);
	printf("pthread exit\n");
  //   break;
	return;
	}
}

void safe_increment1()
{
	printf("1111\n");
    std::lock_guard<std::mutex> lock(g_i_mutex);

    while(1){
    ++g_i;
 	printf("----------%d------\n",g_i);
    // g_i_mutex is automatically released when lock
    // goes out of scope
    
    sleep(1);
//    break;
	}
}
 
int main()
{
    std::thread t1(safe_increment);
//	t1.join(); 
	t1.detach();
	printf("join end\n");
	sleep(20); 
//  std::thread t2(safe_increment1);
 
//    t1.join();
  //  t2.join();
} 
