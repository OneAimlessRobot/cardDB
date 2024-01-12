#ifndef ARTIFACT_H
#define ARTIFACT_H
#define ARTSMALLFIELDSIZE 128
#define ARTMIDFIELDSIZE  750
#define ARTLARGEFIELDSIZE 5000
typedef enum artifactindex {
	
	ARTPIECE=1,
	JOURNAL=2


}artifactindex;

typedef enum artpieceindex {
	PHRASE=1,
	TEXT=2,
	MUSICTRACK=3,
	MUSICALBUM=4
	

}artpieceindex;

typedef struct musictrack{

	char title[ARTMIDFIELDSIZE+1],genre[ARTSMALLFIELDSIZE+1],desc[ARTLARGEFIELDSIZE+1];


}musictrack;
typedef struct text{

	
	char title[ARTMIDFIELDSIZE+1],desc[ARTLARGEFIELDSIZE+1];


}text;
typedef struct phrase{

	
	char desc[ARTMIDFIELDSIZE+1];


}phrase;
typedef struct musicalbum{
	
	u_int64_t numOfTracks;
	char title[ARTMIDFIELDSIZE+1];
	DListWComp* trackList;

}musicalbum;

typedef struct journal{
	u_int64_t numOfTexts;
	char intro[ARTLARGEFIELDSIZE+1];
	DListWComp* textList;
	
}journal;










typedef union untypedartpiece{
	struct musictrack track;
	struct musicalbum album;
	struct text composition;
	struct phrase quote;
}untypedartpiece;












typedef struct artpiece{
	
	artpieceindex type;
	union untypedartpiece contents;

}artpiece;

typedef union untypedartifact{

	struct artpiece artobject;
	struct journal diary;

}untypedartifact;















typedef struct artifact{
	artifactindex type;
	union untypedartifact object;

}artifact;

int compareArtifacts(void* arg1,void* arg2);
extern comparator artCompare;

/*Falta:
	(FAZER ISTO TUDO NO HEADER PRIMEIRO PARA SER MAIS FACIL. DEPOIS DEIXAR CABEÇALHOS PARA TRAS
	ASSIM COMO DECLARACOES. METER FUNCOES ESTATICAS NO FICHEIRO '.c'. Ai de mim daqui a uns
	tempos...)
	
	funcao para triar entre o tipo de artefacto (objeto artistico vs journal).
	vai ter um switch que vai receber o inteiro vindo deste funcao assim como a stream.
	la, se for journal, vai direto para a funcao parseJournal.
	Se for objeto artistico, vai para uma...

	funcao de parsing de objetos artisticos
	em que lhe e passado o tipo de objeto artistico com scanf na stream
	que tem um switch que seleciona o parsing efetuado com base no
	tipo de objeto artistico.

	Isso e enfiado num buffer criado com malloc, escrito na arvore
	depois siga proximo.


*/
BSTreeComp* genArtifactTreeFromStream(FILE* stream);


void printArtifact(FILE* stream,artifact* obj);

void destroyArtifactTree(BSTreeComp* tree);

void printArtifactTree(FILE*stream,BSTreeComp* tree);

#endif
