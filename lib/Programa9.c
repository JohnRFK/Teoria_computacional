#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Programa9.h"

#define ARCH_A "ajedrez.txt"

void ajedrez()
{
    //variables ajedrez
    int desicion1;
    int qfinal[2] = {5, 6};     //estado final
    char op;
    //fin variables

    //system("clear");      //linux
    do
    {
        srand(time(NULL));
        do
        {
            printf("\nAjedres\nSeleccione una opcion:\n");
			printf("1.Crear sus propios movimientos\n");
			printf("2.Realizarlo automaticamente\n3.Salir\n$ ");
			scanf("%d", &desicion1);
			fflush(stdin);
			if(desicion1 == 3)
                return;
        }while(desicion1 < 1 && desicion1 > 3);

        if(!crearArchAj(&desicion1))
            return;

        if(!leerArchAj(qfinal))
            return;

        fflush(stdin);

		printf("\n[Ajedrez]Desea continuar?[s/n]: ");
		op = getchar();
		system("cls");
    }while(op == 's' || op == 'S');
    return;
}

void aut_rd(const char *c, int *q, FILE *fa)
{
    char estados[7][17] = {"{1}", "{2, 4}", "{5}", "{2, 4, 6, 8}", "{1, 3, 5, 7}", "{1, 3, 5, 7}", "{1, 3, 5, 7, 9}"};
	switch(*c)
	{
		case 'r':
			switch(*q)
			{
				case 0:
					*q = 1;
					break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    *q = 3;
                    break;

			}
			printf("%c : combinacion cuadros %s\n", *c, estados[*q]);
			fprintf(fa, "%c : combinacion cuadros %s\n", *c, estados[*q]);
			break;
		case 'b':
			switch(*q)
			{
				case 0:
				case 5:
					*q = 2;
					break;
                case 1:
                    *q = 4;
                    break;
                case 2:
                    *q = 5;
                    break;
                case 3:
                case 4:
                case 6:
                    *q = 6;
                    break;
			}
			printf("%c : combinacion cuadros %s\n", *c, estados[*q]);
			printf("q = %d\n", *q);
			fprintf(fa, "%c : combinacion cuadros %s\n", *c, estados[*q]);
			break;
		default:
			*q = -1;
			break;
	}
}

int crearArchAj(const int *op)
{
    //variables abrirArch
    FILE *fp;
    char c;
    int i, j;
    int rand_a = (rand() % 100) + 1;
    int rand_b;
    //fin va

    if((fp = fopen(ARCH_A, "w")) == NULL)
	{
		perror("abrir archivo");
		return 0;
	}

	switch(*op)
    {
        case 1:
            printf("Escriba los movimientos [r para cuadros rojos; b, para blancos] que desea guardar [Presione \"*\" para terminar]\n");
            printf("(Recomendacion) Puede separar cada cadena con espacio o con enter\n");
            while(1)
            {
                c = getchar();
                if(c == '*')
                    break;
                if(EOF == putc(c, fp))
                {
                    perror("Error de escritura");
                    return 0;
                }
            }
            break;
        case 2:
            for(i = 0; i < rand_a; i++)
            {
                rand_b = (rand() % 100) + 1;
                for(j = 0; j < rand_b; j++)
                {
                    if(rand() % 2)
                        c = 'b';
                    else
                        c = 'r';
                    if(EOF == putc(c, fp))
                    {
                        perror("Error de escritura");
                        return 0;
                    }
                }
                if(EOF == putc('\n', fp))
                {
                    perror("Error de escritura");
                    return 0;
                }
            }
            break;
    }

	fclose(fp);
	return 1;
}

int leerArchAj(const int *qf)
{
    //variables leer
    FILE *fl, *fan;
    char *c, sy;
	int q=0, i=0;
	int j, n2 = 0;
    //fin variables

    srand(time(NULL));
    c = (char *) malloc(sizeof(char) * 1001);

    if((fl = fopen(ARCH_A, "r")) == NULL)
	{
		perror("Error");
		return 0;
	}
	if((fan = fopen("an_ajedrez.txt", "w")) == NULL)
	{
		perror("Escribir archivo de analisis");
		return 0;
	}
    printf("Archivo creado con exito\nAnalisis del archivo: %s\n", "an_ajedrez.txt");
	fprintf(fan, "Resultado del analisis del archivo %s: \n", "an_ajedrez.txt");

    while(1)
	{
        c[i] = fgetc(fl);

        if(c[i] == ' ' || c[i] == '\n' ||c[i] == EOF || i >= sizeof(c))
        {
            sy = c[i];
            c[i] = 0;

            if(strlen(c) == 0)
            {
                if(sy == EOF)
                    break;
                q = 0;
                memset(c, 0, sizeof(c));
                i = 0;
                continue;
            }

            if(q == qf[0] || q == qf[1])
            {
                printf("Los movimientos %s llegan al extremo inferior del tablero\n", c);
                fprintf(fan, "Los movimientos %s llegan al extremo inferior del tablero\n", c);
            }
            else
            {
                printf("Los movimientos %s no llegan al extremo inferior del tablero\n", c);
                fprintf(fan, "Los movimientos %s no llegan al extremo inferior del tablero\n", c);
            }

            if(sy == EOF)
                break;

            printf("\n");
            q = 0;
            memset(c, 0, sizeof(c));
            i = 0;
            n2 = 0;
            continue;
        }

        aut_rd(&c[i], &q, fan);

        if(q == -1)
        {
            printf("existe un simbolo \'%c\' que no pertenece al alfabeto. ", c[i]);
            fprintf(fan, "existe un simbolo \'%c\' que no pertenece al alfabeto. ", c[i]);
            printf("Por lo tanto la cadena \"%s\" no pertenece al lenguaje\n\n", c);
            fprintf(fan, "Por lo tanto la cadena \"%s\" no pertenece al lenguaje\n\n", c);

            q = 0;
            memset(c, 0, sizeof(c));
            i = 0;
            continue;
        }
        i++;
	}

	free(c);
	fclose(fl);
	fclose(fan);
	return 1;

}
