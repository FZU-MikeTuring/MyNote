# 信号量相关操作



## 头文件

```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
```



## 需要的函数

```c
/*
创建或者打开信号量集
创建或打开的信号量集对应的键值
nsems表示需要创建的信号量的个数
 
*/
int semget(key_t key,int nsems,int flag);
/*
对信号量集的操作
可以选择打开p操作或者v操作
semid:信号量集的标识符。
semoparray[]:表示对信号量的操作集。
nops:表示操作集的个数。
*/
int semop(int semid,struct sembuf semoparray[],size_t nops);
/*
信号量集的控制
semid:信号量集的标识符
semnum:信号量集的下标
cmd:函数需要进行的操作，SETVAL表示将arg的值赋值给信号量
arg:配合cmd使用，根据cmd的值来赋值
*/
int semctl(int semid,int semnum,int cmd,union semun arg);
```



```c
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

// 联合体，用于semctl操作
union semun {
    int val;               // SETVAL用的值
    struct semid_ds *buf;  // IPC_STAT, IPC_SET用的缓冲区
    unsigned short *array; // GETALL, SETALL用的数组
};

int main() {
    int sem_id;
    union semun sem_arg;
    struct sembuf sem_op;
    
    // 创建信号量集（包含1个信号量）
    sem_id = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if(sem_id == -1) {
        perror("semget失败");
        exit(1);
    }
    
    // 初始化信号量值为1
    sem_arg.val = 1;
    if(semctl(sem_id, 0, SETVAL, sem_arg) == -1) {
        perror("semctl SETVAL失败");
        exit(1);
    }
    
    printf("信号量创建成功，ID: %d\n", sem_id);
    
    // P操作（等待）
    sem_op.sem_num = 0;     // 信号量编号
    sem_op.sem_op = -1;     // P操作，值减1
    sem_op.sem_flg = SEM_UNDO; // 进程退出时自动撤销操作
    
    if(semop(sem_id, &sem_op, 1) == -1) {
        perror("P操作失败");
    } else {
        printf("获取信号量成功\n");
    }
    
    // 临界区代码
    printf("进入临界区...\n");
    // ... 执行需要同步的操作
    printf("离开临界区...\n");
    
    // V操作（释放）
    sem_op.sem_op = 1;      // V操作，值加1
    if(semop(sem_id, &sem_op, 1) == -1) {
        perror("V操作失败");
    } else {
        printf("释放信号量成功\n");
    }
    
    // 删除信号量
    if(semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("删除信号量失败");
    } else {
        printf("信号量删除成功\n");
    }
    
    return 0;
}
```

