#include <stdio.h>


void savefile(struct Product *products, int num_products) {
    FILE *file = fopen("products.txt", "ab"); 
    if (file == 0) {
        printf("Unable to open file\n");
        return;
    }

    for (int i = 0; i < num_products; i++) {
        fwrite(&products[i], sizeof(struct Product), 1, file);
    }
    fclose(file);
}
