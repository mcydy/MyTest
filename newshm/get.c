#include "shmfifo.h"
#include <unistd.h>
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>

// #define RSP_ROI 
#define FILE_NAME "get.rgb"
#define BUFFER_SIZE 1920*1080*3
#define ROI_MAX 4
#define PERSON_MAX 100

typedef struct Box {
  int left_up_hor;      //左上x 坐标
  int left_up_ver;      //左上y 坐标
  int right_bottom_hor; // 右下x 坐标
  int right_bottom_ver; // 右下y 坐标
} Box;

typedef struct ImageShared {
  char cam_id[64]; //相机id 以'\0' 结尾字符串
  int64_t time_stamp;  //时间戳
  int width;       //图像宽
  int height;      // 图像高
  int roi_num;     // 相机roi 个数
  Box rois[ROI_MAX]; // 相机roi, 每个index对应一个roi, 有效个数由 roi_num决定
  unsigned char rgb[BUFFER_SIZE];  //
} ImageShared;

typedef struct Recoder {
  char cam_id[64];
  int64_t time_stamp;
  int roi_num;
  int person_num[ROI_MAX];
  Box box[ROI_MAX][PERSON_MAX];
} Recoder;

int main(void)
{
#ifdef RSP_ROI

	printf("define RSP_ROI\n");

	//创建共享内存
	shmfifo_t *fifo = shmfifo_init(11160,sizeof(Recoder),39);
	int i;
	Recoder s;
	memset(&s, 0, sizeof(Recoder));
	//创建消息队列
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0; //注意1     
    //建立消息队列   
    msgid = msgget((key_t)1121, 0666 | IPC_CREAT); 
    if(msgid == -1)
    {      
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);
    }  

    Recoder *img_share = (Recoder *)malloc(sizeof(Recoder));
    void *addr = NULL;
    //通过消息队列获取共享内存地址
    while(1) 
    { 
    	//接收队列数据
        if(msgrcv(msgid, (void*)&data, sizeof(data), msgtype, 0) == -1)  
        {  
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);  
            exit(EXIT_FAILURE);    
        }  
        printf("You write:%d\n", data.index);

   		//获取地址，拷贝共享内存数据.
        get_shmaddr(fifo, data.index, &addr);
		memset(img_share,0,sizeof(Recoder));
		memcpy(img_share, (void *)addr, sizeof(Recoder));
        // printf("recv:width:%d height:%d time_stamp:%d\n",img_share->width, img_share->height, img_share->time_stamp);

        for(int i = 0; i < img_share->roi_num; i++)
			printf("recv:person_num = %d\n",img_share->person_num[i]);
    }  
    //删除消息队列 
    if(msgctl(msgid, IPC_RMID, 0) == -1)   
    {      
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);
    }  
    //删除共享内存
    shmfifo_destory(fifo);

    free(img_share);


#else
	//打开输出文件
	FILE *fp = fopen(FILE_NAME,"w+");
	if(fp==NULL)
		printf("file open failed\n");
	//创建共享内存
	shmfifo_t *fifo = shmfifo_init(12000,sizeof(ImageShared),39);
	int i;
	ImageShared s;
	memset(&s, 0, sizeof(ImageShared));
	//创建消息队列
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0; //注意1     
    //建立消息队列   
    msgid = msgget((key_t)1118, 0666 | IPC_CREAT); 
    if(msgid == -1)
    {      
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);
    }  

    ImageShared *img_share = (ImageShared *)malloc(sizeof(ImageShared));
    void *addr = NULL;
    //通过消息队列获取共享内存地址
    while(1) 
    { 
    	//接收队列数据
        if(msgrcv(msgid, (void*)&data, sizeof(data), msgtype, 0) == -1)  
        {  
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);  
            exit(EXIT_FAILURE);    
        }  
        printf("You write: -----index----%d\n" ,data.index);

   		//获取地址，拷贝共享内存数据.
        get_shmaddr(fifo, data.index, &addr);
		memset(img_share,0,sizeof(ImageShared));
		memcpy(img_share, (void *)addr, sizeof(ImageShared));
        printf("recv:width:%d height:%d time_stamp:%d roi_num:%d\n",img_share->width, img_share->height, img_share->time_stamp, img_share->roi_num);

        //保存测试数据
        if(img_share->time_stamp == 103 ){
			int write_length = fwrite(img_share->rgb, 1, BUFFER_SIZE, fp);
			fflush(fp);
			printf("write to rgb file %p,%d\n", &s,write_length);
		}  
    }  
    //删除消息队列 
    if(msgctl(msgid, IPC_RMID, 0) == -1)   
    {      
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);
    } 
    //断开共享内存连接
    shmfifo_destory(fifo); 

    //free
    free(img_share);

    //fifo interface
    /*
	while(1){
		void *ppp = NULL;
		shmfifo_get(fifo,&s);
		printf("recv:rgb = %p,age=%d  width:%d height:%d time_stamp:%d\n",s.rgb,s.time_stamp,s.width, s.height, s.time_stamp);
		if(s.time_stamp == 60 ){
			int write_length = fwrite(s.rgb, 1, BUFFER_SIZE, fp);
			fflush(fp);
			s.time_stamp = 0;
			memset(&s, 0, sizeof(ImageShared));
			printf("write to rgb file %p,%d\n", &s,write_length);
		}
		sleep(1);
	}
	*/
#endif
	return 0;
}
