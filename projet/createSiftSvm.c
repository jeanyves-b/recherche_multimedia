#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


int main(int argc, char *argv[])
{
	FILE *image = NULL;
	image = fopen(argv[1],"r+");

	char *cluster = malloc(sizeof(char)*10);
	int counter=0;
	int *table = malloc(sizeof(int)*256);

	if (image != NULL)
	{
		while (fgets(cluster, 10, image) != NULL)
		{
			table[atoi(cluster)-1]++;
			counter++;
		}
		for (int i = 0; i < 256; i++)
		{
			float a = ((float)table[i])/((float)counter);
			printf("%d:%f ", i, a);
		}
		printf("\n");
	}
	else
		fprintf(stderr, "erreur, impossible d'ouvrir le fichier %s", argv[1]);
}