#include "Includes/preprocessor.h"
#define PROGRAMPATHAUX "/home/oar_X_I/cardDB"
#define RESOURCES_PATH PROGRAMPATHAUX "/resources"
#define CARDS_PATH RESOURCES_PATH "/useable.txt"
#define CARDS_DUMP_PATH RESOURCES_PATH "/dump.txt"

int main(int argc, char ** argv){

	
	for(int i=0;i<5;i++){
	int fdtest= open(CARDS_PATH,O_RDWR | O_CREAT | O_APPEND,0777);
	FILE* testCard= fdopen(fdtest,"a+");
	if(!testCard||fdtest==-1){
		close(fdtest);
		perror("Ficheiro nao aberto no loop!!!\n");
		exit(-1);
	}
	int fddump= open(CARDS_DUMP_PATH,O_RDWR | O_CREAT | O_TRUNC,0777);
	FILE*dumpCard= fdopen(fddump,"a+");
	if(!dumpCard||fddump==-1){
		fclose(testCard);
		perror("Ficheiro nao aberto no loop!!!\n");
		exit(-1);
	}
	fseek(testCard,0,SEEK_SET);
	card* collectible= fscanCard(testCard);
	char* strCard=printPrettyCard(collectible);
	printf("%s\n",strCard);
	free(strCard);
	fprintCard(collectible,dumpCard);
	destroyCard(&collectible);
	
	fclose(dumpCard);
	fclose(testCard);
	
	fdtest= open(CARDS_PATH,O_RDWR | O_CREAT | O_APPEND,0777);
	testCard= fdopen(fdtest,"a+");
	if(!testCard||fdtest==-1){
		close(fdtest);
		perror("Ficheiro nao aberto no loop!!!\n");
		exit(-1);
	}
	fddump= open(CARDS_DUMP_PATH,O_RDWR | O_CREAT | O_TRUNC,0777);
	dumpCard= fdopen(fddump,"a+");
	if(!dumpCard||fddump==-1){
		fclose(testCard);
		perror("Ficheiro nao aberto no loop!!!\n");
		exit(-1);
	}
	fseek(dumpCard,0,SEEK_SET);
	collectible= fscanCard(testCard);
	strCard=printPrettyCard(collectible);
	printf("%s\n",strCard);
	free(strCard);
	fprintCard(collectible,dumpCard);
	destroyCard(&collectible);
	
	fclose(dumpCard);
	fclose(testCard);
	}
	
	return 0;
}
