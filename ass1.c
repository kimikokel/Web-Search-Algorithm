/* Program to generate term-biased snippets for paragraphs of text.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2022, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Kuan Pui Leong 1289672
   Dated:     09/01/2023

*/

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

int main(int argc, char *argv[]) {
	word_t w;
	while (get_word(w, MAX_WORD_LEN) != EOF) {
		printf("%s\n", w);
	}
	
	return 0;
}

int get_word(word_t W, int limit) {
	int c;
	/* first, skip over any non alphanumerics */
	while ((c=getchar())!=EOF && !isalnum(c)) {
	}
	if (c==EOF) {
		return EOF;
	}
	/* ok, first character of next word has been found */
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