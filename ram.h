void initialize_ram();
void load_to_ram(FILE *, int *start, int *end);
void removefromram(int start, int end);
void clear_ram();


#define RAM_LENGTH 1000

 char *ram[RAM_LENGTH];