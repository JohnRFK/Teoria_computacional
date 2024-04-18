#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "Programa8.h"
#include "archivos.h"

#define C_PAR "aut4.txt"
#define AUT_BIN 0

int cand_ter01()
{
    //variables cand_ter01
    int desicion1;
    char op;
    //fin variables

    do
    {
        srand(time(NULL));
        do
        {
            printf("Automata no deterministico\nCadenas que terminen en \"01\" [Automata 4]\nSeleccione una opcion:\n");
			printf("1.Crear sus propias cadenas\n");
			printf("2.Realizarlo automaticamente\n3.Salir\n$ ");
			scanf("%d", &desicion1);
			fflush(stdin);
			if(desicion1 == 3)
                return 0;
        }while(desicion1 < 1 && desicion1 > 3);

        if(!crearArch(&desicion1, C_PAR, AUT_BIN))
            return 0;

        leerAut();

        fflush(stdin);

		printf("\n[No Deterministico]Desea continuar?[s/n]: ");
		op = getchar();
		system("cls");
    }while(op == 's' || op == 's');
    return 0;
}
void aut_nd01(const char *c, int *q, FILE *fa)
{
    //variables aut_nd01
    int i;
    //fin variables
    switch(*c)
	{
		case '0':
			if(q[1] == 0 && q[2] == 0)
			{
			    q[1] = 1;
			}
			else if(q[1] == 0 && q[2] == 1)
			{
			    q[1] = 1;
			    q[2] = 0;
			}
            printf("%c : estado%c ", *c,(q[1] || q[2]) ? 's' : ' ');
            fprintf(fa, "%c : estado%c ", *c,(q[1] || q[2]) ? 's' : ' ');
            for(i = 0; i < 3; i++)
            {
                if(q[i])
                {
                    printf("%d ", i);
                    fprintf(fa ,"%d ", i);
                }

            }
			printf("\n ");
            fprintf(fa ,"\n ");
			break;
		case '1':
			if(q[1] == 1 && q[2] == 0)
			{
			    q[2] = 1;
			    q[1] = 0;
			}
			else if(q[1] == 0 && q[2] ==1)
			{
			    q[2] = 0;
			}

            printf("%c : estado%c ", *c,(q[1] || q[2]) ? 's' : ' ');
            fprintf(fa ,"%c : estado%c ", *c,(q[1] || q[2]) ? 's' : ' ');
            for(i = 0; i < 3; i++)
            {
                if(q[i])
                {
                    printf("%d ", i);
                    fprintf(fa ,"%d ", i);
                }

            }
			printf("\n ");
            fprintf(fa ,"\n ");
			break;
		default:
			q[0] = -1;
			break;
	}
}

void leerAut()
{
    //variables leer
    FILE *fl, *fan;
    char *c, sy;
    char fanalisis[50], faux[20];
	int q[3], i=0, n=0;
	int n2 = 0;
    //fin variables

    q[0] = 1;
    q[1] = 0;
    q[2] = 0;

    srand(time(NULL));
    c = (char *) malloc(sizeof(char) * 102);

    memset(faux, '\0', sizeof(faux));
    memcpy(faux, C_PAR, strlen(C_PAR) - 4);
    sprintf(fanalisis, "an_%s.txt", faux);
    printf("%s\n", fanalisis);

    if((fl = fopen(C_PAR,"r")) == NULL)
	{
		perror("archivo de lectura");
		return;
	}
	if((fan = fopen(fanalisis, "w")) == NULL)
	{
		perror("Escribir archivo de analisis");
		return;
	}

    printf("Archivo creado con exito\nAnalisis del archivo: %s\n", C_PAR);
	fprintf(fan, "Resultado del analisis del archivo %s: \n", C_PAR);

    while(1)
	{
        c[i] = fgetc(fl);

        if(!AUT_BIN)
            n = !isgraph(c[i]);
        else
            n = !isalnum(c[i]);

        if(n || c[i] == EOF || i >= 100)
        {
            sy = c[i];
            c[i] = 0;

            if(strlen(c) == 0)
            {
                if(sy == EOF)
                    break;
                q[1] = 0;
                q[2] = 0;
                memset(c, 0, sizeof(c));
                i = 0;
                continue;
            }

            if(q[0] == 1 && q[1] == 0 && q[2] == 1)
            {

                printf("La cadena %s pertenece al lenguaje, por lo tanto si termina en 01\n", c);
                fprintf(fan, "La cadena %s pertenece al lenguaje, por lo tanto si termina en 01\n", c);
            }
            else
            {
                printf("La cadena %s no pertenece al lenguaje, por lo tanto no termina en 01\n", c);
                fprintf(fan, "La cadena %s no pertenece al lenguaje, por lo tanto no termina en 01\n", c);
            }

            if(sy == EOF)
                break;

            printf("\n");
            q[1] = 0;
            q[2] = 0;
            memset(c, 0, 101);
            i = 0;
            n2 = 0;
            continue;
        }

        aut_nd01(&c[i], &q[0], fan);

        if(q[0] == -1)
        {
            printf("existe un simbolo \'%c\' que no pertenece al alfabeto. ", c[i]);
            fprintf(fan, "existe un simbolo \'%c\' que no pertenece al alfabeto. ", c[i]);
            printf("Por lo tanto la cadena \"%s\" no pertenece al lenguaje\n\n", c);
            fprintf(fan, "Por lo tanto la cadena \"%s\" no pertenece al lenguaje\n\n", c);

            q[1] = 0;
            q[2] = 0;
            memset(c, 0, 101);
            i = 0;
            continue;
        }
        i++;
	}

	free(c);
	fclose(fl);
	fclose(fan);

}
