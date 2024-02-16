#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define sort_shell   0
#define sort_quick   1
#define sort_heap    2
#define sort_batcher 3
#define OPTIONS      "ahbsqr:n:p:H" //Nishant gave me the idea to use colons to refer to arguments

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   A collection of comparison-based sorting algorithms.\n"
        "\n"
        "USAGE\n"
        "   %s [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n"
        "\n"
        "OPTIONS\n"
        "   -H              Display program help and usage.\n"
        "   -a              Enable all sorts.\n"
        "   -s              Enable Shell Sort.\n"
        "   -b              Enable Batcher Sort.\n"
        "   -h              Enable Heap Sort.\n"
        "   -q              Enable Quick Sort.\n"
        "   -n length       Specify number of array elements (default: 100).\n"
        "   -p elements     Specify number of elements to print (default: 100).\n"
        "   -r seed         Specify random seed (default: 13371453).\n",
        exec);
}

int main(int argc, char **argv) {
    Set set = set_empty();

    Stats stats;

    uint32_t seed = 13371453; //does this work for the seed?
    uint32_t array_size = 100;
    uint32_t print_el = 100;
    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            set = set_insert(set, 0);
            set = set_insert(set, 3);
            set = set_insert(set, 2);
            set = set_insert(set, 1);
            break;
        case 's': set = set_insert(set, 0); break;
        case 'q': set = set_insert(set, 1); break;
        case 'h': set = set_insert(set, 2); break;
        case 'b': set = set_insert(set, 3); break;
        case 'n': array_size = strtoul(optarg, NULL, 10); break;
        case 'r':
            seed = strtoul(optarg, NULL, 10);
            srandom(seed);
            break;
        case 'p':
            print_el = strtoul(optarg, NULL, 10); //what to do for this case???
            break;
        default:
            usage(argv[0]); /* Invalid options, show usage */
            return EXIT_FAILURE;

        case 'H':
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms. \n");
            printf("\n");
            printf("USAGE\n");
            printf("   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed] \n");
            printf("\n");
            printf("OPTIONS\n");
            printf("   -H              Display program help and usage.\n");
            printf("   -a              Enable all sorts.\n");
            printf("   -s              Enable Shell Sort.\n");
            printf("   -b              Enable Batcher Sort.\n");
            printf("   -h              Enable Heap Sort.\n");
            printf("   -q              Enable Quick Sort.\n");
            printf("   -n length       Specify number of array elements (default: 100). \n");
            printf("   -p elements     Specify number of elements to print (default: 100). \n");
            printf("   -r seed         Specify random seed (default: 13371453).\n");
            break;
        }
    }
    if (print_el > array_size) {
        print_el = array_size;
    }

    if (argc < 2) { //John (TA) gave me this code if the user entered no inputs
        printf("Select at least one sort to perform. \n");
        usage(argv[0]);
    }

    //reset(&stats);

    uint32_t *list = calloc(array_size, sizeof(uint32_t)); //creates an array
    srandom(seed);
    for (uint32_t i = 0; i < array_size; i++) {
        list[i] = random() & ((1 << 30) - 1); //Lev gave me this code to bit-mask
    }

    reset(&stats);

    if (set_member(set, 0)) { //done
        shell_sort(&stats, list, array_size);
        printf("Shell Sort, %u elements, %lu moves, %lu compares \n", array_size, stats.moves,
            stats.compares);
        for (uint32_t i = 0; i < print_el; i++) {
            printf(("%13" PRIu32), list[i]);
            if (((i + 1) % 5) == 0) {
                printf("\n");
            }
        }
        if ((print_el % 5) != 0) {
            printf("\n");
        }
    }
    reset(&stats);

    srandom(seed);
    for (uint32_t i = 0; i < array_size; i++) {
        list[i] = random() & ((1 << 30) - 1); //Lev gave me this code to bit-mask
    }

    if (set_member(set, 3)) { //batcher-done
        batcher_sort(&stats, list, array_size);
        printf("Batcher Sort, %u elements, %lu moves, %lu compares \n", array_size, stats.moves,
            stats.compares);

        for (uint32_t i = 0; i < print_el; i++) {
            printf(("%13" PRIu32), list[i]);
            if (((i + 1) % 5) == 0) {
                printf("\n");
            }
        }
        if ((print_el % 5) != 0) {
            printf("\n");
        }
    }
    reset(&stats);

    srandom(seed);
    for (uint32_t i = 0; i < array_size; i++) {
        list[i] = random() & ((1 << 30) - 1); //Lev gave me this code to bit-mask
    }

    if (set_member(set, 2)) { //heap-done
        heap_sort(&stats, list, array_size);
        printf("Heap Sort, %u elements, %lu moves, %lu compares \n", array_size, stats.moves,
            stats.compares);
        for (uint32_t i = 0; i < print_el; i++) {
            printf(("%13" PRIu32), list[i]);
            if (((i + 1) % 5) == 0) {
                printf("\n");
            }
        }
        if ((print_el % 5) != 0) {
            printf("\n");
        }
    }
    reset(&stats);

    srandom(seed);
    for (uint32_t i = 0; i < array_size; i++) {
        list[i] = random() & ((1 << 30) - 1); //Lev gave me this code to bit-mask
    }

    if (set_member(set, 1)) { //quick
        quick_sort(&stats, list, array_size);
        printf("Quick Sort, %u elements, %lu moves, %lu compares \n", array_size, stats.moves,
            stats.compares);
        for (uint32_t i = 0; i < print_el; i++) {
            printf(("%13" PRIu32), list[i]);
            if (((i + 1) % 5) == 0) {
                printf("\n");
            }
        }
        if ((print_el % 5) != 0) {
            printf("\n");
        }
    }
    reset(&stats);

    free(list);
    return 0;
}
