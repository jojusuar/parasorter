// Authored by José Julio Suárez (jojusuar@espol.edu.ec)

#include "main.h"

int num_procs;
int base_case;
int threads_created = 0;
char *buffer;
int buffer_capacity = 1024*sizeof(char);
int read_size = 512;

int main(int argc, char **argv) {
    char *fvalue = NULL;
    bool inputFlag = true;
    int index;
    int c;

    opterr = 0;
    while ((c = getopt (argc, argv, "hf:")) != -1){
        switch (c)
        {
        case 'f':
            fvalue = optarg;
            inputFlag = false;
            break;
        case 'h':
            printf("Usage: %s [option]\n", argv[0]);
            printf("    No option:      Prompts user for input.\n");
            printf("    -f: <filename>  Reads numbers from specified path.\n");
            printf("    -h:             Shows this message.\n");
            return 0;
        case '?':
            if (optopt == 'f')
            fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
            fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
            fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
            return 1;
        }
    }
    buffer = (char *)malloc(buffer_capacity);
    if(inputFlag){
        printf("Enter a sequence of up to 200 integers, separated by commas. E.g: [number1],[number2],[number3],...,[numberN]\n");
        printf("Waiting for input: ");
        scanf("%s", buffer);
    }
    else{
        char *filename = strdup(fvalue);
        char *extension = NULL;
        char *token = strtok(filename, ".");
        while(token != NULL){
            extension = token;
            token = strtok(NULL, ".");
        }
        if(strcmp(extension, "csv") != 0){
            fprintf(stderr, "Specified file must have *.csv extension and format.\n");
            free(buffer);
            return 1;
        }
        int fd = open(fvalue, O_RDONLY);
        int total_read = 0;
        int bytes_read;
        while ((bytes_read = read(fd, buffer + total_read, read_size)) > 0) {
        total_read += bytes_read;
            if (total_read + read_size >= buffer_capacity) {
                buffer_capacity *= 2;
                char *new_buffer = realloc(buffer, buffer_capacity);
                buffer = new_buffer;
            }
        }
        buffer[total_read] = '\0';
        close(fd);
    }
    num_procs = sysconf(_SC_NPROCESSORS_ONLN);
    List *list = newList();
    char *token = strtok(buffer, ",");
    while(token != NULL){
        tailInsert(list, atoi(token));
        token = strtok(NULL, ",");
    }
    free(buffer);
    base_case = ceil((double)list->length / num_procs);
    printf("List length: %d\n", list->length);
    printf("Processor count: %d\n", num_procs);
    printf("Base case for parallelization: %d items\n", base_case);
    list = mergesort(list);
    printf("\nsorted list: ");
    printList(list);
    printf("\nThreads created for parallel sorting: %d\n", threads_created);
    return 0;
}

List *mergesort(List *list){
    if(list->length <= base_case){
        pthread_t thread;
        pthread_create(&thread, NULL, sorterThread, (void *)&list);
        pthread_join(thread, NULL);
        threads_created++;
        return list;
    }
    List *left = list;
    List *right;
    Split(left, &right);
    List *processed_left = mergesort(left);
    List *processed_right = mergesort(right);
    return merge(processed_left, processed_right);
}

List *merge(List *left, List *right){
    List *result = newList();
    while(left->length > 0 && right->length > 0){
        if(left->head->n <= right ->head->n){
            appendNode(result, extractNode(left, 0));
        }
        else{
            appendNode(result, extractNode(right, 0));
        }
    }
    if(left->length > 0){
        Node *leftTail = left->tail;
        result->tail->next = left->head;
        result->tail = leftTail;
        result->length += left->length;
        left->length = 0;
    }
    if(right->length > 0){
        Node *rightTail = right->tail;
        result->tail->next = right->head;
        result->tail = rightTail;
        result->length += right->length;
        right->length = 0;
    }
    free(left);
    free(right);
    return result;
}

void *sorterThread(void *arg){
    List **list = (List **)arg;
    *list = quicksort(*list);
}

List *quicksort(List *list){
    if(list->length <= 1){
        return list;
    }
    Node *pivot = extractNode(list, 0);
    List *left = newList();
    List *right = newList();
    while(list->length > 0){
        Node *current = extractNode(list, 0);
        if(current->n <= pivot->n){
            appendNode(left, current);
        }
        else{
            appendNode(right, current);
        }
    }
    free(list);
    left = quicksort(left);
    right = quicksort(right);
    appendNode(left, pivot);
    appendList(left, right);
    return left;
}