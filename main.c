#include<stdio.h>
#include<stdlib.h>
struct word_s {
	char* string;
	int length;
};
struct node_t  {
	char* value;
	struct node_t *left;
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
		free( tree);
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
int treeDepth(struct node_t* tree,int* co) {
	
	if (tree != NULL) {
		treeDepth(tree->left,co);
		*co +=1;
	}
	return 0;
}
int maxDepth(struct node_t* tree)
{
	if (tree == NULL) return 0;
	return max(maxDepth(tree->left), maxDepth(tree->right)) + 1;
}

void treeprint(struct node_t* tree) {
	if (tree != NULL) { //Пока не встретится пустой узел
		for (int i = 0; i < getSize(tree->value); i++) {
			printf("%c", tree->value[i]);
		}
		printf("\n");
		treeprint(tree->left); //Рекурсивная функция для левого поддерева
		//printf("	");
		treeprint(tree->right); //Рекурсивная функция для правого поддерева
	}
}
struct node_t* addnode(struct word_s x, struct node_t* tree,int wordcount) {
	//printf("first %c", x.string[0]);
	if (tree == NULL) { // Если дерева нет, то формируем корень
		tree = (struct node_t*)malloc(sizeof(struct node_t)); // память под узел
		if (tree) {
			tree->value = (char*)malloc((x.length + 1) * sizeof(char));   // поле данных
			if (tree->value) {
				//printf("Addnode\n");
				for (int i = 0; i < x.length + 1; i++) {
					tree->value[i] = x.string[i];
					//printf("%c", tree->value[i]);
				}
				tree->value[x.length] = 0;
				//printf("\n");
				tree->left = NULL;
				tree->right = NULL; // ветви инициализируем пустотой
			}
		}
	}
	else  if (x.length <= getSize(tree->value)) {   // условие добавление левого потомка
		tree->left = addnode(x, tree->left,wordcount);
	}
	else  {  // условие добавление правого потомка		
		tree->right = addnode(x, tree->right,wordcount);
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
			//printf("");
			wordcount++;
			word.length = wordsize;
			//printf("\n%d\n", word.length);
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
	treeDepth(tree, &p);
	printf("tree depth %d\n", maxDepth(tree)-1);
	print_Tree(tree, 0);
	//treeprint(tree);
	freemem(tree);
	return 0;
}