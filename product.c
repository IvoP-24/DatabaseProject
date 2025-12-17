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
    int i, j;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No file found.\n");
        return;
    }

    struct Products products[1000];
    int count = 0;
    char line[1000];
    while (fgets(line, sizeof(line), file)) {
    if (sscanf(line, "%d,%[^,],%[^,],%[^,],%d,%d,%d,%[^,],%[^,],%d",
                   &products[count].product_id,
                   products[count].category,
                   products[count].brand,
                   products[count].product_name,
                   &products[count].year,
                   &products[count].ram,
                   &products[count].quantity,
                   products[count].cpu,
                   products[count].gpu,
                   &products[count].per_unit) == 10) {
            count++;
        }
    }

    fclose(file);

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (str_compare(criteria, "year") == 0) {
                if (products[j].year > products[j + 1].year) {
                    struct Products temp = products[j];
                    products[j] = products[j + 1];
                    products[j + 1] = temp;
                }
            } else if (str_compare(criteria, "price") == 0) {
                if (products[j].per_unit > products[j + 1].per_unit) {
                    struct Products temp = products[j];
                    products[j] = products[j + 1];
                    products[j + 1] = temp;
                }
            }
        }
    }

    if (count == 0) {
        printf("No products found to sort.\n");
        return;
    }

    overwrite(products, count, filename);

    if (str_compare(criteria, "year") == 0) {
        printf("--- Products Sorted by Year ---\n");
    } else if (str_compare(criteria, "price") == 0) {
        printf("--- Products Sorted by Price ---\n");
    } else {
        printf("Invalid sort type. Use 'year' or 'price'.\n");
        return;
    }

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
    }
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

void overwrite(struct Products *products, int num_products, char *filename) {
    if (num_products <= 0) {
        printf("File not modified, number of products is 0.\n");
        return;
    }
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
    struct Products product;
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
        printf("Invalid or incomplete arguments. Type --help for more information.\n");
        return -1;
    }
    return 0;
}
