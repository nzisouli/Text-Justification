//P2 process
//This program takes as input a text and calculates how many words and spaces
//fit in a line in order to be fully justified

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char *argv[]) {
	int line_size, word_len = 0, total_word_len = 0, word_no = 0, i = 1, x_space_no, if_fits = 1, first_time = 1;
	//if_fits: 1 if the word fits elses 0
	//first_time: 1 if the first word of next line else 0
	char *word = NULL, **words = NULL;//words has the words that fit in a line
	char byte, *last_word;

	//Calculate lebgth of the line given from the command line
	line_size = atoi(argv[1]);
	
	do {k
		if (if_fits == 0) {
			first_time = 0;
			word_no = 1;
			words = (char **)realloc(words, word_no * sizeof(char *));
			if (words == NULL) {
				printf ("Problem in realloc 0\n");
				return 1;
			}
			words[word_no - 1] = last_word;
			
			total_word_len = word_len;
		}
		
		//for every line read every word, find its length and add it to the overall length of the words
		do {
			//read word byte by byte
			word_len = 0;
			do {
				byte = getchar();
				if (isspace(byte) == 0 && byte != EOF) {
					word_len ++;
					word = (char *)realloc(word, word_len * sizeof(char));
					if (word == NULL) {
						printf ("Problem in realloc 1\n");
						return 1;
					}
					word[word_len - 1] = byte;
				}
			}
			while (isspace(byte) == 0 && byte != EOF);
			
			//Terminate word string if it fits put it to words matrix
			if (word_len != 0) {
				word = (char *)realloc(word, (word_len + 1) * sizeof(char));
				if (word == NULL) {
					printf ("Problem in realloc 2\n");
					return 1;
				}
				word[word_len] = '\0';
				
				if (total_word_len + (word_len + !first_time) <= line_size) {
					if_fits = 1;
					word_no ++;
					words = (char **)realloc(words, word_no * sizeof(char *));
					if (words == NULL) {
						printf ("Problem in realloc 3\n");
						return 1;
					}
					words[word_no - 1] = word;
					word = NULL;
					
					total_word_len = total_word_len + (word_len + !first_time);
				}
				else {
					if_fits = 0;
					last_word = word;
					word = NULL;
				}
			}
			first_time = 0;
		}
		while (byte != EOF && if_fits == 1 && total_word_len <= line_size);
		
		x_space_no = line_size - total_word_len;
		
		//Print number of words and spaces for the current line
		printf("%d %d ", word_no, x_space_no);
		
		for (i = 0 ; i < word_no ; i ++) {
			printf ("%s ", words[i]);
			free (words[i]);
			words[i] = NULL;
		}
		
		total_word_len = 0;
		first_time = 1;
	}
	while (byte != EOF);
	
	if (if_fits == 0 && word_len != 0) {
		word_no = 1;
		total_word_len = word_len;
		x_space_no = line_size - total_word_len;
		
		printf("%d %d %s ", word_no, x_space_no, last_word);
	}
	
	printf("0");
	
	//Free all dynamically allocated memory
	free(word);
	free(words);
	
	return 0;
}