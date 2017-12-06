#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 12345

int create_sem(int count){
	int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0600);
	semctl(semd, 0, SETVAL, count);
	return semd;
}

int view_sem(){
	return semctl(KEY, 0, GETVAL);
}

int rem_sem(){
	return semctl(KEY, 0, IPC_RMID);
}

void usage(){
	perror("USAGE ./control <-c N | -v | -r>");
}

int main(int argc, char ** argv){
	//if (argc != 2){
	//	usage();
	//}
	
	int ret;
	
	if ( argv[1] == "-c"){
		ret = create_sem( atoi(argv[2]) );
		printf("semaphore created: %d\n value set: 0\n", ret);
	}
	
	else if (argv[1] == "-v"){
		ret = view_sem();
		printf("semaphore value: %d\n", ret);
		
	}

	else if (argv[1] == "-r"){
		ret = rem_sem();
		printf("semaphore removed: %d\n", ret);
	}

	else {
		usage();
	}
}
