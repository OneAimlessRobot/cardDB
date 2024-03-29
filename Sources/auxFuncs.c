#include "../Includes/preprocessor.h"
#include "../Includes/auxFuncs.h"


//char whitespacechars[]=  {'\n',' ','\r','\f','\t','\v'};
char whitespacechars[]=  {'\n',' ','\r','\f','\t','\v'};
double genRanddouble(double min, double max){

    if (max < min) {
        fprintf(stderr, "Error: max must be greater than or equal to min\n");
        return 0.0f;
    }

    // Generate a random double between 0 and 1
    double random = ((double)rand() / RAND_MAX);

    // Scale and shift the random value to fit within the desired range
    return (random * (max - min)) + min;

}

void removeSpaceChars(char* buff, u_int64_t length){

	for(u_int64_t i=0;i<length&&length>0;i++){

		if(buff[i]==' '){

			buff[i]='_';
		}

	}

}
void removeUnderscoreChars(char* buff, u_int64_t length){

	for(u_int64_t i=0;i<length&&length>0;i++){

		if(buff[i]=='_'){

			buff[i]=' ';
		}

	}

}
int genRandInt(int min, int max) {
    if (max < min) {
        fprintf(stderr, "Error: max must be greater than or equal to min\n");
        return 0;
        }

    // Generate a random integer between min and max
    return (rand() % (max - min + 1)) + min;
}


char* randStr(int size){

        char* result= malloc(size+2);
        memset(result,0,size+2);
        for(int i=0;i<size;i++){

                result[i]=(char)genRandInt((int)97,(int)112);

        }
	result[size]=';';
	result[size+1]=0;
        return result;



}

char** randStrArr(int sizeOfStrs,int size){

	char** result= malloc(sizeof(char*)*size);

	for(int i=0;i<size;i++){

		result[i]=randStr(sizeOfStrs);

	}

	return result;


}

void freeStrArr(char** arr,int size){
	if(!arr){

		return;

	}
	
	for(int i=0;i<size;i++){
		if(arr[i]){
		free(arr[i]);
		}
	}

	free(arr);


}

int* getRandIntArr(int min,int max,int size){

	int* result= malloc(sizeof(int)*size);
	for(int i=0;i<size;i++){

		result[i]=genRandInt(min,max);
	}
	return result;

}

void swap(void** var1, void** var2){

void* tmp=*var1;
*var1=*var2;
*var2=tmp;




}


int64_t min(int64_t arg1, int64_t arg2){

	if(arg1<arg2){

		return arg1;

	}
	return arg2;


}
