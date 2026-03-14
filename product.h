#include <stdio.h>
#include <stdlib.h>

struct Products{
    int product_id;
    char *brand;
    char *product_name;
    int quantity;
    int per_unit;
    char *category;
    int year;
    int ram;
    char *cpu;
    char *gpu;
};
int function(struct Products *products, char *filename, int argc, char *argv[]);
int get_last_id(char *filename);
void savefile(struct Products *products, int num_products, char *filename);
void printfile(char *filename);
void filter_products(char *filename, char *field, char *value);
void sort_products(char *filename, char *criteria);
void str_copy(char *dest, char *src);
int str_compare(char *s1, char *s2);
