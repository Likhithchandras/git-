#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "students.dat"
typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void menu();
void clearInput();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n=== Student Management program ===\n");
        printf("1. Add Student\n");
        printf("2. Display every Students\n");
        printf("3. Search Student by collegeID\n");
        printf("4. Delete Student by collegeID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInput();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}

void addStudent() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    clearInput();

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;  // Remove newline

    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    clearInput();

    fwrite(&s, sizeof(Student), 1, file);
    fclose(file);

    printf("Student added successfully.\n");
}

void displayStudents() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    Student s;
    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(Student), 1, file)) {
        printf("ID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n\n", s.marks);
    }

    fclose(file);
}

void searchStudent() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    clearInput();

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == id) {
            printf("Record Found:\n");
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }

    fclose(file);
}

void deleteStudent() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error opening temp file.\n");
        fclose(file);
        return;
    }

    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    clearInput();

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id != id) {
            fwrite(&s, sizeof(Student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("Student with ID %d deleted successfully.\n", id);
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

