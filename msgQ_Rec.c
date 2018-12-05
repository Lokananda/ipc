#include<sys/msg.h>
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#define MSGSZ 128

/*
 * Declare the message structure.
 */

typedef struct cmsg{
		int x;
		char c[20];
	}scmsg;
typedef struct msgbuf {
         long mtype;
         struct cmsg info;
         } message_buf;

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    long i;
    message_buf sbuf;
    size_t buf_length;	
    key = 1234;
	 if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }
    else 
     (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
     
    buf_length = sizeof(scmsg) ;

 
    for(i=0;i<3;i++)
		{
						
			if(msgrcv(msqid,&sbuf,buf_length,i+1,IPC_NOWAIT | MSG_NOERROR) <0 )
				{
					printf("message %ld receiving failed.\n",i+1);
				
				}
			else 
				{
					printf("message no. %d received with message: %s \n",sbuf.info.x, sbuf.info.c);
					//printf("%d",errno);
		
				}
			}
	
  
  return 0;
}

