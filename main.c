#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#define KEY 23545 

int create_sem(int count){
	int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
	
	semctl(semd, 0, SETVAL, count);
	return semd;
}

int view_sem(){
	int semd = semget(KEY,0,0);
	return semctl(semd, 0, GETVAL);
}

int rem_sem(){
	int semd = semget(KEY,0,0);
	return semctl(semd, 0, IPC_RMID);
}

void usage(){
	printf("USAGE ./control <-c N | -v | -r>");
	exit(1);
}


int main(int argc, char ** argv){
	//if (argc != 2){
	//	usage();
	//}
	printf("%s\n", argv[1]);	

	int ret;
	
	if ( !strcmp(argv[1], "-c") ){
		int value = atoi(argv[2]);
		ret = create_sem( value );
		printf("semaphore created: %d\nvalue set: %d\n", ret, value);
	}
	
	else if ( !strcmp(argv[1], "-v") ){
		ret = view_sem();
		printf("semaphore value: %d\n", ret);
		
	}

	else if ( !strcmp(argv[1], "-r") ){
		ret = rem_sem();
		printf("semaphore removed: %d\n", ret);
	}

	else {
		usage();
	}
}
