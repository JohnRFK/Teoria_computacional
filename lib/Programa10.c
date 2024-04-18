#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Programa10.h"
#define ELEM 1000

int exp_reg()
{
    //variables expresion regular
    FILE *fp;

    //fin variables

    srand(time(NULL));

    if((fp = fopen("expresion.txt","w")) == NULL)
	{
		perror("abrir archivo expresion regular");
		return 0;
	}

    printf("Cadenas que no contengan dos o mas \'1\' consecutivos\nExpresion regular (0+10)*(1+e)\n");
    fprintf(fp, "Cadenas que no contengan dos o mas \'1\' consecutivos\nExpresion regular (0+10)*(1+e)\n");
    generarLR(fp);

    fclose(fp);
    return 0;
}

void generarLR(FILE *fp)
{
    //variables generarLR
    int i, j = 0;
    int rnd[3];
    const char *a[] = {"0", "10"};
    const char *b[] = {"", "1"};
    int v_b;
    //fin variables

    rnd[0] = rand() % ELEM;

    printf("{e");
    fprintf(fp, "{e");

    for(i = 0; i < rnd[0]; i++)
    {
        if(i < rnd[0] - 1)
        {
            printf(", ");
            fprintf(fp, ", ");
        }
        rnd[1] = rand() % 10;
        for(j = 0; j < rnd[1]; j++)
        {
            rnd[2] = rand() % 2;
            printf("%s", a[rnd[2]]);
            fprintf(fp, "%s", a[rnd[2]]);
        }

        if(!(v_b = rand() % 2) && !j)
        {
            printf("%s", b[1]);
            fprintf(fp, "%s", b[1]);
        }
        else
        {
            printf("%s", b[v_b]);
            fprintf(fp, "%s", b[v_b]);
        }
    }
    printf("}\n");
    fprintf(fp, "}");

}

