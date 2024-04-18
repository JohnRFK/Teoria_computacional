#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Programa5.h"
#include "archivos.h"

#define C_PAR "aut2.txt"

int cad_paridad()
{
    //variables cad_paridad
    int desicion1;
    int qfinal = 0;     //estado final
    char op;
    char mng[80] = "El automata %s tiene paridades de 0 y 1";
    //fin variables

    do
    {
        srand(time(NULL));
        do
        {
            printf("\nCadenas que contengan paridades de ceros y unos [Automata 2]\nSeleccione una opcion:\n");
			printf("1.Crear sus propias cadenas\n");
			printf("2.Realizarlo automaticamente\n3.Salir\n$ ");
			scanf("%d", &desicion1);
			fflush(stdin);
			if(desicion1 == 3)
                return 0;
        }while(desicion1 < 1 && desicion1 > 3);

        if(!crearArch(&desicion1, C_PAR, AUT_BIN))
            return 0;

        if(!leerArch(C_PAR, &qfinal, mng, AUT_BIN, aut_paridad))
            return 0;

        fflush(stdin);

		printf("\n[Paridad]Desea continuar?[s/n]: ");
		op = getchar();
    }while(op == 's' || op == 's');
    return 0;

}

void aut_paridad(const char *c, int *q, FILE *fa)
{
	switch(*c)
	{
		case '0':
			switch(*q)
			{
				case 0:
					*q = 2;
					break;
				case 1:
					*q = 3;
					break;
				case 2:
					*q = 0;
					break;
				case 3:
					*q = 1;
					break;
			}
			printf("%c : estado %d\n", *c, *q);
			fprintf(fa, "%c : estado %d\n", *c, *q);
			break;
		case '1':
			switch(*q)
			{
				case 0:
					*q = 1;
					break;
				case 1:
					*q = 0;
					break;
				case 2:
					*q = 3;
					break;
				case 3:
					*q = 2;
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
