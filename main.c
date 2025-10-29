#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Products{
    int product_id;
    char brand[50];
    char product_name[100];
    int quantity;
    int per_unit;
    char category[100];
    int year;
    int ram;
    char cpu[100];
    char gpu[100];
};

int get_last_id(char *filename);
void savefile(struct Products *products, int num_products, char *filename);
void overwrite(struct Products *products, int num_products, char *filename);
void printfile(char *filename);

int main(int argc, char * argv[]){
    struct Products *products = malloc(sizeof(struct Products));
    int i = 1;
    printf("--- Product Inventory Management ---\n");
    if (argc >  1 && strcmp(argv[1], "--help") == 0) {

        printf("Required 9 specifications : GPU = -g CPU = -c RAM = -r YEAR = -y BRAND = -b  QUANTITY = -q  PRICE PER UNIT = -p CATEGORY = -u PRODUCT NAME = -n\n");
        printf("Delete everything = -o\n");
        return-1;
        free(products); }
     else if (argc  == 1 ) {

        printf("Invalid command. Type --help for more information.\n");
        printf("\n--- Products ---\n");
        printfile("products.txt");

        return -1;
    }
    if (argc > 1) {

        struct Products product;
        int count = 0;

        for (int j = 1; j < argc; j++) {

            if (strcmp(argv[j], "-g") == 0) {
                strcpy(product.gpu, argv[++j]);
                count++;

            } else if (strcmp(argv[j], "-c") == 0) {
                strcpy(product.cpu, argv[++j]);
                count++;

            } else if (strcmp(argv[j], "-r") == 0) {
                product.ram = atoi(argv[++j]);
                count++;

            } else if (strcmp(argv[j], "-y") == 0) {
                product.year = atoi(argv[++j]);
                count++;

            } else if (strcmp(argv[j], "-b") == 0) {
                strcpy(product.brand, argv[++j]);
                count++;

            } else if (strcmp(argv[j], "-n") == 0) {
                strcpy(product.product_name, argv[++j]);
                count++;

            } else if (strcmp(argv[j], "-q") == 0 ) {
                product.quantity = atoi(argv[++j]);
                count++;

            } else if (strcmp(argv[j], "-p") == 0) {
                product.per_unit = atoi(argv[++j]);
                count++;

            } else if (strcmp(argv[j], "-u") == 0) {
                strcpy(product.category, argv[++j]);
                count++;

            }
            else if (strcmp(argv[j], "-o") == 0) {
            overwrite(products, 0, "products.txt");
            printf("All products deleted.\n");
        }
        }
        if(count == 9){

            int last_id = get_last_id("products.txt");
            product.product_id = get_last_id("products.txt") + 1; 
            products[0] = product;
            savefile(products, 1, "products.txt");
            printf("\n--- Product Saved ---\n");
            printfile("products.txt");
            free(products);
            return 0;

        } 
        else {
            printf("Invalid or incomplete arguments. Type --help for more information.\n");
            return -1;
        }
    }

    free(products);
    }   

void overwrite(struct Products *products, int num_products, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }
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
    if (file == NULL) 
        printf("The file is not opened.");
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
    if (file == NULL) {
        return 0; 
    }
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

