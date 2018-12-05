#include<sys/msg.h>
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

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
         scmsg info;
         } message_buf;

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    char c[4][20] = {"hello","hi","76123478"};
    key_t key;
    int i;
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
			sbuf.mtype = (long) i+1;
			sbuf.info.x = i+1;
			strcpy(sbuf.info.c, c[i]);
			//printf("%s",sbuf.info.c);
			
			if(msgsnd(msqid,&sbuf,buf_length,IPC_NOWAIT)<0)
				{
					printf("message %d sending failed.\n",i+1);
				
				}
			else printf("message %d sent.\n",i+1);
			}
	
  exit(0);
  return 0;
}
