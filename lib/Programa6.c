#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pila.h"
#include "Programa6.h"

#define ARCH_ES "especies.txt"

void combinatorio(const int *ne, char *ch_esp, PILA *comesp, FILE *fp);
int tres_especies(int *esp, PILA *pila, FILE *fp);

int pespecies()
{
		//variables especies
		int esp[3];
		int ne;
		int op;
		int bol = 0;
		char ch_esp[3] = {0, 0, 0};
		char cop;

        FILE *fp;

		PILA pila = NULL;
		PILA comesp = NULL;
		NODO nodoesp = NULL;
		//fin variables especies

		if((fp = fopen(ARCH_ES, "w")) == NULL)
        {
            perror("Error ");
            return -1;
        }

		do
		{
			srand(time(NULL));

			printf("Simulacion del automata de las 3 especies [Automata 3]\nSeleccione la opcion que desea realizar:\n");
			printf("1.Insertar el numero de habitantes del planeta\n");
			printf("2.Generar el numero de habitantes del planeta automaticamente\n3.Salir\n");

			do
			{
				printf("$ ");
				scanf("%d", &op);
				fflush(stdin);
				if(op == 3)
				      return 0;
			}while(op > 2 || op < 1);

			switch(op)
			{
				case 1:
					do
					{
						printf("\nIntroduce el numero de habitantes [max 13]:\t");
						scanf("%d", &ne);
						fflush(stdin);
					}while(ne >= 13 || ne < 1);
					break;
				case 2:
					ne = (rand()%12)+1;
					printf("\nEl numero de habitantes generado es: %d\n", ne);
					break;
			}
            fprintf(fp, "Numero de habitantes: %d\n\n", ne);
            combinatorio(&ne, ch_esp, &comesp, fp);
			//iniciacion(esp, &ne);
			while(comesp != NULL)
			{

			    nodoesp = pop(&comesp);
			    esp[0] = nodoesp->esp[0];
			    esp[1] = nodoesp->esp[1];
			    esp[2] = nodoesp->esp[2];
			    if(pila != NULL)
                    liberar(&pila);

                printf("Analisis de las especies:\n");
                fprintf(fp, "Analisis de las especies:\n");

                while(1)
                {
                    burbuja(esp, ch_esp);
                    imprimir(esp, ch_esp, fp);

                    if(onton(esp))
                        continue;

                    if(ne == 3 && esp[1] == 1 && esp[2] == 2)
                    {
                        printf("Ciclo infinito, ninguna especie dominara el planeta\n\n");
                        fprintf(fp, "Ciclo infinito, ninguna especie dominara el planeta\n\n");
                        //imprimir(esp, ch_esp);
                        //system("pause");
                        break;
                    }
                    if(!esp[0] && !esp[1])
                    {
                        printf("Finalizo el automata:\nEspecie dominante: %c\n\n", ch_esp[2]);
                        fprintf(fp, "Finalizo el automata:\nEspecie dominante: %c\n\n", ch_esp[2]);
                        if(pila != NULL)
                                liberar(&pila);
                        //system("pause");
                        break;
                    }
                    if(bol)
                        break;
                    if(!esp[0])
                        dos_especies(esp);
                    else
                        bol = tres_especies(esp, &pila, fp);
                }
                free(nodoesp);
			}

            fclose(fp);
			printf("[Especies] Desea continuar? [s/n]: ");
			cop = getchar();
			fflush(stdin);
		}while(cop == 'S' || cop == 's');

		return 0;
}

void imprimir(const int *esp, const char *nesp, FILE *fp)
{
     int i;
    for(i = 0; i < 3; i++)
    {
        printf("%c ", nesp[i]);
        fprintf(fp,"%c ", nesp[i]);
    }
    printf("\n");
    fprintf(fp, "\n");
    for(i = 0; i < 3; i++)
    {
        printf("%d ", esp[i]);
        fprintf(fp, "%d ", esp[i]);
    }
    printf("\n\n");
    fprintf(fp, "\n\n");
}

