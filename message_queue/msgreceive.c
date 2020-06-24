/*使用消息队列通信*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
struct msg_st
{  
    long int msg_type; 
    void *msg_addr;
    char text[BUFSIZ];
};
int main()
{  
    int running = 1;   
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0; //注意1     //建立消息队列   
    msgid = msgget((key_t)4444, 0666 | IPC_CREAT); 
    if(msgid == -1)
    {      
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);
    }   //从队列中获取消息，直到遇到end消息为止 
    while(running) 
    { 
	printf("while---\n"); 
    printf("BUFSIZis %d\n",BUFSIZ);
        if(msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1)  
        {  
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);  
            exit(EXIT_FAILURE);    
        }  
        printf("You wrote: %s---%p\n",data.text, data.msg_addr);        //遇到end结束  

        // static int flag = 0;
        // void *pp = malloc(1920*1080*4);
        // if(flag == 0){
        //     printf("(sizeof(ImageShared) is %d)\n",5);
        //     memset(pp,0,5);
        //     memcpy(pp, data.msg_addr, 5);
        //     flag =1;
        // }

        if(strncmp(data.text, "end", 3) == 0)      
            running = 0;   
    }   //删除消息队列   
    if(msgctl(msgid, IPC_RMID, 0) == -1)   
    {      
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);
    }  
    exit(EXIT_SUCCESS);
}
