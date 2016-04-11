#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <dirent.h>

#include "rdjpeg.h"

#define NBCOLOR 	256
#define NBCELL		4

float* colorHisto(char *fichier)
{
	CIMAGE cim;
	int factor = NBCOLOR/NBCELL;
	int row = 1;
	int line = NBCELL;
	int depth = NBCELL*NBCELL;

	/*------------------------------------------------*/
	/* lecture d'une image requête                    */
	/*------------------------------------------------*/
	read_cimage(fichier,&cim);
	if (cim.nx == 0)
	{
		printf("mauvaise image\n");
		exit(0);
	} 
	float *result = malloc(sizeof(float)*NBCELL*NBCELL*NBCELL);
	for (int i=0 ; i<NBCELL*NBCELL*NBCELL ; i++)
		result[i] = 0;
	/*--------------------------------------------------*/
	/* création de l'histogramme de l'image             */
	/*--------------------------------------------------*/
	for (int j = 0; j < cim.ny; j++)
	{       /* ligne par ligne */
		for (int i = 0; i < cim.nx; i++)
		{   /* pixel par pixel */
			result[row*(cim.r[i][j]/factor)
					+ line*(cim.g[i][j]/factor)
					+ depth*(cim.b[i][j]/factor)] += ((float)1)/(cim.nx*cim.ny);
		}
	}
	return result;
	free_cimage(fichier, &cim);
	/*------------------------------------------------*/

	exit(0);
}

int main(int argc, char *argv[])
{
	float *histogramme = NULL;
	int n = 100;
	char *link = malloc(sizeof(char)*(n/2+1));
	char *filepos = malloc(sizeof(char)*(n+1));
	char *ann = malloc(sizeof(char)*(n/2+1));

	FILE *output = NULL, *input = NULL, *annotation = NULL;
	output = fopen("log_training", "w+");
	input = fopen("train/list.txt", "r");
	annotation = fopen("train/ann/aeroplane.ann", "r");

	if (input != NULL && output != NULL)
	{
		fgets(link, n/2, input);
		for (int i=0; link[i] != '\0'; i++)
		{
			if (link[i] == '\n')
			{
				link[i] = '\0';
				break;
			}
		}
		fgets(ann, n/2, annotation);
		strcpy(filepos,"train/img/");
		strcat(filepos, link);

		while (link !=NULL && *link != EOF)
		{
			histogramme = colorHisto(filepos);
			if (ann[12] == '-')
				fprintf(output, "-1 ");
			else
				fprintf(output, "+1 ");
			for(int i=0 ; i<NBCELL*NBCELL*NBCELL ; i++)
			{
				fprintf(output, "%d:%8f ", i+1, histogramme[i]);
			}
			fprintf(output, "\n");

			fgets(link, n, input);
			for (int i=0; link[i] != '\0'; i++)
			{
				if (link[i] == '\n')
				{
					link[i] = '\0';
					break;
				}
			}
			fgets(ann, n/2, annotation);
			strcpy(filepos,"train/img/");
			strcat(filepos, link);
		}

		fclose(output);
		fclose(input);
	}
	else
	{
		printf("Couldn't open the directory or the output file\n");
	}

	return 0;
}
