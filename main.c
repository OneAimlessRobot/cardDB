#include "Includes/preprocessor.h"
#define PROGRAMPATHAUX "/home/oar_X_I/cardDB"
#define RESOURCES_PATH PROGRAMPATHAUX "/resources"
#define CARDS_PATH RESOURCES_PATH "/useable.txt"

int main(int argc, char ** argv){

	FILE *testCard= fopen(CARDS_PATH,"r");
	printf("%s\n",CARDS_PATH);
	card* collectible= fscanCard(testCard);
	char* strCard=printPrettyCard(collectible);
	printf("%s\n",strCard);
	free(strCard);
	destroyCard(&collectible);
	fclose(testCard);


	return 0;
}
