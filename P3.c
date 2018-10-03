//P3 process
//This program takes as input the number of words and spaces that fit in a line and the words which fit
//and fully justifies the line

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int read_word_no, word_no, x_space_no, total_space_no, word_spaces, i, space_remainder, word_len;
	char byte, *word = NULL;
	
	do {
		scanf("%d", &word_no);
		if (word_no == 0) {
			break;
		}
		
		scanf ("%d", &x_space_no);
		
		//calculate extra spaces needed after a word
		if (word_no > 1) {
			total_space_no = x_space_no + (word_no - 1);
			word_spaces = total_space_no / (word_no - 1);
			space_remainder = total_space_no % (word_no - 1);
		}
		
		read_word_no = 0;
		
		//Read every word byte by byte
		do {
			word_len = 0;
			
			do {
				scanf("%c", &byte);
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
			
			if (word_len != 0) {
				//Terimnate word string
				word = (char *)realloc(word, (word_len + 1) * sizeof(char));
				if (word == NULL) {
					printf ("Problem in realloc\n");
					return 1;
				}
				word[word_len] = '\0';
				
				read_word_no ++;
				
				//Print the word and the spaces neede after it
				printf ("%s", word);
				
				if (read_word_no != word_no) {
					for (i = 0 ; i < word_spaces ; i ++) {
						putchar(' ');
					}
					if (space_remainder > 0) {
						putchar(' ');
						space_remainder --;
					}
				}
				
				//Free all dynamically allocated memory
				free (word);
				word = NULL;
			}
		} while (read_word_no < word_no);
		
		putchar('\n');
	}
	while (1);
	
	return 0;
}