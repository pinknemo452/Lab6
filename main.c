#include<stdio.h>
#include<stdlib.h>
struct word_s {
	char* string;
	int length;
};
struct node_t  {
	char* value;
	struct node_t* left;
	struct node_t* right;
};
int getSize(char* array) {
	int stringsize = 0;
	while ((array[stringsize] != '\n') && (array[stringsize] != 0)) {
		stringsize++;
	}
	return stringsize;
}

void freemem(struct node_t* tree) {
	if (tree != NULL) {
		freemem(tree->left);
		freemem(tree->right);
		free(tree);
	}
}

void print_Tree(struct node_t* p, int level) {

	if (p)
	{
		print_Tree(p->left, level + 1);
		for (int i = 0; i < level; i++) printf("   ");
		printf("%d", level);
		for (int i = 0; i < getSize(p->value); i++) {
			printf("%c", p->value[i]);
		}
		printf("\n");
		print_Tree(p->right, level + 1);
	}
}

int maxDepth(struct node_t* tree)
{
	if (tree == NULL) return 0;
	return max(maxDepth(tree->left), maxDepth(tree->right)) + 1;
}

struct node_t* addnode(struct word_s x, struct node_t* tree,int wordcount) {
	if (x.length > 0) {
		if (tree == NULL) {
			tree = (struct node_t*)malloc(sizeof(struct node_t));
			if (tree) {
				tree->value = (char*)malloc((x.length + 1) * sizeof(char));
				if (tree->value) {
					for (int i = 0; i < x.length + 1; i++) {
						tree->value[i] = x.string[i];
					}
					tree->value[x.length] = 0;
					tree->left = NULL;
					tree->right = NULL;
				}
			}
		}
		else  if (x.length <= getSize(tree->value)) {
			tree->left = addnode(x, tree->left, wordcount);
		}
		else {
			tree->right = addnode(x, tree->right, wordcount);
		}
	}
	return(tree);
}

int main() {
	FILE *file = fopen("file.txt","r") ;
	char string[1000];
	fgets(string, 1000, file);
	int wordsize = 0,wordcount = 0;
	char* tmp = (char*)malloc(10);
	struct node_t* tree = NULL;
	struct word_s word = {NULL,0}; 
	for (int i = 0; i < getSize(string)+1; i++) {
		if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z')) {
			wordsize++;
		}
		else {
			wordcount++;
			word.length = wordsize;
			word.string = (char*)realloc(tmp,(word.length+1) * sizeof(char));
			if (word.string) {
				int k = 0;
				for (int j = i - word.length; j < i; j++) {

					word.string[k] = string[j];
					k++;
				}
				word.string[word.length] = 0;
				tree = addnode(word, tree,wordcount);
				word.length = 0;
				wordsize = 0;
				
			}
			
		}
	}
	int p = 0;
	free(word.string);
	printf("tree depth %d\n", maxDepth(tree)-1);
	print_Tree(tree, 0);
	freemem(tree);
	return 0;
}