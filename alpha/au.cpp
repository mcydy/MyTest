#include <iostream>
#include <stdio.h>
int main()
{
	for(int i = 0; i<=8; i++)
	{
	auto work_number = [&](){
	while(1){
	printf("%d\n",i);
	sleep(1);	
	}
	}
	}
}
