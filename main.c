#include "Includes/preprocessor.h"
void sigint_handler(int signal){
	
}
int main(int argc, char ** argv){
	
	signal(SIGINT,sigint_handler);
	printf("Hello! Welcome to cardDB!!!!! Insert the 'showallcmds' command for help!!!!\n");
	hashtablecomp* htable = initCmdLine(maincmds);

	runCmdLine(htable);

	destroyHashTableComp(htable);

	
	return 0;
}
