#include "Includes/preprocessor.h"

int main(int argc, char ** argv){

	hashtablecomp* htable = initCmdLine(maincmds);

	runCmdLine(htable);

	destroyHashTableComp(htable);

	
	return 0;
}
