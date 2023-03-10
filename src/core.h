


int gen_chain_word_unique(const char* words[], int len, char* result[]);

int gen_chains_all(const char* words[], int len, char* result[]); 
int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, char jinz, bool enable_loop);
int gen_chain_char(const char* words[], int len, char* result[], char head, char tail, char jinz, bool enable_loop);