#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Programa1.h"
#include "Programa2.h"
#include "Programa3.h"
#include "Programa4.h"
#include "Programa5.h"
#include "Programa6.h"
#include "Programa7.h"
#include "Programa8.h"
#include "Programa9.h"
#include "Programa10.h"
#include "Programa12.h"
#include "Programa13.h"
#include "Programa14.h"

void automatas(void);

int main(int argc, char *argv[])
{
        //variables teoria
		char c_menp;
		int i_menp;
		//fin variables teoria

		do
		{
		    system("cls");
			printf("Teoria Computacional\nSeleccione el numero de opcion que desea realizar:\n");
			printf("1.Potencia de un alfabeto [Pr1]\n2.Cerradura de kleane[Pr2]\n");
			printf("3.Numero binario primo [Pr3]\n4.Automatas\n");
			printf("5.Expresion regular[Pr10]\n6.Palindrome[Pr12]\n7.Balanceo parentesis[Pr13]\n8.Maquina de Turing[Pr14]\n9.Salir\n");
			do
			{
			    printf("# ");
                scanf("%d", &i_menp);
                if(i_menp == 9)
                    return 0;
			}while(i_menp >8 || i_menp < 1);
			fflush(stdin);

            system("cls");
			switch(i_menp)
			{
				case 1:
					potencia();
					break;
				case 2:
                    cerradura();
					break;
				case 3:
				    binprimo();
					break;
				case 4:
				    automatas();
					break;
                case 5:
                    exp_reg();
					break;
                case 6:
                    palin();
                    break;
                case 7:
                    parentesis();
                    break;
                case 8:
                    maquina_T();
                    break;
                default:
                    return 0;
			}

			printf("Teoria computacional\nDesea continuar?[s/n]\n# ");
			fflush(stdin);
			c_menp = getchar();

		}while(c_menp == 'S' || c_menp == 's');

		return 0;
}

void automatas(void)
{
		int opcion;

		printf("Automatas\nSeleccione el numero de opcion que desea realizar:\n");
		printf("1.Cadena que contenga un 01[Pr4]\n2.Paridad de 0 y 1[Pr5]\n");
		printf("3.Especie dominante[Pr6]\n4.Cadena que termine en 01 (DNA)[Pr7]\n");
		printf("5.Busqueda de cadenas con \"web\" y \"ebay\"[Pr8]\n6.Ajedrez[pr9]\n6.Salir\n");

        do
        {
            printf("& ");
            scanf("%d", &opcion);
            fflush(stdin);
        }while(opcion < 1 || opcion > 7);

        system("cls");
		switch(opcion)
		{
			case 1:
                cad_01();
				break;
			case 2:
                cad_paridad();
				break;
			case 3:
			    pespecies();
				break;
			case 4:
                cand_ter01();
				break;
			case 5:
                cad_ebayweb();
				break;
            case 6:
                ajedrez();
                break;
            case 7:
                return;
		}
}
