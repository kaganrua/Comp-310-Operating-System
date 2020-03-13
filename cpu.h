void initializeCPU();
void runCPU(int end);


struct CPU{
	int IP;
	char *IR[1000];
	int quanta;
};

struct CPU *cpu;
