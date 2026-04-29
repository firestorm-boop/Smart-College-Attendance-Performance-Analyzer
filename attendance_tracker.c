#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define SUBJECTS 3

struct Student {
    int roll;
    char name[50];
    float attendance;
    float marks[SUBJECTS];
};

void inputStudent(struct Student *s, int i) {
    printf("\nEnter details for Student %d:\n", i+1);
    printf("Roll No: "); scanf("%d", &s->roll);
    printf("Name: "); scanf("%s", s->name);
    printf("Attendance %%: "); scanf("%f", &s->attendance);
    for(int j=0; j<SUBJECTS; j++) {
        printf("Marks %d: ", j+1); scanf("%f", &s->marks[j]);
    }
}

float calcAverage(float marks[]) {
    float sum = 0;
    for(int i=0; i<SUBJECTS; i++) sum += marks[i];
    return sum / SUBJECTS;
}

char getGrade(float avg) {
    if(avg >= 90) return 'A+';
    if(avg >= 80) return 'A';
    if(avg >= 70) return 'B';
    if(avg >= 60) return 'C';
    return 'F';
}

int main() {
    struct Student students[MAX_STUDENTS];
    int n;
    printf("Enter number of students: "); scanf("%d", &n);
    
    for(int i=0; i<n; i++) {
        inputStudent(&students[i], i);
    }
    
    printf("\n--- SUMMARY ---\n");
    printf("Roll\tName\tAtt%%\tAvg\tGrade\n");
    int topper = 0;
    for(int i=0; i<n; i++) {
        float avg = calcAverage(students[i].marks);
        char grade = getGrade(avg);
        printf("%d\t%s\t%.1f\t%.1f\t%c\n", students[i].roll, students[i].name, 
               students[i].attendance, avg, grade);
        if(avg > calcAverage(students[topper].marks)) topper = i;
    }
    
    printf("\n--- SHORTAGE (<75%% Attendance) ---\n");
    for(int i=0; i<n; i++) {
        if(students[i].attendance < 75) {
            printf("%s (%.1f%%)\n", students[i].name, students[i].attendance);
        }
    }
    
    printf("\n--- TOPPER ---\n");
    float topAvg = calcAverage(students[topper].marks);
    printf("Roll: %d, Name: %s, Average: %.1f\n", students[topper].roll, 
           students[topper].name, topAvg);
    
    return 0;
}
