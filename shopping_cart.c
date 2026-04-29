#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 20
#define MAX_CART 100

struct Item {
    int id;
    char name[50];
    float price;
    int stock;
};

struct CartItem {
    int id;
    int qty;
    float total;
};

void displayItems(struct Item items[], int n) {
    printf("\n--- INVENTORY ---\nID\tName\tPrice\tStock\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%s\t₹%.2f\t%d\n", items[i].id, items[i].name, items[i].price, items[i].stock);
    }
}

float addToCart(struct Item items[], int n, struct CartItem cart[], int *cart_count) {
    int id, qty;
    printf("Enter Item ID: "); scanf("%d", &id);
    printf("Quantity: "); scanf("%d", &qty);
    
    for(int i=0; i<n; i++) {
        if(items[i].id == id && items[i].stock >= qty) {
            cart[*cart_count].id = id;
            cart[*cart_count].qty = qty;
            cart[*cart_count].total = items[i].price * qty;
            items[i].stock -= qty;
            (*cart_count)++;
            return items[i].price * qty;
        }
    }
    printf("Item not found or insufficient stock!\n");
    return 0;
}

float checkout(struct CartItem cart[], int cart_count) {
    float total = 0;
    printf("\n--- CART ---\nID\tQty\tTotal\n");
    for(int i=0; i<cart_count; i++) {
        printf("%d\t%d\t₹%.2f\n", cart[i].id, cart[i].qty, cart[i].total);
        total += cart[i].total;
    }
    if(total > 1000) total *= 0.9;  // 10% discount
    printf("Grand Total: ₹%.2f\n", total);
    return total;
}

int main() {
    struct Item inventory[MAX_ITEMS] = {
        {1, "Laptop", 50000, 5}, {2, "Mouse", 500, 20}, {3, "Keyboard", 1500, 10},
        // Add more up to 20...
    };
    int n = 3;  // Expand as needed
    struct CartItem cart[MAX_CART];
    int cart_count = 0;
    
    int choice;
    do {
        printf("\n1. View Items 2. Add to Cart 3. Checkout 0. Exit\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1: displayItems(inventory, n); break;
            case 2: addToCart(inventory, n, cart, &cart_count); break;
            case 3: checkout(cart, cart_count); break;
        }
    } while(choice);
    
    return 0;
}
