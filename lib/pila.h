#include <stdio.h>
#include <stdlib.h>

typedef struct n
{
        int esp[3];
		short ocr;
        struct n *siguiente;
} snodo;

typedef snodo *NODO;
typedef snodo *PILA;

void push(PILA *pila, int *x)
{
		//variables push
        NODO nodo;
		int i;
		//fin v p
        nodo = (NODO) malloc(sizeof(snodo));
        if (nodo != NULL)
        {
			for(i=0; i<3; i++)
				nodo->esp[i] = x[i];
			nodo->ocr = 0;
			nodo->siguiente = *pila;
			*pila=nodo;
		}
}

NODO pop(PILA *pila)
{
		//variables pop
		NODO nodo;
		//fin v p

		nodo = *pila;
		*pila = (*pila)->siguiente;
		//free(nodo);
		return nodo;
}

int pila_vacia(PILA pila)
{
		return pila == NULL;
}

void nodos_pila(NODO nodo)
{
		if (nodo == NULL)
			printf("La pila está vacia\n");
		else
		{
			while (nodo != NULL)
            {
				printf("Especie: %d %d %d\tOcurrencias:%hi\n",nodo->esp[0], nodo->esp[1], nodo->esp[2], nodo->ocr);
				nodo = nodo->siguiente;
            }
			printf("\n");
		}
}

int busqueda_pila(NODO nodo, int * bus)
{
		int ocr;
		if (nodo == NULL)
			return 0;
		else
		{
			while (nodo != NULL)
			{
				if(nodo->esp[0] == bus[0] && nodo->esp[1] == bus[1] && nodo->esp[2] == bus[2])
				{
					//ocurrencia(&nodo);
					nodo->ocr++;
					ocr = nodo->ocr;
					return ocr;
				}
				nodo = nodo->siguiente;
			}
		}
		return 0;
}

void liberar(PILA *pila)
{
        //variable liberar
        NODO nodo;
        //fin variable liberar

		while(pila_vacia(*pila))
		{
			nodo = pop(pila);
			free(nodo);
		}
}
