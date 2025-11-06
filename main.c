#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
int main(int argc, char * argv[]){
    struct Products *products = malloc(sizeof(struct Products));
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    if (argc >  1 && strcmp(argv[1], "--help") == 0) {

        printf("Required 9 specifications :\nGPU = -g \nCPU = -c \nRAM = -r YEAR = -y \nBRAND = -b  \nQUANTITY = -q  \nPRICE PER UNIT = -p \nCATEGORY = -u \nPRODUCT NAME = -n\n");
        printf("--------------------------------\n");
        printf("External commands:\n");
        printf("Delete everything = -o\n");
        printf("Sort = --sort price/year\n");
        printf("Print inventory : --print\n");
        printf("--------------------------------\n");
        return-1;
        free(products); }
     else if (argc  == 1 ) {

        printf("Invalid command. Type --help for more information.\n");
            free(products);

        return -1;
    }
    if (argc > 1) {

      function(products, "products.txt", argc, argv);
    }
    free(products);
    }   

