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
}

int main(int argc, char const *argv[])
{
	float *histogramme = colorHisto(argv[1]);

	for(int i=0 ; i<NBCELL*NBCELL*NBCELL ; i++)
	{
		printf("%d:%8f ", i+1, histogramme[i]);
	}
	free(histogramme);
	return 0;
}