# 共享内存(shm)

# 信号量相关操作(sem)



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

# 网络编程C

## 函数

### 创建套接字

```c
#include<sys/types.h>
#include<sys/socket.h>
int socket(int family,int type,int protocol);
/*
family指明协议族(PF_UNIIX,PF_INET==AF_INET,PF_INET6=AF_INET6,AF_ROUTE)

type知名通信字节流类型，SOCK_STREAM(TCP方式)、SOCK_DGRAM(UDP方式)、SOCK_RAW（原始套接口）
	SOCK_PACKET(支持数据链路访问)等

一般protocol设置为0，除非用在原始套接口上

返回值是socket的id
*/
```

### 释放套接字

```c
close(sockfd);
/*
sockfd刚创建的套接字编号
*/
```

### 绑定端口

```c
#include<sys/types.h>
#include<sys/socket.h>
int bind(int sockfd,const struct sockaddr*my_addr,socklen_t addrlen);
/*
sockfd表示已创立的套接字编号
my_addr指向一个sockaddr结构体指针
addrlen表示my_addr结构的长度，可以用sizeof函数来获得

成功返回0，失败返回-1
*/
```

### 等待监听函数

```c
#include<sys/socket.h>
int listen(int sockfd,int backlog);
/*
sockfd表示已创立的套接字编号
backlog表示能够同时处理的最大连接请求数目，如果超过这个数目，客户端将受到ECONNREFUSED拒绝连接错误
成功返回0 失败返回-1

listen函数只适用于SOCK_STREAM或SOCK_SEQPACKET的socket类型
如果socket为AF_INET，则backlog的最大值可设置为128
*/
```

### 接受连接函数

```c
#include<sys/types.h>
#include<sys/socket.h>
int accept(int sockfd,struct sockaddr*addr,socketlen_t*addrlen);
/*
sockfd表示已创立的套接字编号
addr是一个sockaddr结构体类型指针，系统将remote host的信息保存到这个指针指向的结构体中
addrlen表示sockaddr的内存长度，可用sizeof得到

成功返回一个新的socket编号，addr会保存来者的信息，失败返回-1
*/
```

### 请求连接函数

```c
#include<sys/types.h>
#include<sys/socket.h>
int connect(int sockfd,const struct sockaddr*serv_addr,int addrlen);
/*
sockfd表示已经建立的socket
serv_addr存储远程服务器的ip和端口号
addrlen表示sockaddr的内存长度，可用sizeof函数获取

成功返回0，失败返回-1
*/
```

### 数据发送函数

```c
#include<sys/types.h>
#include<sys/socket.h>
int send(int sockfd,const void*msg,int len,unsigned int flags);
/*
sockfd表示已经建立的socket，这个sockfd要是accept得到的那个newsockfd
msg是需要发送数据的指针
len表示需要发送数据的长度，可以用sizeof函数来取得
flags一般设置为0

成功则返回已经发送的字符数，失败则返回-1
*/
```

### 数据接收函数

```c
#include<sys/types.h>
#include<sys/socket.h>
int recv(int sockfd,void *buf,int len,unsigned int flags);
/*
sockfd表示已经建立的socket
buf是一个指针，指向一个数组，接收的数据会保存到这个数组中
len表示数组的长度，可以用sizeof来取得
flags一般设置为0

成功则返回接收的字符数，失败返回-1
*/
```

# 文件I/O操作流



## 函数

### 打开文件

```c
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int open(const char*pathname,int flags);
int open(const char*pathname,int flags,mode_t mdoe);

/*
pathname是文件的路径， 可以是相对路径也可以是绝对路径
flags用于描述文件的打开方式，可以用逻辑或同时设置多个参数
flags=O_RDWR|O_APPEND可以表示以读写的方式打开，在文件末尾开始写文件
O_CREAT：表示如果文件不存在则创建这个文件，此时需要第三位mode_t来设置文件的权限
O_RDONLY
O_WRONLY
O_TRUNC:如果文件存在，而且为只读或只写的方式打开，则将其长度截短为0
mode=S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH
00777
用户读、写、执行，组读、执行，其他用户读、执行

成功返回文件描述符，失败返回-1
*/
```

### 创建文件

```c
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int creat(const char*pathname,mode_t mode);
/*
参数含义同上

成功则返回文件的描述符，出错则返回-1
*/
```

### 关闭文件

```c
#include<unistd.h>
int close(int fd);
/*
fd需要关闭的文件描述符

一个文件可能有多个引用。文件描述中有一个引用计数器。当文件多一个描述时，引用计数器+1，当减少一个引用时，引用计数器-1。当文件的引用变为0的时候，系统调用close会释放该文件描述符，也将释放该文件所占的描述表项目

成功返回0，失败返回-1
*/
```

### 读文件

```c
#include<unistd.h>
ssize_t read(int fd,void*buf,size_t count);
/*
fd表示文件的描述符
buf是指向缓冲区的指针，存放要读取到终端的数据
count表示本次操作要读取数据的字节数

成功返回读到的字节数，若已到达文件的尾端返回0，出错返回-1
*/
```

### 写文件

```c
#include<unistd.hy>
ssize_t write(int fd,void*buf,size_t count);
/*
fd表示要写入的文件描述符
buf将要写入文件的数据的缓冲区指针
count写入的字符数,sizeof(buf)
*/
```

