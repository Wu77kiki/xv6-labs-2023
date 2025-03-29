#include "kernel/types.h"
#include "user/user.h"

char* int_to_string(int n) {
    if (n == 0) { 
        char* result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    int len = 0;
    int tmp = n;
    while (tmp > 0) {
        len++;
        tmp /= 10;
    }
    // 分配内存（位数 + 结束符）
    char* result = (char*)malloc((len + 1) * sizeof(char));
    // 从低位到高位填充字符
    tmp = n;
    for (int i = len - 1; i >= 0; i--) {
        result[i] = (tmp % 10) + '0'; // 取最后一位并转换为字符
        tmp /= 10; // 移除最后一位
    }
    result[len] = '\0'; // 添加字符串结束符
    return result;
}

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    char buf[1];
    int n,m;
    if(fork() > 0) {
        m=write(p[1],"1",1);
        wait(0);
        if(m != 1){
            fprintf(2, "Pingpong error\n");
        }
        if(m == 1){
            fprintf(1, int_to_string(getpid()));
            fprintf(1, ": received pong\n");
        }
    } else { 
        n=read(p[0],buf,1);
        fprintf(1, int_to_string(getpid()));
        fprintf(1, ": received ping\n");
        if(n < 0){
            fprintf(2, "Pingpong error\n");
        }
    }   
   
    exit(0);
}