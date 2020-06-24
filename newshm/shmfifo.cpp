#ifdef __cplusplus
extern "C" {
#endif
#include "shmfifo.h"
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

union semun {
  int val;
};

shmfifo_t *shmfifo_init(key_t key, int blksize, int blocks) {
  shmfifo_t *p = (shmfifo_t *)malloc(sizeof(shmfifo_t));
  memset(p, 0x00, sizeof(shmfifo_t));
  int shmid = shmget(key, 0, 0);
  // printf("shmid is %d\n",shmid);
  int len = blksize * blocks + sizeof(shmhead_t);
  if (shmid == -1) {
    // shared memory not created
    shmid = shmget(key, len, IPC_CREAT | 0644);
    if (shmid == -1) {
      throw "creat shared memory failed";
    }

    p->shmid = shmid;
    p->p_shm = (shmhead_t *)shmat(shmid, NULL, 0);
    p->p_shm->wr_index = 0;
    p->p_shm->rd_index = 0;
    p->p_shm->blksize = blksize;
    p->p_shm->blocks = blocks;
    p->p_payload = (char *)p->p_shm + sizeof(shmhead_t);
    p->sem_empty = semget(key, 1, IPC_CREAT | 0644);
    p->sem_full = semget(key + 1, 1, IPC_CREAT | 0644);
    p->sem_mutex = semget(key + 2, 1, IPC_CREAT | 0644);
    union semun su;
    su.val = 0;
    semctl(p->sem_empty, 0, SETVAL, su);
    su.val = blocks;
    semctl(p->sem_full, 0, SETVAL, su);
    su.val = 1;
    semctl(p->sem_mutex, 0, SETVAL, su);
  } else {
    // shared memory already created
    p->shmid = shmid;
    p->sem_empty = semget(key, 0, 0);
    p->sem_full = semget(key + 1, 0, 0);
    p->sem_mutex = semget(key + 2, 0, 0);
    p->p_shm = (shmhead_t *)shmat(p->shmid, NULL, 0);
    p->p_payload = (char *)p->p_shm + sizeof(shmhead_t);
  }
  return p;
}

void Operator_P(int key) {
  int semid = semget(key, 0, 0);
  struct sembuf buf[] = {{0, -1, 0}};
  semop(semid, buf, 1);
}

void Operator_V(int key) {
  int semid = semget(key, 0, 0);
  struct sembuf buf[] = {{0, 1, 0}};
  semop(semid, buf, 1);
}

void shmfifo_put(shmfifo_t *fifo, const void *buf, int *index) {
  int mutex = fifo->sem_empty;
  int empty = fifo->sem_empty;
  int full = fifo->sem_full;
  Operator_P(full);
  Operator_P(mutex);
  void *put_place = ((char *)fifo->p_payload) +
                    (fifo->p_shm->wr_index) * (fifo->p_shm->blksize);
  mempcpy(put_place, buf, fifo->p_shm->blksize);
  *index = (fifo->p_shm->wr_index);
  fifo->p_shm->wr_index = (fifo->p_shm->wr_index + 1) % (fifo->p_shm->blocks);
  // printf("write index is %d shm_addr is %p size:%d\n",(fifo->p_shm->wr_index + 1), put_place,fifo->p_shm->blksize);
  Operator_V(empty);
  Operator_V(mutex);
}

void shmfifo_get(shmfifo_t *fifo, const void *buf){
  int mutex = fifo->sem_mutex;
  int empty = fifo->sem_empty;
  int full = fifo->sem_full;
  Operator_P(empty);
  Operator_P(mutex);
  void *get_place = ((char *)fifo->p_payload) +
                    (fifo->p_shm->rd_index) * (fifo->p_shm->blksize);
  memcpy((void *)buf, (void *)get_place, fifo->p_shm->blksize);
  fifo->p_shm->rd_index = (fifo->p_shm->rd_index + 1) % fifo->p_shm->blocks;
  // printf("shminfo is %d fifo->p_shm->rd_index　is %d ====%p\n",fifo->p_shm->rd_index + 1, fifo->p_shm->rd_index, get_place);
  Operator_V(full);
  Operator_V(mutex);
}

void get_shmaddr(shmfifo_t *fifo, int rd_index, void **shm_addr)
{
    //通过消息队列获取共享内存块的地址，不需要信号量加锁.
    int index = rd_index % fifo->p_shm->blocks;
    printf("get_shmaddr index = %d\n",index);
    void *get_place = ((char *)fifo->p_payload) + rd_index * (fifo->p_shm->blksize);
    *shm_addr = get_place;
}

void shmfifo_destory(shmfifo_t *fifo) {
  shmdt(fifo->p_shm);
  free(fifo);
  fifo == NULL;
}

#ifdef __cplusplus
}
#endif
