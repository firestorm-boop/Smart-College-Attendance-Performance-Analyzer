#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define DAYS 30
#define BASE_RATE 50.0

struct Student {
    int id;
    char name[50];
    char room[10];
    int attended[DAYS];
    float bill;
    int paid;
};

void inputAttendance(struct Student *s) {
    printf("\nStudent ID: "); scanf("%d", &s->id);
    printf("Name: "); scanf("%s", s->name);
    printf("Room: "); scanf("%s", s->room);
    int present;
    printf("Enter daily attendance (1=present, 0=absent) for %d days:\n", DAYS);
    int attended_days = 0;
    for(int d=0; d<DAYS; d++) {
        scanf("%d", &present);
        s->attended[d] = present;
        attended_days += present;
    }
    float rate = (attended_days <= DAYS - 5) ? BASE_RATE * 0.9 : BASE_RATE;
    s->bill = attended_days * rate;
    s->paid = 0;  // Initially unpaid
}

void markPaid(struct Student *s) {
    printf("Paid? (1=Yes, 0=No): ");
    scanf("%d", &s->paid);
}

int main() {
    struct Student students[MAX_STUDENTS];
    int n;
    printf("Number of students: "); scanf("%d", &n);
    
    for(int i=0; i<n; i++) {
        inputAttendance(&students[i]);
        markPaid(&students[i]);
    }
    
    printf("\n--- MESS BILL SUMMARY ---\n");
    printf("ID\tName\tRoom\tAttended Days\tBill (₹)\tStatus\n");
    float total_revenue = 0, collected = 0;
    for(int i=0; i<n; i++) {
        int attended_days = 0;
        for(int d=0; d<DAYS; d++) attended_days += students[i].attended[d];
        printf("%d\t%s\t%s\t%d\t\t%.2f\t\t%s\n", 
               students[i].id, students[i].name, students[i].room, 
               attended_days, students[i].bill,
               students[i].paid ? "Paid" : "Unpaid");
        total_revenue += students[i].bill;
        if(students[i].paid) collected += students[i].bill;
    }
    
    printf("\n--- UNPAID BILLS ---\n");
    for(int i=0; i<n; i++) {
        if(!students[i].paid) {
            printf("ID %d - %s: ₹%.2f\n", students[i].id, students[i].name, students[i].bill);
        }
    }
    
    printf("\nTotal Expected: ₹%.2f | Collected: ₹%.2f | Pending: ₹%.2f\n", 
           total_revenue, collected, total_revenue - collected);
    
    return 0;
}
