#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "Programa1.h"

#define LIM_1 10

int potencia()
{
	//*variables
	int desicion1;
	char *alpha;
	char op;
	int cardAlpha;
	int i;
	char j;
	//*fin variables

	do
	{
		srand(time(NULL));

		do
		{
			printf("Potencia de un alfabeto\nSeleccione una opcion:\n");
			printf("1.Crear su propio alfabeto\n");
			printf("2.Realizarlo automaticamente\n3.Salir\n$ ");
			scanf("%d", &desicion1);
			fflush(stdin);
		} while (desicion1 < 1 || desicion1 > 3);

		switch (desicion1)
		{
		case 1:
			do
			{
				printf("Introdusca la cantidad de elementos que contendra el alfabeto [Maximo 10]:\n");
				scanf("%d", &cardAlpha);
				fflush(stdin);
			} while (cardAlpha > 10 || cardAlpha < 1);

			fflush(stdin);
			alpha = (char *)malloc(sizeof(char) * (cardAlpha + 1));
			memset(alpha, '\0', sizeof(char) * (cardAlpha + 1));

			printf("Introdusca los elementos del alfabeto [Presionando enter por cada caso]:\n");
			for (i = 0; i < cardAlpha; i++)
			{
				printf("%d.-", i + 1);
				scanf("%c", &alpha[i]);
				fflush(stdin);
			}
			break;
		case 2:
			cardAlpha = (rand() % LIM_1) + 1;

			alpha = (char *)malloc(sizeof(char) * (cardAlpha + 1));
			memset(alpha, '\0', sizeof(char) * (cardAlpha + 1));

			switch (rand() % 3)
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
			for (i = 0; i < cardAlpha; i++)
			{
				alpha[i] = j;
				printf("%c, ", (char)alpha[i]);
				j = j + (char)1;
			}
			printf("\b\b}\n");
			break;
		case 3:
			return 0;
		}
		do
		{
			printf("Seleccione una opcion:\n");
			printf("1.Capturar la potencia\n");
			printf("2.Realizarlo automaticamente\n$ ");
			scanf("%d", &desicion1);
			fflush(stdin);
		} while (desicion1 != 1 && desicion1 != 2);

		generarPotencia(desicion1, alpha, cardAlpha);

		free(alpha);
		fflush(stdin);
		printf("[Potencia]Desea continuar?[s/n]\n");
		op = getchar();
	} while (op == 's' || op == 'S');
	return 0;
}

void generarPotencia(int des1, char *alpha, int cardAlpha)
{
	// variables gpotencia
	FILE *fp;
	long i, j;
	long kp = 0;
	long r;
	// fin variables

	if (alpha == NULL)
	{
		printf("error");
		free(alpha);
		exit(-1);
	}
	// printf("valores cardinalidad: %d kp: %ld alpha: %c \n", cardAlpha, kp, alpha[0] );

	switch (des1)
	{
	case 1:
		printf("Introdusca la potencia:\n");
		scanf("%ld", &kp);
		break;
	case 2:
		kp = (rand() % LIM_1) + 1;
		printf("Potencia generada: %ld", kp);
		break;
	}

	fflush(stdin);

	if ((fp = fopen("potencia.txt", "w")) == NULL)
	{
		perror("Error en archivo");
		exit(-1);
	}

	fprintf(fp, "Alfabeto E={ e, ");
	for (i = 0; i < sizeof(alpha) / sizeof(char); i++)
	{
		fprintf(fp, "%c", alpha[i]);
		if (i + 1 != sizeof(alpha) / sizeof(char))
			fprintf(fp, ", ");
	}

	fprintf(fp, "}\n\n");
	fprintf(fp, "Potencia = %ld\n", kp);
	printf("\nE={");
	fprintf(fp, "\nE^%ld={", kp);

	for (i = 0; i < potencia_n(cardAlpha, kp); i++)
	{
		r = i;
		for (j = kp - 1; j >= 0; j--)
		{
			fprintf(fp, "%c", alpha[r / (long)pow(cardAlpha, j)]);
			printf("%c", alpha[r / (long)pow(cardAlpha, j)]);
			// fprintf(fp, "r = %ld %d elevado a j=%ld igual %ld  ", r, cardAlpha, j, potencia_n(cardAlpha, j));
			// fprintf(fp,"alpha[%ld] \n", r/potencia_n(cardAlpha, j));
			r %= potencia_n(cardAlpha, j);
		}
		if (i != potencia_n(cardAlpha, kp) - 1)
		{
			printf(", ");
			fprintf(fp, ", ");
		}
		// fprintf(fp, "i = %ld\n", i);
	}
	printf("}");
	fprintf(fp, "}");
	printf("\nArchivo potencia.txt creado con exito\n");

	fclose(fp);
}

long potencia_n(long b, long n)
{
	long poo, i;

	poo = 1;
	if (n == 0)
		return 1;

	for (i = 0; i < n; i++)
	{
		poo *= b;
	}
	return poo;
}
