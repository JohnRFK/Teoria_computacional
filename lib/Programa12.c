#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Programa12.h"

#define ARCH "palindrome.txt"

void palin()
{
    //variables palin
    int desicion1;
    char op;
    //fin variables palin

    do
    {
        srand(time(NULL));
        do
        {
            printf("\nCreador de palindromes [Programa 12]\nSeleccione una opcion:\n");
            printf("1.Generar aleatoriamente\n2.Insertar longitud de palindrome y generarlo aleatoriamente\n3.Salir\n$ ");
			scanf("%d", &desicion1);
			fflush(stdin);
			if(desicion1 == 3)
                return;
        }while(desicion1 < 1 && desicion1 > 3);
        fflush(stdin);

        creador_pa(&desicion1);

        fflush(stdin);

		printf("\n[Palindrome]Desea continuar?[s/n]: ");
		op = getchar();
    }while(op == 's' || op == 's');

}

void creador_pa(const int *op)
{
    //variables
    int i, j, k, l;
    char *base;
    char *aux;
    FILE *f;
    //fin variables

    if((f = fopen(ARCH, "w")) == NULL)
    {
        perror("Error ");
        return;
    }

    switch(*op)
    {
        case 1:
            l = rand() % 20;
            printf("Longitud de palindrome: %d\n", l);
            fprintf( f, "Longitud de palindrome: %d\n", l);
            break;
        case 2:
            do{
                printf("Inserte la longitud del palindrome [max: 1000]\n");
                scanf("%i", &l);
            }while(l < 1 || l >1000);
            break;
    }

    base = (char *) malloc(sizeof(char) * (l + 5));
    aux = (char *) malloc(sizeof(char) * (l + 5));
    memset(base, '\0', sizeof(char) * (l + 5));
    memset(aux, '\0', sizeof(char) * (l + 5));
    base[1] = 'S';
    if(rand() % 2)
    {
        base[0] = '0';
        base[2] = '0';
    }
    else
    {
        base[0] = '1';
        base[2] = '1';
    }
    printf("Inicia generacion del palindrome: \n");
    fprintf(f, "Inicia generacion del palindrome: \n");
    printf("S -> %s\n", base);
    fprintf(f, "S -> %s\n", base);

    for(i = 1; i < (l/2); i++)
    {
        if(base[i] == 'S')
        {
            j = i+1;
            while(base[j] != '\0')
            {
                aux[j-(i+1)] = base[j];
                j++;
            }

            if(rand() % 2)
            {
                base[i] = '0';
                base[i+1] = 'S';
                base[i+2] = '0';
            }
            else
            {
                base[i] = '1';
                base[i+1] = 'S';
                base[i+2] = '1';
            }
            k=0;
            while(aux[k] != '\0')
            {
                base[i+3+k] = aux[k];
                k++;
            }


            printf("S -> %s\n", base);
            fprintf(f, "S -> %s\n", base);
            memset(aux, '\0', sizeof(char) * (l + 1));
        }
    }


    if(l % 2)
    {
        if(rand() % 2)
            base[l/2] = '0';
        else
            base[l/2] = '1';
    }
    else
    {
        k = l/2;
        while(base[k] != '\0')
        {
            base[k] = base[k+1];
            k++;
        }
    }

    printf("Palindromo de longitud %d generado: %s\n", l, base);
    fprintf(f, "Palindromo de longitud %d generado: %s\n\n", l, base);
    fputs(base, f);
    printf("El palindromo esta almacenado en el archivo %s\n", ARCH);

    fclose(f);
    free(base);
    free(aux);
}
