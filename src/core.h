#ifdef CORE_DLL
#define CORE_EXPOSE extern "C" __declspec(dllexport)
#else
#define CORE_EXPOSE extern "C" __declspec(dllimport)
#endif

CORE_EXPOSE
int gen_chains_all(const char* words[], int len, char* result[]); 
CORE_EXPOSE
int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, char skip, bool enable_loop);
CORE_EXPOSE
int gen_chain_char(const char* words[], int len, char* result[], char head, char tail, char skip, bool enable_loop);

