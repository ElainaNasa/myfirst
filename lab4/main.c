#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "student.h"
#include "fileop.h"
#include "sort.h"
#include "print.h"
#include "calculate.h"
#include "analysis.h"
#include "search.h"

// 函数声明
void display_menu();
void append_record();
void search_by_name_menu();
void search_by_id_menu();
void modify_by_id();
void delete_by_id();
void sort_by_course_menu();
void save_to_text_file_menu();
void load_from_text_file_menu();
void save_to_binary_file_menu();
void load_from_binary_file_menu();

int main() {
    init_students();
    int choice;
    
    printf("=== Student Grade Management System ===\n");
    
    while (1) {
        display_menu();
        printf("Please enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // 清除输入缓冲区
            continue;
        }
        
        switch (choice) {
            case 0:
                printf("Exiting system. Goodbye!\n");
                return 0;
            case 1:
                append_record();
                break;
            case 2:
                search_by_name_menu();
                break;
            case 3:
                search_by_id_menu();
                break;
            case 4:
                modify_by_id();
                break;
            case 5:
                delete_by_id();
                break;
            case 6:
                calculate_student_scores();
                break;
            case 7:
                calculate_course_averages();
                break;
            case 8:
                sort_by_course_menu();
                break;
            case 9:
                analyze_course_grades();
                break;
            case 10:
                save_to_text_file_menu();
                break;
            case 11:
                load_from_text_file_menu();
                break;
            case 12:
                save_to_binary_file_menu();
                break;
            case 13:
                load_from_binary_file_menu();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        printf("\n");
    }
    
    return 0;
}

void display_menu() {
    printf("\n=== Menu ===\n");
    printf("1. Append record\n");
    printf("2. Search by name\n");
    printf("3. Search by ID\n");
    printf("4. Modify by ID\n");
    printf("5. Delete by ID\n");
    printf("6. Calculate total and average score of every student\n");
    printf("7. Calculate average score of every course\n");
    printf("8. Sort in descending order by course score\n");
    printf("9. Statistic analysis for every course\n");
    printf("10. Save to text file\n");
    printf("11. Load from text file\n");
    printf("12. Save to binary file\n");
    printf("13. Load from binary file\n");
    printf("0. Exit\n");
}

void append_record() {
    if (student_count >= MAX_STUDENTS) {
        printf("Error: Maximum number of students (%d) reached.\n", MAX_STUDENTS);
        return;
    }
    
    STUDENT new_student;
    printf("\nEnter student information:\n");
    
    printf("Student ID: ");
    scanf("%s", new_student.stu_id);
    
    printf("Name: ");
    scanf("%s", new_student.stu_name);
    
    printf("Computer Systems (iCS) score: ");
    scanf("%f", &new_student.score.ics);
    
    printf("Programming Practice (PDP) score: ");
    scanf("%f", &new_student.score.pdp);
    
    printf("Data Structures (DS) score: ");
    scanf("%f", &new_student.score.ds);
    
    printf("Digital Logic (DL) score: ");
    scanf("%f", &new_student.score.dl);
    
    students[student_count] = new_student;
    student_count++;
    
    printf("Student record added successfully.\n");
}

void search_by_name_menu() {
    char name[NAME_LENGTH];
    printf("Enter name to search: ");
    scanf("%s", name);
    
    int index = search_by_name(name);
    if (index != -1) {
        printf("\nStudent found:\n");
        print_header();
        print_student(&students[index]);
    } else {
        printf("Student with name '%s' not found.\n", name);
    }
}

void search_by_id_menu() {
    char id[ID_LENGTH];
    printf("Enter ID to search: ");
    scanf("%s", id);
    
    int index = search_by_id(id);
    if (index != -1) {
        printf("\nStudent found:\n");
        print_header();
        print_student(&students[index]);
    } else {
        printf("Student with ID '%s' not found.\n", id);
    }
}

void modify_by_id() {
    char id[ID_LENGTH];
    printf("Enter student ID to modify: ");
    scanf("%s", id);
    
    int index = search_by_id(id);
    if (index == -1) {
        printf("Student with ID '%s' not found.\n", id);
        return;
    }
    
    STUDENT *stu = &students[index];
    printf("\nCurrent information:\n");
    print_header();
    print_student(stu);
    
    printf("\nEnter new information (press Enter to keep current value):\n");
    
    char buffer[100];
    printf("Name [%s]: ", stu->stu_name);
    getchar(); // 清除缓冲区
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%s", stu->stu_name);
    }
    
    printf("Computer Systems (iCS) score [%.1f]: ", stu->score.ics);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &stu->score.ics);
    }
    
    printf("Programming Practice (PDP) score [%.1f]: ", stu->score.pdp);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &stu->score.pdp);
    }
    
    printf("Data Structures (DS) score [%.1f]: ", stu->score.ds);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &stu->score.ds);
    }
    
    printf("Digital Logic (DL) score [%.1f]: ", stu->score.dl);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &stu->score.dl);
    }
    
    printf("Student record modified successfully.\n");
}

void delete_by_id() {
    char id[ID_LENGTH];
    printf("Enter student ID to delete: ");
    scanf("%s", id);
    
    int index = search_by_id(id);
    if (index == -1) {
        printf("Student with ID '%s' not found.\n", id);
        return;
    }
    
    printf("\nDeleting student:\n");
    print_header();
    print_student(&students[index]);
    
    // 移动后续元素
    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    
    student_count--;
    printf("Student record deleted successfully.\n");
}

void sort_by_course_menu() {
    printf("\nSelect course to sort by:\n");
    printf("1. Computer Systems (iCS)\n");
    printf("2. Programming Practice (PDP)\n");
    printf("3. Data Structures (DS)\n");
    printf("4. Digital Logic (DL)\n");
    printf("Enter choice: ");
    
    int choice;
    scanf("%d", &choice);
    
    SORT_OPTION option;
    switch (choice) {
        case 1: option = SORT_BY_ICS; break;
        case 2: option = SORT_BY_PDP; break;
        case 3: option = SORT_BY_DS; break;
        case 4: option = SORT_BY_DL; break;
        default:
            printf("Invalid choice.\n");
            return;
    }
    
    sort_students_by_course(option);
    printf("\nStudents sorted by selected course:\n");
    print_all_students();
}

void save_to_text_file_menu() {
    char filename[100];
    printf("Enter filename to save (e.g., scoresheet.txt): ");
    scanf("%s", filename);
    
    if (save_to_text_file(filename) == 0) {
        printf("Data saved to %s successfully.\n", filename);
    } else {
        printf("Failed to save data to %s.\n", filename);
    }
}

void load_from_text_file_menu() {
    char filename[100];
    printf("Enter filename to load: ");
    scanf("%s", filename);
    
    if (load_from_text_file(filename) == 0) {
        printf("Data loaded from %s successfully.\n", filename);
        printf("Loaded %d student records.\n", student_count);
    } else {
        printf("Failed to load data from %s.\n", filename);
    }
}

void save_to_binary_file_menu() {
    char filename[100];
    printf("Enter filename to save: ");
    scanf("%s", filename);
    
    if (save_to_binary_file(filename) == 0) {
        printf("Data saved to %s successfully.\n", filename);
    } else {
        printf("Failed to save data to %s.\n", filename);
    }
}

void load_from_binary_file_menu() {
    char filename[100];
    printf("Enter filename to load: ");
    scanf("%s", filename);
    
    if (load_from_binary_file(filename) == 0) {
        printf("Data loaded from %s successfully.\n", filename);
        printf("Loaded %d student records.\n", student_count);
    } else {
        printf("Failed to load data from %s.\n", filename);
    }
}
