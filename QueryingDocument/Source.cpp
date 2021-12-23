#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char*** kth_paragraph(char**** document, int k) {
	return *(document + k - 1);
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) {
	char*** paragraph;

	paragraph = kth_paragraph(document, m);

	return *(paragraph + k - 1);
}

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
	char** sentence;

	sentence = kth_sentence_in_mth_paragraph(document, m, n);
	
	return *(sentence + k - 1);
}

char**** add_paraph(char**** document, char*** paraph, int n_paraphs) {
	document = (char****)realloc(document, (n_paraphs + 1) * sizeof(char***));
	*(document + n_paraphs) = paraph;
	return document;
}

char*** add_sentence(char*** paraph, char **sentence, int n_sentences) {
	paraph = (char***)realloc(paraph, (n_sentences + 1) * sizeof(char**));

	*(paraph + n_sentences) = sentence;

	return paraph;
}

char** add_word(char** sentence, char* word, int n_words) {
	sentence = (char**)realloc(sentence, (n_words + 1) * sizeof(char*));
	int len = strlen(word);
	char *word_copy = (char*)malloc((len + 1) * sizeof(char));
	strncpy(word_copy, word, len + 1);
	*(sentence + n_words) = word_copy;

	return sentence;
}

char**** get_document(char* text) {
	char**** document = NULL;
	char*** curr_paraph = NULL;
	char** curr_sentence = NULL;
	char* curr_word;
	int n_paraphs = 0, n_words = 0, n_sentences = 0;

	curr_word = (char *)malloc(MAX_CHARACTERS * sizeof(char));
	int i = 0;
	char c;
	for (; c = *text; text++) {
		if (c == ' ') {
			if (i != 0) { /*ignore empty words (ex: space after '.')*/
				curr_word[i] = '\0';
				curr_sentence = add_word(curr_sentence, curr_word, n_words);
				n_words++;
				i = 0;
			}
		}
		else if (c == '.') {

			curr_word[i] = '\0';
			curr_sentence = add_word(curr_sentence, curr_word, n_words);
			i = 0;
			curr_paraph = add_sentence(curr_paraph, curr_sentence, n_sentences);
			n_sentences++;
			n_words = 0;
			curr_sentence = NULL;
		}
		else if (c == '\n') {
			/*Word and sentence has already been added*/
			document = add_paraph(document, curr_paraph, n_paraphs);
			n_paraphs++;
			n_sentences = 0;
			curr_paraph = NULL;
		}
		else {
			curr_word[i++] = c;
		}
	}
	

	/*Last word and sentence has already been added*/
	document = add_paraph(document, curr_paraph, n_paraphs);
	
	free(curr_word);

	return document;
}


char* get_input_text() {
	int paragraph_count;
	scanf("%d", &paragraph_count);

	char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
	memset(doc, 0, sizeof(doc));
	getchar();
	for (int i = 0; i < paragraph_count; i++) {
		scanf("%[^\n]%*c", p[i]);
		strcat(doc, p[i]);
		if (i != paragraph_count - 1)
			strcat(doc, "\n");
	}

	char* returnDoc = (char*)malloc((strlen(doc) + 1) * (sizeof(char)));
	strcpy(returnDoc, doc);
	return returnDoc;
}

void print_word(char* word) {
	printf("%s", word);
}

void print_sentence(char** sentence) {
	int word_count;
	scanf("%d", &word_count);
	for (int i = 0; i < word_count; i++) {
		printf("%s", sentence[i]);
		if (i != word_count - 1)
			printf(" ");
	}
}

void print_paragraph(char*** paragraph) {
	int sentence_count;
	scanf("%d", &sentence_count);
	for (int i = 0; i < sentence_count; i++) {
		print_sentence(*(paragraph + i));
		printf(".");
	}
}

int main()
{
	char* text = get_input_text();
	char**** document = get_document(text);

	int q;
	scanf("%d", &q);

	while (q--) {
		int type;
		scanf("%d", &type);

		if (type == 3) {
			int k, m, n;
			scanf("%d %d %d", &k, &m, &n);
			char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
			print_word(word);
		}

		else if (type == 2) {
			int k, m;
			scanf("%d %d", &k, &m);
			char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
			print_sentence(sentence);
		}

		else {
			int k;
			scanf("%d", &k);
			char*** paragraph = kth_paragraph(document, k);
			print_paragraph(paragraph);
		}
		printf("\n");
	}

	return 0;
}