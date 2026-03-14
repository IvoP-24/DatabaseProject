#include "product.h"
#include <stdio.h>
#include <stdlib.h>


void str_copy(char *dest, char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int str_compare(char *s1, char *s2) {
    while (*s1 || *s2) {
        if (*s1 != *s2) return *s1 - *s2;
        s1++;
        s2++;
    }
    return 0;
}

void sort_products(char *filename, char *criteria) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No file found.\n");
        return;
    }

    int count = 0;
    char line[512];
    while (fgets(line, sizeof(line), file))
        count++;
    rewind(file);

    struct Products *products = malloc(count * sizeof(struct Products));
    int i = 0;
    while (i < count && fgets(line, sizeof(line), file)) {
        products[i].brand        = malloc(100);
        products[i].product_name = malloc(200);
        products[i].category     = malloc(100);
        products[i].cpu          = malloc(100);
        products[i].gpu          = malloc(100);
        sscanf(line, "%d,%[^,],%[^,],%[^,],%d,%d,%d,%[^,],%[^,],%d",
               &products[i].product_id,
               products[i].category, 
               products[i].brand,
               products[i].product_name, 
               &products[i].year, 
               &products[i].ram,
               &products[i].quantity, 
               products[i].cpu, 
               products[i].gpu, 
               &products[i].per_unit);
        i++;
    }
    fclose(file);

    for (i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int swap = 0;
            if (str_compare(criteria, "year") == 0 && products[j].year > products[j+1].year)
                swap = 1;
            if (str_compare(criteria, "price") == 0 && products[j].per_unit > products[j+1].per_unit)
                swap = 1;
            if (swap) {
                struct Products temp = products[j];
                products[j] = products[j+1];
                products[j+1] = temp;
            }
        }
    }

    printf("--- Sorted by %s ---\n", criteria);
    for (i = 0; i < count; i++) {
        printf("%d,%s,%s,%s,%d,%d,%d,%s,%s,%d\n",
               products[i].product_id, 
               products[i].category, 
               products[i].brand,
               products[i].product_name, 
               products[i].year, 
               products[i].ram,
               products[i].quantity, 
               products[i].cpu, 
               products[i].gpu, 
               products[i].per_unit);
        free(products[i].brand);
        free(products[i].product_name);
        free(products[i].category);
        free(products[i].cpu);
        free(products[i].gpu);
    }
    free(products);
}

void filter_products(char *filename, char *field, char *value) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No file found.\n");
        return;
    }

    char line[512];
    char category[512], brand[512];
    printf("--- Filter: %s = %s ---\n", field, value);
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%*d,%[^,],%[^,]", category, brand);
        if (str_compare(field, "category") == 0 && str_compare(category, value) == 0)
            printf("%s", line);
        if (str_compare(field, "brand") == 0 && str_compare(brand, value) == 0)
            printf("%s", line);
    }
    fclose(file);
}

void delete(struct Products *products, int num_products, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return;
    for (int i = 0; i < num_products; i++) {
        fprintf(file, "%d,%s,%s,%s,%d,%d,%d,%s,%s,%d\n",
                products[i].product_id,
                products[i].category, 
                products[i].brand,
                products[i].product_name, 
                products[i].year, 
                products[i].ram,
                products[i].quantity, 
                products[i].cpu, 
                products[i].gpu, 
                products[i].per_unit);
    }
    fclose(file);
}

void printfile(char *filename) {
    FILE *file = fopen(filename, "r");
    int c;
    while ((c = fgetc(file)) != EOF) putchar(c);
    fclose(file);
}

void savefile(struct Products *products, int num_products, char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) printf("The file is not opened.");
    for (int i = 0; i < num_products; i++) {
        fprintf(file, "%d,%s,%s,%s,%d,%d,%d,%s,%s,%d\n",
                products[i].product_id, products[i].category, products[i].brand,
                products[i].product_name, products[i].year, products[i].ram,
                products[i].quantity, products[i].cpu, products[i].gpu, products[i].per_unit);
    }
    fclose(file);
}

int get_last_id(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) return 0;
    int last_id = 0;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        int id;
        if (sscanf(line, "%d,", &id) == 1 && id > last_id)
            last_id = id;
    }
    fclose(file);
    return last_id;
}

int function(struct Products *products, char *filename, int argc, char *argv[]) {
    struct Products product = {0};
    product.brand        = malloc(100);
    product.product_name = malloc(200);
    product.category     = malloc(100);
    product.cpu          = malloc(100);
    product.gpu          = malloc(100);
    int count = 0;
    for (int j = 1; j < argc; j++) {
        if (str_compare(argv[j], "-g") == 0) {
            str_copy(product.gpu, argv[++j]);
            count++;
        } else if (str_compare(argv[j], "-c") == 0) {
            str_copy(product.cpu, argv[++j]);
            count++;
        } else if (str_compare(argv[j], "-r") == 0) {
            product.ram = atoi(argv[++j]);
            count++;
        } else if (str_compare(argv[j], "-y") == 0) {
            product.year = atoi(argv[++j]);
            count++;
        } else if (str_compare(argv[j], "-b") == 0) {
            str_copy(product.brand, argv[++j]);
            count++;
        } else if (str_compare(argv[j], "-n") == 0) {
            str_copy(product.product_name, argv[++j]);
            count++;
        } else if (str_compare(argv[j], "-q") == 0) {
            product.quantity = atoi(argv[++j]);
            count++;
        } else if (str_compare(argv[j], "-p") == 0) {
            product.per_unit = atoi(argv[++j]);
            count++;
        } else if (str_compare(argv[j], "-u") == 0) {
            str_copy(product.category, argv[++j]);
            count++;
        } else if (str_compare(argv[j], "-o") == 0) {
            delete(products, 0, filename);
            printf("All products deleted.\n");
        } else if (str_compare(argv[j], "--sort") == 0) {
            if (j + 1 < argc) {
                j++;
                if (str_compare(argv[j], "price") == 0) {
                    sort_products(filename, "price");
                    return 0;
                } else if (str_compare(argv[j], "year") == 0) {
                    sort_products(filename, "year");
                    return 0;
                } else {
                    printf("Unknown sort target: %s\n", argv[j]);
                    return -1;
                }
            } else {
                printf("Invalid sort argument\n");
                return -1;
            }
        } else if (str_compare(argv[j], "--filter") == 0) {
            filter_products(filename, argv[j+1], argv[j+2]);
            j += 2;
        } else if (str_compare(argv[j], "--print") == 0) {
            printf("\n--- Products ---\n");
            printfile(filename);
        }
    }

    if (count == 9) {
        product.product_id = get_last_id(filename) + 1;
        products[0] = product;
        savefile(products, 1, filename);
        printf("\n--- Product Saved ---\n");
        printfile(filename);
    } else {
        return -1;
    }
    return 0;
}
