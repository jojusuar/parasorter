# ParaSorter
Is a command line program created as an Operative Systems assignment, with the purpose of receiving a CSV-formatted string of integers and sort them through a parallel implementation of Merge-Sort and QuickSort, using the POSIX thread library.

The conceptual guidelines for the parallelization are given by [this article](https://www.selkie.macalester.edu/csinparallel/modules/ParallelSorting/build/html/MergeSort/MergeSort.html) by Macalester College.

## Compilation
From the root folder of the project, execute `$ make` in a Bash terminal.

## Usage
```
Usage: ./parasorter [option]
    No option:      Prompts user for input.
    -f: <filename>  Reads numbers from specified path.
    -h:             Shows this message.
```
## Author
[José Julio Suárez](https://github.com/jojusuar)

## External credits
Based on [Leyxargon](https://github.com/Leyxargon)'s [implementation of a linked list](https://github.com/Leyxargon/c-linked-list) in C.