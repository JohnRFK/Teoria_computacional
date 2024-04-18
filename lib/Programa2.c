#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "Programa2.h"

#define LIM_P 5

int cerradura()
{
	//*variables
	int desicion1;
	char * alpha;
	int cardAlpha;
	int i, j;
	char op;
	//*fin variables

	do
	{
		srand(time(NULL));

		do{
			printf("\nSimulacion de la cerradura de kleane\nSeleccione una opcion:\n");
			printf("1.Crear su propio alfabeto\n");
			printf("2.Realizarlo automaticamente\n3.Salir\n$ ");
			scanf("%d",&desicion1);
			if(desicion1 == 3)
                return 0;
			fflush(stdin);
		}while(desicion1 < 1 && desicion1 > 3);

		switch(desicion1)
		{
			case 1:
				do{
					printf("Introdusca la cantidad de elementos que contendra el alfabeto [Maximo 10]:\n");
					scanf("%d", &cardAlpha);
				}while(cardAlpha > 10 || cardAlpha < 1);

				fflush(stdin);
				alpha = (char *) malloc(sizeof(char) * cardAlpha);

				printf("Introdusca los elementos del alfabeto [Presionando enter por cada caso]:\n");
				for(i = 0; i < cardAlpha; i++)
				{
					printf("%d.-", i+1);
					scanf("%c", &alpha[i]);
					fflush(stdin);
				}
				break;
			case 2:
				cardAlpha = (rand()%LIM_P)+1;

				alpha = (char *) malloc(sizeof(char) * cardAlpha);

				switch(rand()%3)
				{
					case 0:
						j = '0';
						break;
					case 1:
						j = 'a';
						break;
					case 2:
						j = 'A';
						break;
				}

				printf("\nEl alfabeto generado es: { ");
				for(i=j; i < cardAlpha + j; i++)
				{
					alpha[i-j] = (char) i;
					printf("%c, ", (char) alpha[i-j]);
				}
				printf("\b\b}\n");
				break;
		}

		do{
			printf("Seleccione una opcion:\n");
			printf("1.Capturar el limite de la cerradura\n");
			printf("2.Realizarlo automaticamente\n$ ");
			scanf("%d", &desicion1);
		}while(desicion1 != 1 && desicion1 != 2);
        fflush(stdin);
		generarCerradura(desicion1, alpha, cardAlpha);

		free(alpha);
		fflush(stdin);

		printf("[Cerradura]Desea continuar?[s/n]\n$ ");
		op = getchar();
	}while(op == 's' || op == 's');
	return 0;
}

void generarCerradura(int des1, char *alpha, int cardAlpha)
{
	//variables gpotencia
	FILE *fp;
	long i, j, l;
	long kp = 0;
	long r;
	//fin variables

	if(alpha == NULL)
	{
		printf("error");
		free(alpha);
		exit(-1);
	}
	//printf("valores cardinalidad: %d kp: %ld alpha: %c \n", cardAlpha, kp, alpha[0] );

	switch(des1)
	{
		case 1:
			printf("Introdusca el limite de la cerradura:\n");
			scanf("%ld", &kp);
			break;
		case 2:
			kp = (rand() % LIM_P);
			printf("limite de cerradura generada: %ld\n", kp);
			break;
	}



	if((fp = fopen("cerradura.txt", "w")) == NULL)
	{
		perror("Error en archivo");
		exit(-1);
	}


    printf("\nE*={e");
	fprintf(fp, "\nE*={e");
	if(kp == 0)
	{
           printf("}");
	       fprintf(fp,"}");
    }
    else
    {
        fprintf(fp, ", ");
        for(l=1; l<=kp; l++)
        {
            for(i=0; i < potencia_p(cardAlpha, l); i++)
            {
                r=i;
                for(j = l-1; j>=0; j--)
                {
                    fprintf(fp, "%c",alpha[r/potencia_p(cardAlpha, j)]);
                    printf("%c",alpha[r/potencia_p(cardAlpha, j)]);
                 //printf("j =%ld ", j);
                    r%=potencia_p(cardAlpha, j);
                }
                if(i != potencia_p(cardAlpha, l)-1)
                {
                    printf(", ");
                    fprintf(fp, ", ");
                }
            }
            if(l != kp)
            {
                fprintf(fp,", ");
                printf(", ");
            }

        }
		//if(i+1 != (long) pow(cardAlpha, l))
		printf("}\n");
		fprintf(fp, "}\n");
    }
	printf("Archivo cerradura.txt creado con exito\n");
	fclose(fp);
}

long potencia_p(long b, long n)
{
    long poo, i;

    poo = 1;
    if(n == 0)
        return 1;

    for(i = 0; i < n; i++)
    {
        poo *= b;
    }
    return poo;
}

