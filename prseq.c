#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

#define SEM_NAME "/VaibhavMishra.mutex"

int main(int argc, char const *argv[]) {
  int max = 0, i =0;
  sem_t *sem;
  sem_t *sem2;
  sem_t *sem3;
  pid_t  pid, pid2;
  sem = sem_open(SEM_NAME, O_CREAT, O_RDWR, 0);
  sem_unlink(SEM_NAME);
  if (sem==SEM_FAILED) {
    printf("%s sem_open failed!", SEM_NAME);
    return (-1);
  }
  sem2 = sem_open(SEM_NAME, O_CREAT, O_RDWR, 1);
  sem_unlink(SEM_NAME);
  if (sem2==SEM_FAILED) {
    printf("%s sem_open failed!", SEM_NAME);
    return (-1);
  }
  sem3 = sem_open(SEM_NAME, O_CREAT, O_RDWR, 0);
  sem_unlink(SEM_NAME);
  if (sem2==SEM_FAILED) {
    printf("%s sem_open failed!", SEM_NAME);
    return (-1);
  }
  printf("Enter the maximum number\n");
  scanf("%d", &max);
  pid = fork();
  if(pid == 0)
  {
    pid2 = fork();
    if(pid2 == 0)
    {
      i = 0;
      for (; i <= max; ) {
        sem_wait(sem2);
        printf("pid %d done and value is %d\n", getpid(),i);
        i = i + 3;
        sem_post(sem3);
      }
    }
    else{
      i = 2;
        for (; i <= max; ) {
        sem_wait(sem);
        printf("pid %d done and value is %d\n", getpid(),i);
        i = i + 3;
        sem_post(sem2);
      }
    }
  }
  else
  {
      i = 1;
      for (; i <= max; ) {
      sem_wait(sem3);
      printf("pid %d done and value is %d\n", getpid(),i);
      i = i + 3;
      sem_post(sem);
    }
  }
  wait(NULL);
  return 0;
}
