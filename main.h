// Authored by José Julio Suárez (jojusuar@espol.edu.ec)

#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include "list.h"

List *mergesort(List *);

List *merge(List *, List *);

void *sorterThread(void * );

List *quicksort(List * );