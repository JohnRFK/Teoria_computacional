#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "programa13.h"

#define ARCH_PA "parentesis.txt"

void parentesis()
{
    int desicion1;
    char op;
    do
    {
        srand(time(NULL));
        do
        {
            printf("\nAnalizador de balanceo entre parentesis [Programa 13]\nSeleccione una opcion:\n");
            printf("1.Insertar parentesis\n2.Generar parentesis aleatoriamente\n3.Salir\n$ ");
			scanf("%d", &desicion1);
			fflush(stdin);
			if(desicion1 == 3)
                return;
        }while(desicion1 < 1 && desicion1 > 3);
        fflush(stdin);

        anali_paren(&desicion1);

        fflush(stdin);

		printf("\n[Parentesis]Desea continuar?[s/n]: ");
		op = getchar();
		system("cls");
    }while(op == 's' || op == 's');
}

void anali_paren(const int *op)
{
    //variables anali
    char *base;
    char *gram;
    char *aux;
    int i, j, k;
    int ind;
    int lg;
    FILE *fp;
    //fin variables

    if((fp = fopen(ARCH_PA, "w")) == NULL)
    {
        perror("Error ");
        return;
    }

    switch(*op)
    {
        case 1:
            lg = 1000;
            base = (char *) malloc(sizeof(char) * (lg + 10));
            memset(base, '\0', sizeof(char) * (lg + 10));
            printf("Inserte la cadena [maximo 1000 caracteres]: ");
            gets(base);
            for(i = 0; i<strlen(base)-1; i++)
            {
                if(base[i] != '(' && base[i] != ')')
                {
                    printf("Error al colocar los parentesis: introdujo un simbolo %c\n", base[i]);
                    fclose(fp);
                    free(base);
                    return;
                }
            }
            fflush(stdin);
            break;
        case 2:
            lg = (rand() % 20) + 1;
            if((base = (char *) malloc(sizeof(char) * ((lg * 2)+1))) == NULL)
            {
                perror("error");
                return;
            }
            memset(base, '\0', sizeof(char) * (lg * 2));
            generador_paren(base, &lg);
            printf("Cadena generada: %s", base);
            break;
    }
    gram = (char *) malloc(sizeof(char) * (strlen(base)+10));
    aux = (char *) malloc(sizeof(char) * (strlen(base)+10));
    memset(aux, '\0', sizeof(char) * (strlen(base)+10));
    memset(gram, '\0', sizeof(char) * (strlen(base)+10));

    memcpy(gram, "B -> B", sizeof(char) * 6);
    fprintf(fp, "Generacion de la gramatica de cadena %s\n\nGramatica:\n%s", base, gram);
    printf("\nGramatica: \n%s\n", gram);
    ind = 0;

    for(i = 5; gram[i] != '\0'; i++)
    {
        memset(aux, '\0', sizeof(char) * (strlen(base)+10));
        if(gram[i] == 'R')
        {
            for(k = i+1; gram[k] != '\0'; k++)
                aux[k-(i+1)] = gram[k];

            if(base[i-5] == '(')
            {
                gram[i] = '(';
                gram[i+1] = 'R';
                gram[i+2] = 'R';
                j = i + 3;
            }else if(base[i-5] == ')')
            {
                gram[i] = ')';
                j = i + 1;
            }

            for(k = 0; aux[k] != '\0'; k++)
            gram[j+k] = aux[k];

        }
        else if(gram[i] == 'B')
        {
            if(base[i-5] == '(')
            {
                for(k = i+1; gram[k] != '\0'; k++)
                    aux[k-(i+1)] = gram[k];

                gram[i] = '(';
                gram[i+1] = 'R';
                gram[i+2] = 'B';
                j = i+3;
                for(k = 0; aux[k] != '\0'; k++)
                    gram[j+k] = aux[k];
            }
        }
        printf("%s\n", gram);
        fprintf(fp, "%s\n", gram);
    }

    for(i = 5; gram[i] != '\0'; i++)
    {
        memset(aux, '\0', sizeof(char) * (strlen(base)+10));
        if(gram[i] == 'B')
        {
            for(k = i+1; gram[k] != '\0'; k++)
                aux[k-(i+1)] = gram[k];

            gram[i] = 'e';
            j = i+1;
            for(k = 0; aux[k] != '\0'; k++)
                gram[j+k] = aux[k];
            printf("%s\n", gram);
            fprintf(fp, "%s\n", gram);
            i--;
        }
        else if(gram[i] == 'e')
        {
            for(j = i; gram[j] != '\0'; j++)
                gram[j] = gram[j+1];
            printf("%s\n", gram);
            fprintf(fp, "%s\n", gram);
        }
    }

    fclose(fp);
    free(gram);
    free(base);
    free(aux);
}

void generador_paren(char *base, const int *lg)
{
    int i, j, k;
    int rnd;
    char *aux;

    if((aux = (char *) malloc(sizeof (char) * (*lg * 2))) == NULL)
    {
        perror("error ");
        return;
    }
    memset(aux, '\0', sizeof (char) * (*lg * 2));

    if(rand() % 1000 == 999)
    {
        base[0] = ' ';
        return;
    }

    else
    {
        base[0] = '(';
        base[1] = 'R';
        base[2] = 'B';
    }

    for(i = 1; i <= *lg; i++)
    {
        rnd = rand() % 2;
        if(base[i] == 'R')
        {
            for(k = i+1; base[k] != '\0'; k++)
                aux[k-(i+1)] = base[k];
            if(rnd)
            {
                base[i] = ')';
                j = i + 1;
            }
            else
            {
                base[i] = '(';
                base[i+1] = 'R';
                base[i+2] = 'R';
                j = i + 3;
            }

            for(k = 0; aux[k] != '\0'; k++)
                base[j+k] = aux[k];
        }
        else if(base[i] == 'B')
        {
            if(rnd)
            {
                for(j = i; base[j] != '\0'; j++)
                    base[j] = base[j+1];
                continue;
            }
            else
            {
                for(k = i+1; base[k] != '\0'; k++)
                    aux[k-(i+1)] = base[k];

                base[i] = '(';
                base[i+1] = 'R';
                base[i+2] = 'B';
                j = i+3;
                for(k = 0; aux[k] != '\0'; k++)
                    base[j+k] = aux[k];
            }
        }
        if(base[i] == '\0')
            break;

    }

    for(i = 0; base[i] != '\0'; i++)
    {
        if(base[i] == 'B')
            base[i] = '\0';
        if(base[i] == 'R')
            base[i] = ')';
    }

    free(aux);

}
