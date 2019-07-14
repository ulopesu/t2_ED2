#ifndef ORDENACAOEXTERNA2_H
#define ORDENACAOEXTERNA2_H

#ifdef __cplusplus
extern "C" {
#endif

    enum boolean2 {
        true2 = 1, false2 = 0
    };
    typedef enum boolean2 bool2;

    typedef FILE* ArqEntradaTipo;
    
    typedef struct {
        int chave;
        char dados[28];
    } TipoRegistro2;

    void OrdenaExterna2(char *arquivoEntrada, char* arquivoFinal, long int n, long int m, int f);

#ifdef __cplusplus

#endif

#endif /* ORDENACAOEXTERNA2_H */

