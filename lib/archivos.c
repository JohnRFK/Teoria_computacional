#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "archivos.h"

int crearArch(const int *op, const char *narch, int tarch)
{
    //variables abrirArch
    FILE *fp;
    char c;
    char *tcad[2] = {"cadenas binarias", "palabras"};
    int i, j;
    int rand_a = (rand() % 100) + 1;
    int rand_b;
    //fin va

    if((fp = fopen(narch,"w")) == NULL)
	{
		perror("abrir archivo");
		return 0;
	}

	switch(*op)
    {
        case 1:
            printf("Escriba la/las %s que desea guardar [Presione \"*\" para terminar]\n", tcad[tarch]);
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
                    c = ((char) (rand() % 2)) + '0';
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

int leerArch(char *narch, const int *qf, const char *mng, int tarch, void (*aut)(const char *c, int *q, FILE *fa))
{
    //variables leer
    FILE *fl, *fan;
    char *c, sy;
    char fanalisis[50], faux[20];
    char mnn[200];
	int q=0, i=0, n=0;
	int j, n2 = 0;
    //fin variables

    srand(time(NULL));
    c = (char *) malloc(sizeof(char) * 102);

    memset(faux, '\0', sizeof(faux));
    memcpy(faux, narch, strlen(narch) - 4);
    sprintf(fanalisis, "an_%s.txt", faux);
    printf("%s\n", fanalisis);

    if((fl = fopen(narch,"r")) == NULL)
	{
		printf("El archivo %s no existe o puso la ruta equivocada\n", narch);
		return 0;
	}
	if((fan = fopen(fanalisis, "w")) == NULL)
	{
		perror("Escribir archivo de analisis");
		return 0;
	}
    printf("Archivo creado con exito\nAnalisis del archivo: %s\n", narch);
	fprintf(fan, "Resultado del analisis del archivo %s: \n", narch);


    while(1)
	{
        c[i] = fgetc(fl);

        if(!tarch)
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
                q = 0;
                memset(c, 0, sizeof(c));
                i = 0;
                continue;
            }
            for(j = 0; (j <= sizeof(qf)/sizeof(int)) && !n2; j++)
                n2 = (q == qf[j]);

            if(n2)
            {
                sprintf(mnn, mng, "si");
                printf("La cadena %s pertenece al lenguaje, %s\n", c, mnn);
                fprintf(fan, "La cadena %s pertenece al lenguaje, %s\n", c, mnn);
            }
            else
            {
                sprintf(mnn, mng, "no");
                printf("La cadena %s no pertenece al lenguaje, %s\n",c, mnn);
                fprintf(fan, "La cadena %s no pertenece al lenguaje, %s\n", c, mnn);
            }

            if(sy == EOF)
                break;

            printf("\n");
            q = 0;
            memset(c, 0, 101);
            i = 0;
            n2 = 0;
            continue;
        }

        aut(&c[i], &q, fan);

        if(q == -1)
        {
            printf("existe un simbolo \'%c\' que no pertenece al alfabeto. ", c[i]);
            fprintf(fan, "existe un simbolo \'%c\' que no pertenece al alfabeto. ", c[i]);
            printf("Por lo tanto la cadena \"%s\" no pertenece al lenguaje\n\n", c);
            fprintf(fan, "Por lo tanto la cadena \"%s\" no pertenece al lenguaje\n\n", c);

            q = 0;
            memset(c, 0, 101);
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


