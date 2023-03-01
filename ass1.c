#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#define MAX_WORD_LEN 23
#define MAX_PARA_LEN 10000
#define PARA_END 1
#define WORD_FND 2
#define TERM_PUNCT ".,;:!?"
#define NEEDS_DOTS ",;:"
#define PARA_SEPARATOR "\n\n"
#define BBOLD "**"
#define BBOLD_LEN (2*strlen(BBOLD))
#define DDOTS "..."
#define MAX_SNIPPET_LEN 30
#define MIN_SNIPPET_LEN 20
#define MAX_OUTPUT_LINE 72
#define MAX_TERMS 50
#define NO_MATCH (-1)

typedef char word_t[MAX_WORD_LEN+1];
int get_word(word_t w, int limit);
void print_para(word_t w);
int get_para(word_t w, int* is_EOF);

int main(int argc, char *argv[]) {
	word_t w = "";
	int is_EOF = 0;
	int count = 0;
	int length = 0;
	int match = 0;
	while(is_EOF == 0){
		length = get_para(w, &is_EOF);
		// printf("%d\n\n",length);
		count++;
		printf("======= Stage 1 [para %d; %d words]\n\n",count,length);
		printf("======= Stage 2 [para %d; %d words; %d matches]\n\n",count,length,match);
	}
	
	
	// print_para(w);
	
	return 0;
}

int get_word(word_t W, int limit) {
	int c;
	int count = 0;
	while ((c=getchar())!=EOF && !isalnum(c)) {
		if(c == '\n'){
			count++;
		}
	}

	if (count == 2) {
		*W = c;
		W += 1;
		return PARA_END;
	}

	if (c==EOF) {
		return EOF;
	}
	/* ok, first character of next word has been found */
	if (strlen(W) > 0){
		W += 1;
	}

	*W = c;
	W += 1;
	limit -= 1;
	while (limit>0 && (c=getchar())!=EOF && isalnum(c)) {
		/* another character to be stored */
		*W = c;
		W += 1;
		limit -= 1;
	}
	/* take a look at that next character, is it a sensible trailing
	   punctuation? */
	if (strchr(TERM_PUNCT, c) && (limit>0)) {
		/* yes, it is */
		*W = c;
		W += 1;
		limit -= 1;
	}

	/* now close off the string */
	*W = '\0';
	return WORD_FND;
}

void print_para(word_t w){
	while (get_word(w, MAX_WORD_LEN) != EOF) {
		printf("%s ", w);
	}
}

int get_para(word_t w, int* is_EOF){
	int length = 0;
	while (1) {
		int result = get_word(w, MAX_WORD_LEN);
		if(result == EOF){
			*is_EOF = 1;
			return length;
		}
		if(result == PARA_END){
			return length;
		}
		if(result == WORD_FND){
			// printf("%s ", w);
			strcpy(w,"");
			length++;
		}
		
	} 
	
}