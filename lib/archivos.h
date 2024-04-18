#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#define AUT_BIN 0
#define AUT_TEX 1

int crearArch(const int *op, const char *narch, int tarch);
int leerArch(char * narch, const int *qf, const char *mng, int tarch, void (*aut)(const char *c, int *q, FILE *fa));

#endif // ARCHIVOS_H_INCLUDED
