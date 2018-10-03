//P1 process
//This program reads a text, finds its words and prints them with a space between them

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	char *word = NULL, byte;
	int word_len = 0;
	
	do {
		//Reads every word byte by byte
		do {
			byte = getchar();
			if (isspace(byte) == 0 && byte != EOF) {
				word_len ++;
				word = (char *)realloc(word, word_len * sizeof(char));
				if (word == NULL) {
					printf ("Problem in realloc\n");
					return 1;
				}
				word[word_len - 1] = byte;
			}
		}
		while (isspace(byte) == 0 && byte != EOF);
		
		//Terminates the string with the word and prints it
		if (word_len != 0) {
			word = (char *)realloc(word, (word_len + 1) * sizeof(char));
			if (word == NULL) {
				printf ("Problem in realloc\n");
				return 1;
			}
			word[word_len] = '\0';
			
			printf ("%s ", word);
		}
		
		//Free all dynamicaly allocated memory and initializes word_len
		free (word);
		word = NULL;
		word_len = 0;
	}
	while (byte != EOF);
	
	
	return 0;
}
