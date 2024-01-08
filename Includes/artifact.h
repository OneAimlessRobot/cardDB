#ifndef ARTIFACT_H
#define ARTIFACT_H
#define ARTSMALLFIELDSIZE 128
#define ARTMIDFIELDSIZE  750
#define ARTLARGEFIELDSIZE 2000
typedef enum artifactindex {
	
	ARTPIECE=1;
	JOURNAL=2;


}artifactindex;

typedef enum artpieceindex {
	PHRASE=1;
	TEXT=2;
	MUSICTRACK=3;
	MUSICALBUM=4;
	

}artpieceindex;

typedef struct musictrack{

	char title[ARTSMALLFIELDSIZE+1],genre[ARTSMALLFIELDSIZE+1],desc[ARTLARGEFIELDSIZE+1];


}musictrack;
typedef struct text{

	
	char title[ARTSMALLFIELDSIZE+1],desc[ARTLARGEFIELDSIZE+1];


}text;
typedef struct phrase{

	
	char desc[ARTMIDFIELDSIZE+1];


}phrase;
typedef struct musicalbum{

	DListWComp* musicTrackList;

}musicalbum;
typedef union artpiece{
	musictrack track;
	musicalbum album;
	text composition;
	phrase quote;
}artpiece;
typedef struct journal{

	DListWComp* textList;
	
}journal;

typedef union artifact{

	artpiece artobject;
	journal diary;

}artifact;
#endif
