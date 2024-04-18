#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Programa3.h"
#define ARCH_P "primo.txt"
#define LIM_PR 20

int binprimo()
{
	//variables pro3
	int desicion1;
	char op;
	//fin variables pro3
	do
	{
		srand(time(NULL));

		printf("Programa para determinar si un numero binario es primo o no\n");
		do{
			printf("Seleccione una opcion:\n");
			printf("1.Crear el numero\n");
			printf("2.Realizarlo automaticamente\n3.Salir\n$ ");
			scanf("%d",&desicion1);
			while(getchar()!='\n');
			if(desicion1 == 3)
				return 0;

		}while(desicion1 < 1 && desicion1 > 3);


		nbinario(desicion1);

		fflush(stdin);
		printf("[Primo] Desea continuar? [s/n]\n$ ");
		op = getchar();
		system("cls");
	}while(op == 's' || op == 'S');
	return 0;
}

void nbinario(int des)
{
	//variables nbinario
	long i, j;
	long btod = 0;
	long lim;
	short n=0;
	char *cad;
	FILE *fp;
	//fin cariables nbinario

	if((fp = fopen(ARCH_P, "w")) == NULL)
    {
        perror("Error ");
        return;
    }


	switch(des)
	{
		case 1:
			cad = (char *) malloc(sizeof(char) * 101);
			memset(cad, 0, 101);
			do{
				printf("Capture el numero binario [maxima longitud 100]:\t");
				//scanf("%100s", cad);
				fflush(stdin);
				gets(cad);

				for(i=0; i < (long)strlen(cad); i++)
				{
					if(cad[i] != '0' && cad[i] != '1')
					{
						printf("\nRecuerda, solo se admiten 0 y 1\n");
						n = 1;
						break;
					}
					n = 0;
				}
			}while(n);
			//printf("\nnumero: %d\n", i);

			break;
		case 2:
			i = (rand() % LIM_PR) + 1;
			cad = (char *) malloc(sizeof(char) * (i+1));
			memset(cad, '\0', sizeof(char) * (i+1));

			for(j=0; j<i; j++)
			{
				cad[j] = ((char)(rand()%2)) + '0';
			}
			printf("Numero binario generado:\t%s\n", cad);
			fprintf(fp, "Numero binario generado:\t%s\n", cad);
			break;
	}

	for(j=0; j<i; j++)
	{
		if(cad[j] == '1')
			btod += (long) pow(2, i-j-1);
	}
    printf("\nConjunto de numeros primos con limite convertido a decimal %ld\n", btod);
    fprintf(fp, "Conjunto de numeros primos con limite convertido a decimal %ld\n", btod);

    printf("Primos en binario");
    fprintf(fp, "Primos en binario");

    printf("P = { 1");
    fprintf(fp, "P = { 1");
    for(j = 0; j< btod; j++)
    {
        if(primo(j))
        {
            printf(", ");
            fprintf(fp, ", ");
            lim = (long) (log(j)/log (2.0));
            for(i = (long) pow(2, lim); i > 0; i = i >> 1)
            {
                if(i & j)
                {
                    printf("1");
                    fprintf(fp, "1");
                }
                else
                {
                    printf("0");
                    fprintf(fp, "0");
                }
            }
        }
    }
    printf("}\n");
    fprintf(fp, "}\n");

    printf("Primos en decimal");
    fprintf(fp, "Primos en decimal");

    printf("P = { 1");
    fprintf(fp, "P = { 1");

    for(j = 0; j< btod; j++)
    {
        if(primo(j))
        {
            printf(", %d", j);
            fprintf(fp, ", %d", j);

        }
    }

    printf("}\n");
    fprintf(fp, "}\n");

	free(cad);
	fclose(fp);
}

int primo(int n)
{
	//variable primo
	int r = 0, i;
	//fin variable primo
	if(n == 0 || n == 1 || n == 2)
		return 0;

	for(i=1; i<=n; i++)
	{
		if(!(n%i))
			r++;
		if(r > 2)
			return 0;
	}
		return 1;

}
