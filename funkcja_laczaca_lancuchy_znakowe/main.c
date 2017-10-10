#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * my_own_strcat(char firstword[], char secondword[]){
	char *joinWord;
	int i, z=0;
	joinWord = (char *)malloc(sizeof(char *) * (strlen(firstword) + strlen(secondword) + 1));
	for(i=0,z;i<strlen(firstword);i++,z++){
		joinWord[z] = firstword[i];
	}
	for(i=0,z;i<strlen(secondword);i++,z++){
		joinWord[z] = secondword[i];
	}
	joinWord[z] = '\0';
	return joinWord;
}

int main(){
	char *joinWord = my_own_strcat("Zero", "Death!");
	puts(joinWord);
	free(joinWord);
	return 0;
}
