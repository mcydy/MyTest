#include "shmfifo.h"
#include <unistd.h>
#include <string.h> 
#include <stdio.h>


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define FILE_NAME "out.rgb"
#define BUFFER_SIZE (1920*1080*3)
#define PERSON_MAX 200
#define ROI_MAX 4


typedef struct stu
{
	
	char name[BUFFER_SIZE];
	int age;
	
}STU;

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

int main(int argc, char ** argv)
{


#ifdef RGB_DATA
	shmfifo_t *fifo = shmfifo_init(11120,sizeof(ImageShared),39);

	FILE *fp = fopen(FILE_NAME,"r+");
	if(fp==NULL)
		printf("file open failed\n");

	fseek (fp , 0 , SEEK_END);  
    int lSize = ftell (fp);  
    rewind (fp); 

    int i;
	ImageShared s;

	int wr_index = 0;

	memset(&s, 0, sizeof(ImageShared));

	int len = fread((void *)s.rgb,1,lSize,fp);
 
	for(i=0; i<50; i++)
	{
		s.time_stamp =  100+i;
		s.width = 1920;
		shmfifo_put(fifo,&s,&wr_index);
		printf("ppppppppppp====%d s.time_stamp %d\n",wr_index, s.time_stamp );
		// s.name[0] = s.name[0] + 1;
		printf("send ok %d\n",i);
   
	    struct msg_st data;
	    int msgid = -1;     //建立消息队列
	    msgid = msgget((key_t)1120, 0666 | IPC_CREAT);
	    if(msgid == -1)
	    {  
	        fprintf(stderr, "msgget failed with error: %d\n", errno);  
	        exit(EXIT_FAILURE);
	    }  
  
		static int i = 0;

		data.msg_type = 1;    //注意2     
		data.index = wr_index;
		printf("------------%d\n",data.index);

		if(msgsnd(msgid, (void*)&data, sizeof(data), 0) == -1) 
		{      
			fprintf(stderr, "msgsnd failed\n");       
		}       
		sleep(1);

		i++;

	}

	shmfifo_destory(fifo); 
 
#else


	shmfifo_t *fifo = shmfifo_init(11113,sizeof(Recoder),39);

    int i;
	Recoder s;
	int wr_index = 0;
	memset(&s, 0, sizeof(Recoder));

 
	for(; ; )
	{
		s.time_stamp =  100+i;
		s.roi_num = 2;
		strcpy(s.cam_id,"087ec4e5d8f6467988c40f083dad0b12");
		s.person_num[0] = 1;
		s.person_num[1] = 3;
		shmfifo_put(fifo,&s,&wr_index);
		printf("ppppppppppp====%d s.time_stamp %d\n",wr_index, s.time_stamp );
		// s.name[0] = s.name[0] + 1;
		printf("send ok %d\n",i);
   
	    struct msg_st data;
	    int msgid = -1;     //建立消息队列
	    msgid = msgget((key_t)2233, 0666 | IPC_CREAT);
	    if(msgid == -1)
	    {  
	        fprintf(stderr, "msgget failed with error: %d\n", errno);  
	        exit(EXIT_FAILURE);
	    }  
  
		static int i = 0;

		data.msg_type = 1;    //注意2     
		data.index = wr_index;
		printf("------------%d\n",data.index);

		if(msgsnd(msgid, (void*)&data, sizeof(data), 0) == -1) 
		{      
			fprintf(stderr, "msgsnd failed\n");       
		}       
		sleep(1);

		i++;

	}

	shmfifo_destory(fifo);


#endif

	return 0;
}
 