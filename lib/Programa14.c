#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Programa14.h"

#define Q_FINAL -4
#define ARCH "maquinat.txt"

void maquina_T()
{
    int desicion1;
    char op;
    do
    {
        srand(time(NULL));
        do
        {
            printf("\nMaquina de turing paridad de 0n1n [Programa 14]\nSeleccione una opcion:\n");
            printf("1.Generar cadenas binarias aleatoriamente\n2.Insertar cadena\n3.Salir\n$ ");
			scanf("%d", &desicion1);
			fflush(stdin);
			if(desicion1 == 3)
                return;
        }while(desicion1 < 1 && desicion1 > 3);
        fflush(stdin);

        inicio_MT(&desicion1);

        fflush(stdin);

		printf("\n[Maquina de turing] Desea continuar?[s/n]: ");
		op = getchar();
		system("cls");
    }while(op == 's' || op == 's');
}
void inicio_MT(const int *op)
{
    int i, j, q, lg0;
    int rnd1, rnd2;
    char *base;
	char *cinta;
	FILE *fp;

	if((fp = fopen(ARCH, "w")) == NULL)
	{
	    perror("error");
	    return;
	}

    switch(*op)
    {
        case 1:
            lg0 = (rand() % 11) + 4;
            base = (char *) malloc(sizeof (char) * (lg0+2));
            memset(base, '\0', sizeof (char) * (lg0+2));
            if(rand() % 7 != 2)
            {
                for(i = 0; i < (lg0/2); i++)
                    base[i] = '0';
                for(j = i; j < (lg0/2)+i; j++)
                    base[j] = '1';
            }else
            {
                rnd1 = rand() % (lg0/2);
                rnd2 = rand() % (lg0/2);
                for(i = 0; i < rnd1; i++)
                    base[i] = '0';
                for(j = i; j < rnd2; j++)
                    base[j] = '1';
            }
            printf("Cadena generada: %s\n", base);
            fprintf(fp, "Maquina de turing\nCadena generada: %s\n", base);
            break;
        case 2:
            base = (char *) malloc(sizeof(char) * 1001);
            printf("Inserte la cadena [maximo 1000 caracteres]: ");
            gets(base);
            fprintf(fp, "Maquina de turing\nCadena introducida: %s\n", base);
            break;
    }

	cinta = (char *) malloc(sizeof(char) * (strlen(base) + 5));

	memset(cinta, '\0', sizeof(char) * (strlen(base) + 5));
	memset(cinta, 'B', sizeof(char) * (strlen(base) + 4));

	for(i = 2; base[i-2] != '\0'; i++)
        cinta[i] = base[i-2];

	i = 2;
	q = 0;
	printf("\nInicio proceso: \nCinta: ...%s... \nEstado: %d\n", cinta, q);
	fprintf(fp, "\nInicio proceso: \nCinta: ...%s...\nEstado: %d\n\n", cinta, q);
	while(1)
	{
        i = funcion_MT(&q, &cinta[i], &i);

        //printf("i = %d\n", i);
		switch(i)
		{
			case -1:
				printf("Se introdujo caracter no valido\n");
				fprintf(fp, "Se introdujo caracter no valido\n");
				free(cinta);
				free(base);
				fclose(fp);
				return;
            case Q_FINAL:
                printf("La cadena %s cumple con la paridad de 0n 1n \n", base);
                fprintf(fp, "La cadena %s cumple con la paridad de 0n 1n \n", base);
                printf("Cinta: ...%s...\nEstado: %d\n", cinta, q);
                fprintf(fp, "Cinta: ...%s...\nEstado: %d\n", cinta, q);
                free(cinta);
                free(base);
                fclose(fp);
                return;
            case -2:
            case -3:
            case -5:
            case -6:
            case -7:
                printf("La cadena %s no cumple con la paridad de 0n 1n \n", base);
                fprintf(fp, "La cadena %s no cumple con la paridad de 0n 1n \n", base);
                free(cinta);
                free(base);
                fclose(fp);
                return;
            default:
                printf("Cinta: ...%s...\nEstado: %d\n\n", cinta, q);
                fprintf(fp, "Cinta: ...%s...\nEstado: %d\n\n", cinta, q);
                break;
		}

	}
    //printf("%s", cinta);
}

int funcion_MT(int *q, char *cc, const int *i)
{
    int j = *i;
    //printf("leo %d %c %i\n", *q ,*cc, *i);

	switch(*cc)
	{
		case '0':
			switch(*q)
			{
				case 0:
					*q = 1;
					*cc = 'X';
					j++;
					break;
				case 1:
					j++;
					break;
				case 2:
					j--;
					break;
				default:
					return -2;
			}
			break;
		case '1':
			switch(*q)
			{
				case 1:
					*q = 2;
					*cc = 'Y';
					j--;
					break;
				default:
					return -3;

			}
			break;
		case 'X':
			switch(*q)
			{
				case 2:
                    *q = 0;
					j++;
					break;
				default:
					return -5;
			}
			break;
		case 'Y':
			switch(*q)
			{
				case 0:
					*q = 3;
					j++;
					break;
				case 1:
					j++;
					break;
				case 2:
					j--;
					break;
				case 3:
					j++;
					break;
				default:
					return -6;
			}
			break;
		case 'B':
			switch(*q)
			{
				case 3:
					*q = 4;
					j--;
					return Q_FINAL;
				default:
					return -7;
			}
			break;
		default:
			return -1;
	}
	return j;
}
