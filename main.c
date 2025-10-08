#include <stdio.h>
#include <stdlib.h>

struct Products{
    int product_id;
    char brand[50];
    char product_name[50];
    int quantity;
    int per_unit;
    char category[20];
    int year;
    int ram;
    char cpu[60];
    char gpu[60];
};
int main(){
    struct Products product[5] = {
        {1, "Apple", "MacBook Pro", 999, 1399, "Laptop", 2022, 16, "Apple M2 Pro", "Integrated"},
        {2, "Dell", "XPS 15", 399, 1599, "Laptop", 2024, 32, "Intel Core i7-13700H", "NVIDIA RTX 4060"},
        {3, "HP", "Envy x360", 100, 599, "Laptop", 2021, 16, "AMD Ryzen 7 7840U", "Integrated"},
        {4, "Asus", "ROG Zephyrus G14", 500, 1399, "Laptop", 2025, 32, "AMD Ryzen 9 8945HS", "NVIDIA RTX 4070"},
        {5, "Microsoft", "Surface Laptop 7", 600, 1799, "Laptop", 2024, 16, "Snapdragon X Elite", "Adreno"}
    };
    struct Products temp;
    int n = 5;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (product[j].year > product[j + 1].year) {
                temp = product[j];
                product[j] = product[j + 1];
                product[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < 5; i++){
        printf("Product ID: %d\n", product[i].product_id);
        printf("Brand: %s\n", product[i].brand);
        printf("Product Name: %s\n", product[i].product_name);
        printf("Quantity in stock: %d\n", product[i].quantity);
        printf("Price per unit: $%d\n", product[i].per_unit);
        printf("Category: %s\n", product[i].category);
        printf("Year: %d\n", product[i].year);
        printf("RAM: %dGB\n", product[i].ram);
        printf("CPU: %s\n", product[i].cpu);
        printf("GPU: %s\n", product[i].gpu);
        printf("\n");
    }


return 0;
}
