#include "Includes/preprocessor.h"
#define PROGRAMPATHAUX "/home/oar_X_I/cardDB"
#define RESOURCES_PATH PROGRAMPATHAUX "/resources"
#define CARDS_PATH RESOURCES_PATH "/useable.txt"
#define CARDS_DUMP_PATH RESOURCES_PATH "/dump.txt"

int main(int argc, char ** argv){

	
	int fdtest= open(CARDS_PATH,O_RDWR | O_CREAT | O_APPEND,0777);
	if(fdtest==-1){
		
		perror("Ficheiro não aberto!!!!!\n");
		exit(-1);
	}
	int fddump= open(CARDS_DUMP_PATH,O_RDWR | O_CREAT | O_TRUNC,0777);
	
	if(fddump==-1){
		
		perror("Ficheiro não aberto!!!!!\n");
		close(fdtest);
		exit(-1);
	}
	FILE *testCard= fdopen(fdtest,"a+");
	FILE *dumpCard= fdopen(fddump,"w+");
	for(int i=0;i<1;i++){
	fseek(testCard,0,SEEK_SET);
	card* collectible= fscanCard(testCard);
	char* strCard=printPrettyCard(collectible);
	printf("%s\n",strCard);
	free(strCard);
	fprintCard(collectible,dumpCard);
	fsync(fddump);
	destroyCard(&collectible);

	card* collectible2= fscanCard(dumpCard);
	char* strCard2=printPrettyCard(collectible2);
	printf("%s\n",strCard2);
	free(strCard2);
	
	fprintCard(collectible2,testCard);
	fsync(fdtest);
	destroyCard(&collectible2);
	
	}
	fclose(testCard);
	fclose(dumpCard);
	close(fdtest);
	close(fddump);

	return 0;
}
