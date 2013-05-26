#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree
{
	char info[20];
	int repeats;
	struct tree *left;
	struct tree *right;

}tree;

void GetString(char * string)
{
	fgets(string,20,stdin);
}

int GetInt(int * number)
{
	char buffer[20];
	fgets(buffer,20,stdin);
	*number = atoi(buffer);
	return strlen(buffer)>3?0:1;
}

void Help()
{
	puts("Usage:");
}

void FillTree(tree * tr)
{
	puts("Type EXIT for input interruption");
	tree *tr1, *tr2;
	char buffer[20];
	int result;
	int ind;
	if(!tr)
	{
		puts("No root");
		return;
	}
	do
	{
		puts("Info:");
		GetString(buffer);
		if(strcmp(buffer,"EXIT\n")==0)
			return;
		tr1 = tr;
		ind = 0;
		do 
		{
			if(!(result = strcmp(buffer, tr1->info)))
			{
				tr1->repeats++;
				ind = 1;
			}
			else 
			{
				if (result < 0)
				{
					if (tr1->left != NULL) tr1 = tr1->left;
					else ind = 1;
				}
				else
				{
					if (tr1->right!=NULL) tr1 = tr1->right;
					else ind = 1;
				}
			}
		} while (ind == 0);
		if (result != 0)
		{
			if ((tr2 = (tree*)malloc(sizeof(tree))) == NULL)
			{
				puts("Not enough memory");
				return;
			}
			if (result < 0) tr1->left = tr2;
			else tr1->right = tr2;
			strcpy(tr2->info,buffer);
			tr2->repeats = 1;
			tr2->left = NULL;
			tr2->right = NULL;
		}
	} while (1);
}

tree * CreateTree(tree * tr)
{
	if (tr)
	{
		puts("Tree has already been created");
		return (tr);
	}
	if (!(tr = (tree*)malloc(sizeof(tree))))
	{
		puts("Not enough memory");
		return(NULL);
	}
	puts("Type some info on root level");
	GetString(tr->info);
	tr->repeats = 1;
	tr->left = NULL;
	tr->right = NULL;
	char tmp [10];
	puts("Proceed? [Y/N]");
	GetString(tmp);
	if (strcmp(tmp,"Y\n")==0)
		FillTree(tr);	
	return tr;
}

int CountNodesMethod(tree * root, int N)
{
   if (root == 0)
       return 0;
   if (N == 0)
       return 1;
   return CountNodesMethod(root->left, N - 1) + CountNodesMethod(root->right, N - 1);
}



void CountNodes(tree * tr)
{
	puts("Type in tree level");
	int N = -1;
	while (1)
	{
		if (GetInt(&N) == 0)
			puts("Input error. Try again");
		else break;
	}
	int resultCount = CountNodesMethod(tr, N);
	
	printf("There's %d nodes on %d level\n",resultCount, N); 
}

void ShowTree(tree * tr)
{
	if(tr)
	{
		printf("Node contains (%d) %s\n",tr->repeats,tr->info);
		if (tr->left) ShowTree(tr->left);
		if (tr->right) ShowTree(tr->right);
	}
}
int main(int argc, char * argv[])
{
	if (argc>1)
	{
		if (strcmp(argv[1],"-h")==0)
		{
			Help();
			return 0;
		}
		else 
		{
			puts("Error. Improper parameter.");
			return 0;
		}
	}
	tree *root;
	root = NULL;
	while (1)
	{
		puts("Options:\n1 - Create tree\n2 - Show tree\n3 - Count nodes on N level\n0 - Exit");
		int inp = -1;
		if (!GetInt(&inp))
			{
				puts("Input error. Try again");
				continue;
			}
		switch(inp)
		{
			case 1:
			root = CreateTree(root);
			break;
			case 2:
			ShowTree(root);
			break;
			case 3:
			CountNodes(root);
			break;
			case 0:
			return EXIT_SUCCESS;
			default:
			puts("Input error. Try again");
			break;			
		}
	}
	//TODO
}