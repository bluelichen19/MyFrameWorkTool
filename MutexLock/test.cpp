#include "BlueMutexLock.h"
void* func1(void* p)
{
    int i;
    for(i=0;i<5;i++)
        printf("func1 i is %d\n",i);
    return 0;
}
void* func2(void* p)
{
    int i;
    for(i=0;i<5;i++)
        printf("func2 i is %d\n",i);
    return 0;
}
void* func3(void* p)
{
    int i;
    for(i=0;i<5;i++)
        printf("func3 i is %d\n",i);
    return 0;
}
int main(int argc,char* argv[])
{
    int ret = 0;
    pthread_t pthread_key1;
    pthread_t pthread_key2;
    pthread_t pthread_key3;
    pthread_create(&pthread_key1,NULL,&func1,NULL);
    pthread_create(&pthread_key2,NULL,&func2,NULL);
    pthread_create(&pthread_key3,NULL,&func3,NULL);
    pthread_join(pthread_key1,NULL);
    pthread_join(pthread_key2,NULL);
    pthread_join(pthread_key3,NULL);
    return 0;
}
