#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Programa4.h"
#include "archivos.h"

int cad_01()
{
    //variables cad_01
    int desicion1;
    int qfinal[1] = {1};     //estado final
    char op;
    char mng[80] = "El automata %s contiene 01";
    //fin variables

    //system("clear");      //linux
    do
    {
        srand(time(NULL));
        do
        {
            printf("\nCadenas que contengan un 01\nSeleccione una opcion:\n");
			printf("1.Crear sus propias cadenas\n");
			printf("2.Realizarlo automaticamente\n3.Salir\n$ ");
			scanf("%d", &desicion1);
			fflush(stdin);
			if(desicion1 == 3)
                return 0;
        }while(desicion1 < 1 && desicion1 > 3);

        if(!crearArch(&desicion1, "aut1.txt", AUT_BIN))
            return 0;

        if(!leerArch("aut1.txt", qfinal, mng, AUT_BIN, aut_01))
            return 0;

        fflush(stdin);

		printf("\n[Aut 01]Desea continuar?[s/n]: ");
		op = getchar();
    }while(op == 's' || op == 's');
    return 0;
}

void aut_01(const char *c, int *q, FILE *fa)
{
	switch(*c)
	{
		case '0':
			switch(*q)
			{
				case 0:
					*q = 2;
					break;
			}
			printf("%c : estado %d\n", *c, *q);
			fprintf(fa, "%c : estado %d\n", *c, *q);
			break;
		case '1':
			switch(*q)
			{
				case 2:
					*q = 1;
					break;
			}
			printf("%c : estado %d\n", *c, *q);
			fprintf(fa, "%c : estado %d\n", *c, *q);
			break;
		default:
			*q = -1;
			break;
	}
}



