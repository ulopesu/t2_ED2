#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "OrdenacaoExterna2.h"

long int n;
long int m;
long int seg;
long int dig = 0;

void movimentaDigitos(char final[11]) {
    long int num, aux, i, tam, k = 10;
    char c;
    tam = 10;

    for (i = 0; i < tam; i++) {
        aux = pow(k, i + 1);
        num = dig % aux;
        aux = pow(k, i);
        num = num / aux;
        final[(tam - 1) - i] = num + 48;
        c = final[(tam - 1) - i];
    }

    dig++;
    final[tam] = '\n';
    c = final[tam];
    return;
}

void GeraRegistros() {
    int chave, cont;
    char nomeAqv[50], registro[28], meio[17] = "_Estrutura_Dados_", final[11];
    FILE *Arqregistros;
    long long i, n;
    srand(time(NULL));

    for(cont = 0; cont <= 2; cont++){
    	n = pow(2, cont + 20);
	sprintf(nomeAqv, "files/input/2_%d.bin", cont + 20);
    	Arqregistros = fopen(nomeAqv, "wb+");
    	for (i = 0; i < n; i++) {
    	    chave = rand() % 10;
    	    movimentaDigitos(final);
    	    fwrite(&chave, sizeof(int), 1, Arqregistros);
    	    sprintf(registro, "%s%s", meio, final);
    	    fwrite(registro, sizeof (registro), 1, Arqregistros);
    	}
	fclose(Arqregistros);
    }
}




int main(int argc, char** argv) {
    int i, j, f;
    char entrada[100], resultado[100];
    char dir[100];
    FILE *Aqv;
    struct timeval Inicio, Final;

    GeraRegistros();
    printf("\nFAZENDO ORDENACAO EXTERNA...\n");
    Aqv = fopen("files/resultado.txt", "w+");

    for (f = 2; f <= 4; f++) {
        printf("\nf: %d", f);
        fprintf(Aqv, "\nf: %d", f);
        for (j = 0; j <= 2; j++) {
            n = pow(2, j + 20);
            printf("\nn: %d\n", j + 20);
            fprintf(Aqv, "\nn: %d\n", j + 20);
            for (i = 2; i <= 8; i = i * 2) {
                m = n / pow(2, i);
                sprintf(entrada, "files/input/2_%d.bin", j + 20);
                sprintf(resultado, "files/output/f%dn%dm%d.bin", f, j + 20, i);
                gettimeofday(&Inicio, NULL);
                OrdenaExterna2(entrada, resultado, n, m, f);
                gettimeofday(&Final, NULL);
                seg = ((Final.tv_sec - Inicio.tv_sec) + (Final.tv_usec - Inicio.tv_usec) / 1000000);
                printf("\nOrdem de intercalação: %d\nNumero de Registros: %li\nEspaco de Memoria: %li\nTempo em Segundos: %li\n", f, n, m, seg);
                fprintf(Aqv, "\nOrdem de intercalação: %d\nNumero de Registros: %li\nEspaco de Memoria: %li\nTempo em Segundos: %li\n", f, n, m, seg);
                seg = 0;
            }
        }
    }
    fclose(Aqv);
    
    return 0;
}
