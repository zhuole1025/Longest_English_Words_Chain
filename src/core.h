#ifndef LEWC_CORE_H
#define LEWC_CORE_H


#ifdef F_PIC
#define LIB_FUNC __declspec(dllexport)
#else
#define LIB_FUNC __declspec(dllimport)
#endif

#ifdef _cplusplus2
extern "C" {
#endif

    extern "C" __declspec(dllexport) int gen_chains_all(char* words[], int len, char* result[]);
    extern "C" __declspec(dllexport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);
    extern "C" __declspec(dllexport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);

#ifdef _cplusplus
}
#endif

#endif //LEWC_CORE_H
