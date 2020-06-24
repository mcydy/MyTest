#ifdef __cplusplus
extern "C" {
#endif

#ifndef __SHMFIFO_H__
#define __SHMFIFO_H__
#include <sys/ipc.h>

typedef struct shmhead {
  unsigned int blksize;  //块大小
  unsigned int blocks;   //总块数
  unsigned int rd_index; //读索引
  unsigned int wr_index; //写索引
} shmhead_t;

typedef struct shmfifo {
  shmhead_t *p_shm; //共享内存头部指针
  char *p_payload;  //有效负载真实地址
  int shmid;        //共享内存ID
  int sem_mutex;    //互斥信号量
  int sem_full;     //满信号量
  int sem_empty;    // 控信号量

} shmfifo_t;


struct msg_st
{  
    int msg_type;   
    int index;
    char message[64];
};

shmfifo_t *shmfifo_init(key_t key, int blksize, int blocks);
void shmfifo_put(shmfifo_t *fifo, const void *buf, int *index);
void shmfifo_get(shmfifo_t *fifo, const void *buf);
void shmfifo_destory(shmfifo_t *fifo);
void get_shmaddr(shmfifo_t *fifo, int rd_index, void **shm_addr);

#endif

#ifdef __cplusplus
}
#endif