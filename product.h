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
int function(struct Products *products, char *filename, int argc, char *argv[]);
int get_last_id(char *filename);
void savefile(struct Products *products, int num_products, char *filename);
void overwrite(struct Products *products, int num_products, char *filename);
void printfile(char *filename);
void sort_products(char *filename, char *criteria);
