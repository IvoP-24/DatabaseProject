#include <stdio.h>
#include <stdlib.h>
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
int main(){

    int num_products;
    
    struct Products *productStatic = malloc(5 * sizeof(struct Products)); 
    productStatic[0] = (struct Products){1, "Apple", "MacBook Pro", 999, 1399, "Laptop", 2022, 16, "Apple M2 Pro", "Integrated"};
    productStatic[1] = (struct Products){2, "Dell", "XPS 15", 399, 1599, "Laptop", 2024, 32, "Intel Core i7-13700H", "NVIDIA RTX 4060"};
    productStatic[2] = (struct Products){3, "HP", "Envy x360", 100, 599, "Laptop", 2021, 16, "AMD Ryzen 7 7840U", "Integrated"};
    productStatic[3] = (struct Products){4, "Asus", "ROG Zephyrus G14", 500, 1399, "Laptop", 2025, 32, "AMD Ryzen 9 8945HS", "NVIDIA RTX 4070"};
    productStatic[4] = (struct Products){5, "Microsoft", "Surface Laptop 7", 600, 1799, "Laptop", 2024, 16, "Snapdragon X Elite", "Adreno"};
    

    for(int i = 0; i < 5; i++){
        printf("\n-------------------");
        printf("\n Unsorted array");
        printf("\nProduct ID: %d\n", productStatic[i].product_id);
        printf("Category: %s\n", productStatic[i].category);
        printf("Brand: %s\n", productStatic[i].brand);
        printf("Product Name: %s\n", productStatic[i].product_name);
        printf("Year: %d\n", productStatic[i].year);
        printf("RAM: %dGB\n", productStatic[i].ram);
        printf("CPU: %s\n", productStatic[i].cpu);
        printf("GPU: %s\n", productStatic[i].gpu);
        printf("Quantity in stock: %d\n", productStatic[i].quantity);
        printf("Price per unit: $%d\n", productStatic[i].per_unit);

    }

    struct Products temp;
    for (int i = 0; i < 5 - 1; i++) {
        for (int j = 0; j < 5 - i - 1; j++) {
            if (productStatic[j].year > productStatic[j + 1].year) {
                temp = productStatic[j];
                productStatic[j] = productStatic[j + 1];
                productStatic[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < 5; i++){
        printf("\n-------------------");
        printf("\n Sorted static array by year");
        printf("\nProduct ID: %d\n", productStatic[i].product_id);
        printf("Category: %s\n", productStatic[i].category);
        printf("Brand: %s\n", productStatic[i].brand);
        printf("Product Name: %s\n", productStatic[i].product_name);
        printf("Year: %d\n", productStatic[i].year);
        printf("RAM: %dGB\n", productStatic[i].ram);
        printf("CPU: %s\n", productStatic[i].cpu);
        printf("GPU: %s\n", productStatic[i].gpu);
        printf("Quantity in stock: %d\n", productStatic[i].quantity);
        printf("Price per unit: $%d\n", productStatic[i].per_unit);

    }

    printf("\nHow many products would you like to add:");
    scanf("%d",&num_products);
    struct Products *product = malloc(num_products * sizeof(struct Products));  
    
    for(int i = 0; i < num_products;i++){
        product[i].product_id = i;
        printf("\nEnter category:");
        scanf("%s",product[i].category);
        printf("\nEnter product name:");
        scanf("%s",product[i].product_name);
        printf("\nEnter product brand: ");
        scanf("%s",product[i].brand);
        printf("\nEnter year of manufacture:");
        scanf("%d",&product[i].year);
        printf("\nEnter product CPU:");
        scanf("%s",product[i].cpu);
        printf("\nEnter product GPU:");
        scanf("%s",product[i].gpu);
        printf("\nEnter product RAM in GB:");
        scanf("%d",&product[i].ram);
        printf("\nEnter quantity in stock:");
        scanf("%d",&product[i].quantity);
        printf("\nEnter price per unit:");
        scanf("%d",&product[i].per_unit);
    }
    
   
    for(int i = 0; i < num_products; i++){
        printf("\n-------------------");
        printf("\nUnsorted dynamic array by year");
        printf("\nProduct ID: %d\n", product[i].product_id);
        printf("Category: %s\n", product[i].category);
        printf("Brand: %s\n", product[i].brand);
        printf("Product Name: %s\n", product[i].product_name);
        printf("Year: %d\n", product[i].year);
        printf("RAM: %dGB\n", product[i].ram);
        printf("CPU: %s\n", product[i].cpu);
        printf("GPU: %s\n", product[i].gpu);
        printf("Quantity in stock: %d\n", product[i].quantity);
        printf("Price per unit: $%d\n", product[i].per_unit);

    }
    struct Products tempdynamic;
    for (int i = 0; i < num_products - 1; i++) {
        for (int j = 0; j < num_products - i - 1; j++) {
            if (product[j].year > product[j + 1].year) {
                tempdynamic = product[j];
                product[j] = product[j + 1];
                product[j + 1] = tempdynamic;
            }
        }
    }
     
    for(int i = 0; i < num_products; i++){
        printf("\n-------------------");
        printf("\nSorted dynamic array by year");
        printf("\nProduct ID: %d\n", product[i].product_id);
        printf("Category: %s\n", product[i].category);
        printf("Brand: %s\n", product[i].brand);
        printf("Product Name: %s\n", product[i].product_name);
        printf("Year: %d\n", product[i].year);
        printf("RAM: %dGB\n", product[i].ram);
        printf("CPU: %s\n", product[i].cpu);
        printf("GPU: %s\n", product[i].gpu);
        printf("Quantity in stock: %d\n", product[i].quantity);
        printf("Price per unit: $%d\n", product[i].per_unit);

    }
    free(product);
    free(productStatic);
return 0;
}
