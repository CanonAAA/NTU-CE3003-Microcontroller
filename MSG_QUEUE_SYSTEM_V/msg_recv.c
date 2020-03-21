/* Filename: msgq_recv.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define PERMS 0644
struct my_msgbuf {
   long mtype;
   char mtext[200];
};  //same buffer for receiving msg from msg Q

int main(void) {
   struct my_msgbuf buf;
   int msqid;
   int toend;
   key_t key;
   
	//we assume that the send was run first and hence the file is alr created
   if ((key = ftok("msgq.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }
   	//notice this call only gets and does not do IPC_CREAT like send because we assume send alr executed and hence the queue is alr there. 
   if ((msqid = msgget(key, PERMS)) == -1) { /* connect to the queue */
      perror("msgget");
      exit(1);
   }
   printf("message queue: ready to receive messages.\n");
   
   for(;;) { /* normally receiving never ends but just to make conclusion 
             /* this program ends wuth string of end */
      if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      printf("recvd: \"%s\"\n", buf.mtext);
      toend = strcmp(buf.mtext,"end"); //just a check if what we receive is end
      if (toend == 0)
      break;
   }
   printf("message queue: done receiving messages.\n");
   system("rm msgq.txt"); //rm the damn file because likely the send gonna exit first
   return 0;
}
