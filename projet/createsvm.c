#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main(int argc, char *argv[])
{
	char *svmline, *annline;
	svmline = malloc(sizeof(char)*1000);
	annline = malloc(sizeof(char)*20);

	char *outname, *annname;
	outname = malloc(sizeof(char)*30);
	annname = malloc(sizeof(char)*30);
	strcpy(outname, "eval/svm/color_");
	outname = strcat(outname, argv[1]);
	outname = strcat(outname, ".svm");
	strcpy(annname, "eval/ann/");
	annname = strcat(annname, argv[1]);
	annname = strcat(annname, ".ann");

	FILE *output = NULL, *svm = NULL, *annotation = NULL;
	output = fopen(outname, "w+");
	svm = fopen("eval/histo.svm", "r");
	annotation = fopen(annname, "r");

	if (output != NULL || svm != NULL || annotation != NULL)
	{
		while(fgets(svmline, 1000, svm) != NULL 
			&& fgets(annline, 20, annotation) != NULL)
		{
			svmline[0] = '1';
			if (annline[12] == '-')
				fprintf(output, "-");
			fprintf(output, "%s", svmline);
		}
	}
	else
	{
		printf("patate\n");
	}
	free(svmline);
	free(annline);
	free(outname);
	free(annname);
	exit(0);
}