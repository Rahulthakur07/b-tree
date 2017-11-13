#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
int main (int argc, char *argv[]) 
{
    	FILE *fp;
    	BTree T;
    	BTreeCreate(&T, 3);
	node t;
	
	char *token;
	char *stringBuffer;
	stringBuffer = malloc(BUFFER_SIZE);

	if ((fp=fopen("dataset.csv", "r"))==NULL)
    	{
        	printf ("file cannot be opened");
        		return 1;
    	}
    	while ((fgets(stringBuffer, BUFFER_SIZE, fp)))
    	{

		token = strtok(stringBuffer, ",");
		t.key = atoi(token); //atoi: ASCII to integer

		token = strtok(NULL, ",");
		strcpy(t.country,token);

		token = strtok(NULL, ",");
		strcpy(t.grade,token);

		token = strtok(NULL, ",");
		t.score = atoi(token);

		token = strtok(NULL, ",");
		t.rate = atoi(token);
		//printf("%s ",t.country);
		BTreeInsert(&T, t);
    	}

	node *a;
	a = search(T.root,7845);

	printf("%d ",a->key);
	printf("%s ",a->country);

    	free(stringBuffer);
    	//BTreeTraverse(T.root);

    	return 0;
}
