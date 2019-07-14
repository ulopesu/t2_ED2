#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OrdenacaoExterna2.h"

void Particao(long int Esq, long int Dir, long int *i, long int *j, TipoRegistro2* buffer) {
    TipoRegistro2 x, w;
    *i = Esq;
    *j = Dir;
    x = buffer[(*i + *j) / 2]; /* obtem o pivo x */
    do {
        while (x.chave > buffer[*i].chave) {
            (*i)++;
        }
        while (x.chave < buffer[*j].chave) {
            (*j)--;
        }
        if (*i <= *j) {
            w = buffer[*i];
            buffer[*i] = buffer[*j];
            buffer[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Ordena(long int Esq, long int Dir, TipoRegistro2* buffer) {
    long int i, j;
    Particao(Esq, Dir, &i, &j, buffer);
    if (Esq < j) Ordena(Esq, j, buffer);
    if (i < Dir) Ordena(i, Dir, buffer);
}

void QuickSort(TipoRegistro2* buffer, long int nRegistrosLidos) {
    Ordena(1, nRegistrosLidos, buffer);
}

bool2 verificaBufferVazio2(TipoRegistro2 buffer[]) {
    if (buffer[1].chave == -1 && buffer[1].dados[0] == '\0') {
        return true2;
    } else {
        return false2;
    }
}

bool2 EnchePaginas2(ArqEntradaTipo ArqEntrada, long int* nRegistrosLidos, TipoRegistro2 buffer[], long int n, long int m) {
    long i;
    int chave;
    char dados[28];
    *nRegistrosLidos = 0;

    for (i = 0; i < m; i++) {
        if (feof(ArqEntrada)) {
            return true2;
        } else {
            if (fread(&chave, sizeof (int), 1, ArqEntrada) && fread(dados, sizeof (char), 28, ArqEntrada)) {
                buffer[i + 1].chave = chave;
                strcpy(buffer[i + 1].dados, dados);
                *nRegistrosLidos += 1;
            }
        }
    }

    if (feof(ArqEntrada)) {
        return true2;
    }

    return false2;
}

ArqEntradaTipo AbreArqSaida2(long int NBloco) {
    char nome[100];
    sprintf(nome, "files/output/%li.bin", (NBloco - 1));
    return fopen(nome, "wb+");
}

void LimpaBuffer(TipoRegistro2 *buffer, long int tam) {
    int i;
    for (i = 0; i <= tam; i++) {
        buffer[i].chave = -1;
        buffer[i].dados[0] = '\0';
    }
}

void DescarregaPaginas2(ArqEntradaTipo ArqSaida, TipoRegistro2 *buffer, long int nRegistrosLidos) {
    long int i;
    for (i = 0; i < nRegistrosLidos; i++) {
        fwrite(&buffer[i + 1].chave, sizeof (int), 1, ArqSaida);
        fwrite(&buffer[i + 1].dados, sizeof (char), 28, ArqSaida);
    }
    LimpaBuffer(buffer, nRegistrosLidos);
}

long int Minimo2(long int a, long int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void AbreArqEntrada2(ArqEntradaTipo *ArrArqEnt, long int Low, long int Lim) {
    char nome[100];
    long int j = 0, i;
    for (i = Low; i <= Lim; i++) {
        sprintf(nome, "files/output/%li.bin", i);
        ArrArqEnt[j] = fopen(nome, "r+");
        if (ArrArqEnt[j] == NULL) {
            break;
        }
        j++;
    }
}

int ContCabValido2(TipoRegistro2 **reg, int f) {
    int i, cont;
    for (i = 0; i < f; i++) {
        if (reg[i] != NULL) {
            cont++;
        }
    }
    return cont;
}

bool2 VerRegistroLimpo2(TipoRegistro2 *reg) {
    if (reg->chave == -1 && reg->dados[0] == '\0') {
        return true2;
    } else {
        return false2;
    }
}

void LimpaRegistro2(TipoRegistro2 **reg, int i) {
    reg[i]->chave = -1;
    reg[i]->dados[0] = '\0';
}

void LimpaCabecote2(TipoRegistro2 **reg, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        reg[i]->chave = -1;
        reg[i]->dados[0] = '\0';
    }
}

int MenorPosChaveRegistro2(TipoRegistro2 **cabecote, int f) {
    int posmenorChave, i, aux = 0;
    int menorChave = -1;
    bool2 verRegLimpo;

    for (i = 0; i < f; i++) {
        if (cabecote[i] != NULL) {
            verRegLimpo = VerRegistroLimpo2(cabecote[i]);
            if (cabecote[i] != NULL && !verRegLimpo) {
                if (aux == 0) {
                    menorChave = cabecote[i]->chave;
                    posmenorChave = i;
                    aux++;
                } else if (cabecote[i]->chave < menorChave) {
                    menorChave = cabecote[i]->chave;
                    posmenorChave = i;
                }
            }
        }
    }
    if (menorChave == -1) {
        return -1;
    }
    return posmenorChave;
}

TipoRegistro2** CriaRegistro2(int tam) {
    TipoRegistro2 **reg;
    int i;
    reg = (TipoRegistro2**) malloc(sizeof (TipoRegistro2*) * tam);
    for (i = 0; i < tam; i++) {
        reg[i] = (TipoRegistro2*) malloc(sizeof (TipoRegistro2));
    }
    return reg;
}

TipoRegistro2** EliminaRegistro2(TipoRegistro2 **reg, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        free(reg[i]);
    }
    free(reg);
    return NULL;
}

void ManipulaCabecote(ArqEntradaTipo* ArrArqEnt, ArqEntradaTipo ArqSaida, TipoRegistro2 **cabecote, int f, int finalizados) {
    int i, posmenorChave;
    int chave;

    do {
        for (i = 0; i < f; i++) {
            if (cabecote[i] != NULL && ArrArqEnt[i] != NULL) {
                if (VerRegistroLimpo2(cabecote[i]) && !feof(ArrArqEnt[i])) {
                    fread(&cabecote[i]->chave, sizeof (int), 1, ArrArqEnt[i]);
                    fread(cabecote[i]->dados, sizeof (char), 28, ArrArqEnt[i]);
                } else if (feof(ArrArqEnt[i])) {
                    cabecote[i] = NULL;
                    finalizados++;
                }
            }
        }

        if (f - finalizados == 1) {
            for (i = 0; i < f; i++) {
                if (cabecote[i] != NULL && ArrArqEnt[i] != NULL) {
                    break;
                }
            }

            while (1) {
                if (!feof(ArrArqEnt[i])) {
                    if (VerRegistroLimpo2(cabecote[i])) {
                        fread(&cabecote[i]->chave, sizeof (int), 1, ArrArqEnt[i]);
                        fread(cabecote[i]->dados, sizeof (char), 28, ArrArqEnt[i]);
                        if (!VerRegistroLimpo2(cabecote[i])) {
                            chave = cabecote[i]->chave;
                            fwrite(&chave, sizeof (int), 1, ArqSaida);
                            fwrite(cabecote[i]->dados, sizeof (char), 28, ArqSaida);
                            LimpaRegistro2(cabecote, i);
                        }
                    } else {
                        chave = cabecote[i]->chave;
                        fwrite(&chave, sizeof (int), 1, ArqSaida);
                        fwrite(cabecote[i]->dados, sizeof (char), 28, ArqSaida);
                        LimpaRegistro2(cabecote, i);
                    }
                } else {
                    cabecote[i] = NULL;
                    finalizados++;
                    break;
                }
            }
        } else if (f - finalizados > 1) {
            posmenorChave = MenorPosChaveRegistro2(cabecote, f);
            if (posmenorChave != -1) {
                chave = cabecote[posmenorChave]->chave;
                fwrite(&chave, sizeof (int), 1, ArqSaida);
                fwrite(cabecote[posmenorChave]->dados, sizeof (char), 28, ArqSaida);
                LimpaRegistro2(cabecote, posmenorChave);
            }
        }
    } while (finalizados < f);
    cabecote = EliminaRegistro2(cabecote, f);
}

void Intercale2(ArqEntradaTipo* ArrArqEnt, ArqEntradaTipo ArqSaida, int f) {
    long long int i = 0;
    long long int arquivosFinalizados = 0;
    TipoRegistro2 **cabecote = CriaRegistro2(f);
    LimpaCabecote2(cabecote, f);

    for (i = 0; i < f; i++) {
        if (ArrArqEnt[i] == NULL) {
            arquivosFinalizados++;
        }
    }

    if (arquivosFinalizados == f) {
        cabecote = EliminaRegistro2(cabecote, f);
        return;
    }

    ManipulaCabecote(ArrArqEnt, ArqSaida, cabecote, f, arquivosFinalizados);

}

void ApagaArquivo2(long long i) {
    char nome[100];
    sprintf(nome, "files/output/%lli.bin", i);
    remove(nome);
}

void OrdenaExterna2(char *arquivoEntrada, char* arquivoFinal, long int n, long int m, int f) {
    long int NBlocos, Low, Lim, High, nRegistrosLidos, i, j;
    char ultimoArq[100];
    bool2 Fim;
    ArqEntradaTipo ArqEntrada1, ArqSaida;
    ArqEntradaTipo ArrArqEnt[f];
    TipoRegistro2 *buffer = (TipoRegistro2*) malloc(sizeof (TipoRegistro2)*(m + 1));

    NBlocos = 0;
    nRegistrosLidos = 0;
    LimpaBuffer(buffer, m);

    ArqEntrada1 = fopen(arquivoEntrada, "r+");

    if (ArqEntrada1 == NULL) {
        printf("Erro Arquivo de Entrada\n");
        return;
    }

    do /*Formacao inicial dos NBlocos ordenados */ {
        Fim = EnchePaginas2(ArqEntrada1, &nRegistrosLidos, buffer, n, m);
        if (verificaBufferVazio2(buffer)) {
            break;
        }
        NBlocos++;
        QuickSort(buffer, nRegistrosLidos);
        ArqSaida = AbreArqSaida2(NBlocos);
        DescarregaPaginas2(ArqSaida, buffer, nRegistrosLidos);
        nRegistrosLidos = 0;
        fclose(ArqSaida);
    } while (!Fim);

    free(buffer);
    buffer = NULL;
    fclose(ArqEntrada1);

    Low = 0;
    High = NBlocos - 1;

    while (Low < High) { // Intercalacao dos NBlocos ordenados
        Lim = Minimo2(Low + f - 1, High);
        AbreArqEntrada2(ArrArqEnt, Low, Lim);
        High++;
        ArqSaida = AbreArqSaida2(High + 1);
        Intercale2(ArrArqEnt, ArqSaida, f);
        fclose(ArqSaida);
        for (i = Low, j = 0; i <= Lim; i++, j++) {
            if (ArrArqEnt[j] != NULL) {
                fclose(ArrArqEnt[j]);
                ArrArqEnt[j] = NULL;
                ApagaArquivo2(i);
            }
        }
        Low += f;
    } //Mudar o nome do arquivo FINAL(high) para o nome fornecido pelo usuario;

    sprintf(ultimoArq, "files/output/%li.bin", i);
    rename(ultimoArq, arquivoFinal);
}