void burbuja(int * esp, char * nesp)
{
	//variables burbuja
    int i, j;
    int aux;
    char naux;
	//fin variables

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 2; j++)
        {
            if(esp[j] > esp[j+1])
            {
                aux = esp[j];
                esp[j] = esp[j+1];
                esp[j+1] = aux;

                naux = nesp[j];
                nesp[j] = nesp [j+1];
                nesp[j+1] = naux;
            }
        }
    }
}

void iniciacion(int *esp, const int *ne)
{
	//variables iniciacion
    int i;
	//fin variable

    srand(time(NULL));
    for(i = 0; i < 3; i++)
          esp[i] = 0;

    for(i = 0; i < *ne; i++)
        esp[rand()%3]++;
}

void dos_especies(int *esp)
{
	esp[0] += 2;
	esp[1] --;
	esp[2] --;
}

int onton(int *esp)
{
    if(esp[0] == 1 && esp[1] == 1)
    {
        esp[0] = 0;
        esp[1] = 0;
        esp[2] = esp[2] + 2;
        return 1;
    }
    if(esp[2] == 1 && esp[1] == 1)
    {
        esp[2] = 0;
        esp[1] = 0;
        esp[0] = esp[0] + 2;
        return 1;
    }
    if(esp[0] == 1 && esp[2] == 1)
    {
        esp[0] = 0;
        esp[2] = 0;
        esp[1] = esp[1] + 2;
        return 1;
    }
    return 0;
}

void combinatorio(const int *ne, char *ch_esp, PILA *comesp, FILE *fp)
{
    //variables combinatorio
    int esp[3];
    int i, j;
    //fin variables

    srand(time(NULL));

    ch_esp[0] = (char)(rand()%3)+'a';

    do{
        ch_esp[1] = (char)(rand()%3)+'a';
    }while(ch_esp[1] == ch_esp[0]);
    do{
        ch_esp[2] = (char)(rand()%3)+'a';
    }while(ch_esp[2] == ch_esp[0] || ch_esp[2] == ch_esp[1]);

    printf("especies generadas:\n%c %c %c\n", ch_esp[0], ch_esp[1], ch_esp[2]);
    fprintf(fp, "especies generadas:\n%c %c %c\n", ch_esp[0], ch_esp[1], ch_esp[2]);
    // printf("id\n");
    i = 1;
    j = 0;

    esp[0] = *ne;
    esp[1] = 0;
    esp[2] = 0;

    do{
        while(esp[0] >= i)
        {
            //printf("id\n");
            esp[0] = *ne - i - j;
            esp[1] = i;
            esp[2] = j;

            if(esp[0] < i)
                      break;
            i++;
            push(comesp, esp);
            printf("%d %d %d\n", esp[0], esp[1], esp[2]);
            fprintf(fp, "%d %d %d\n", esp[0], esp[1], esp[2]);
        }

        i = 1;
        j++;
        while(j > i)
                i++;
        esp[0] = *ne - i - j;
        if(j > esp[0])
             break;
    }while(1);
}

int tres_especies(int *esp, PILA *pila, FILE *fp)
{
    //variables tres_especies
	int ocr;
	//fin variables tres_especies

		if(!(ocr = busqueda_pila((NODO)*pila, esp)))
			push(pila, esp);

		switch(ocr)
		{
			case 0:
				esp[0]--;
				esp[1]--;
				esp[2]+=2;
				//printf("0.-resultado: %d %d %d\n", esp[0], esp[1], esp[2]);
				break;
			case 1:
				esp[1]--;
				esp[2]--;
				esp[0]+=2;
				//printf("1.-resultado: %d %d %d\n", esp[0], esp[1], esp[2]);
				break;
			case 2:
				esp[2]--;
				esp[0]--;
				esp[1]+=2;
				//printf("2.-resultado: %d %d %d\n", esp[0], esp[1], esp[2]);
				break;
			case 3:
				printf("Ciclo infinito, ninguna especie dominara\n");
				fprintf(fp, "Ciclo infinito, ninguna especie dominara\n");
				liberar(pila);
				//system("pause");
				return 1;
		}
		return 0;
}

