#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    key_t thiskey;
    int *roll;
    int shmid,rollnum;
    pid_t stud_id;
    uid_t owner;
    //    key_t ftok(const char *pathname, int proj_id);
    thiskey = ftok("/home/sandipan/Academics/semester_6/Operating_systems/teacher.c", 1);
    shmid = shmget(thiskey, 3*sizeof(int), IPC_CREAT|0777);
    if(shmid==-1)
    {
        perror("shmget() failed");
        return -1;
    }


    printf("\nRespond to your roll call: ");
    scanf("%d",&rollnum);
    //    void *shmat(int shmid, const void *shmaddr, int shmflg);
    roll = (int*)shmat(shmid, NULL, 0);

    if((*roll)==-1)
    	{
            
            *(roll+1) = getpid();
            *(roll+2) = getuid();
            *roll = rollnum;
        }
	//    int shmdt(const void *shmaddr);
    shmdt(roll);

    return 0;
}