#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"
#include "shellmemory.h"
#include "interpreter.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"
#include "kernel.h"






struct PCB *makePCB(int start, int end)
{
	struct PCB *newpcb;
	newpcb = (struct PCB *) malloc(sizeof(struct PCB));
	newpcb->PC = start;
	newpcb->start = start;
	newpcb->end = end;

	return newpcb;
}