#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mysql/mysql.h>
#include "student.h"
#include "fileop.h"
#include "sort.h"
#include "print.h"
#include "calculate.h"
#include "analysis.h"
#include "search.h"
#include "speak.h"

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
    char msg[256];
    init_students();
    int choice;
    
    printf("=== Student Grade Management System ===\n");
    
    while (1) {
        display_menu();
        printf("Please enter your choice: ");
        sleep(0.1);
        snprintf(msg, sizeof(msg),"Please enter your choice");
        speak(msg);
        msg[0] = '\0';

        
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
    char msg[256];
    int returnValue = 0;
    
    if (student_count >= MAX_STUDENTS) {
        printf("Error: Maximum number of students (%d) reached.\n", MAX_STUDENTS);
        return;
    }
    
    STUDENT new_student;
    printf("\nEnter student information:\n");

    snprintf(msg, sizeof(msg),"Enter student information");
    speak(msg);
    msg[0] = '\0';

    printf("Student ID: ");
    scanf("%s", new_student.stu_id);
    
    printf("Name: ");
    scanf("%s", new_student.stu_name);
    
    printf("Computer Systems (iCS) score: ");
    if((returnValue = scanf("%f", &new_student.score.ics)) != 1){
        printf("Invalid input for score. Please enter a valid number.\n");
        snprintf(msg, sizeof(msg),"Invalid input for score. Please enter a valid number");
        speak(msg);
        msg[0] = '\0';
        sleep(2);
        while (getchar() != '\n'); // 清除输入缓冲区
        return;
    };

    
    printf("Programming Practice (PDP) score: ");
    
     if((returnValue = scanf("%f", &new_student.score.pdp)) != 1){
        printf("Invalid input for score. Please enter a valid number.\n");
        snprintf(msg, sizeof(msg),"Invalid input for score. Please enter a valid number");
        speak(msg);
        msg[0] = '\0';
        sleep(1);
        while (getchar() != '\n'); // 清除输入缓冲区
        return;
    };
    
    printf("Data Structures (DS) score: ");
    
    if((returnValue = scanf("%f", &new_student.score.ds)) != 1){
        printf("Invalid input for score. Please enter a valid number.\n");
        snprintf(msg, sizeof(msg),"Invalid input for score. Please enter a valid number");
        speak(msg);
        msg[0] = '\0';
        sleep(1);
        while (getchar() != '\n'); // 清除输入缓冲区
        return;
    };

    printf("Digital Logic (DL) score: ");

    if((returnValue = scanf("%f", &new_student.score.dl)) != 1){
        printf("Invalid input for score. Please enter a valid number.\n");
        snprintf(msg, sizeof(msg),"Invalid input for score. Please enter a valid number");
        speak(msg);
        msg[0] = '\0';
        sleep(1);
        while (getchar() != '\n'); // 清除输入缓冲区
        return;
    };

    students[student_count] = new_student;
    student_count++;
    
    printf("Student record added successfully.\n");

    snprintf(msg, sizeof(msg),"Student record added successfully");
    speak(msg);
    msg[0] = '\0';

}

void search_by_name_menu() {
    char msg[256];
    char name[NAME_LENGTH];
    printf("Enter name to search: ");
    
    strcpy(msg, "Enter name to search: ");
    speak(msg);
    msg[0] = '\0';

    scanf("%s", name);
    
    int index = search_by_name(name);
    if (index != -1) {
        printf("\nStudent found:\n");

        snprintf(msg, sizeof(msg),"Student %s found", name);
        speak(msg);
        msg[0] = '\0';

        print_header();
        print_student(&students[index]);
        
    } else {
        printf("Student with name '%s' not found.\n", name);
        snprintf(msg, sizeof(msg),"Student %s not found", name);
        speak(msg);
        msg[0] = '\0';
    }
}

void search_by_id_menu() {
    char msg[256];  
    char id[ID_LENGTH];
    printf("Enter ID to search: ");

    snprintf(msg, sizeof(msg),"Enter ID to search");
    speak(msg);
    msg[0] = '\0';

    scanf("%s", id);
    
    int index = search_by_id(id);
    if (index != -1) {
        printf("\nStudent found:\n");

        snprintf(msg, sizeof(msg),"Student %s found", id);
        speak(msg);
        msg[0] = '\0';
        
        print_header();
        print_student(&students[index]);
    } else {
        printf("Student with ID '%s' not found.\n", id);

        snprintf(msg, sizeof(msg),"Student with ID '%s' not found", id);
        speak(msg);
        msg[0] = '\0';
    }
}

void modify_by_id() {
    char msg[256];

    char id[ID_LENGTH];
    printf("Enter student ID to modify: ");

    snprintf(msg, sizeof(msg),"Enter student ID to modify");
    speak(msg);
    msg[0] = '\0';

    scanf("%s", id);
    
    int index = search_by_id(id);
    if (index == -1) {
        printf("Student with ID '%s' not found.\n", id);

        snprintf(msg, sizeof(msg),"Student with ID '%s' not found", id);
        speak(msg);
        msg[0] = '\0';

        return;
    }
    
    STUDENT *stu = &students[index];
    printf("\nCurrent information:\n");

    snprintf(msg, sizeof(msg),"Current information");
    speak(msg);
    msg[0] = '\0';

    print_header();
    print_student(stu);
    
    printf("\nEnter new information (press Enter to keep current value):\n");

    snprintf(msg, sizeof(msg),"Enter new information (press Enter to keep current value)");
    speak(msg);
    msg[0] = '\0';
    
    char buffer[100];
            
    snprintf(msg, sizeof(msg),"Name %s", stu->stu_name);
    speak(msg);
    msg[0] = '\0';

    printf("Name [%s]: ", stu->stu_name);
    getchar(); // 清除缓冲区
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%s", stu->stu_name);
    }
        
    snprintf(msg, sizeof(msg),"Computer Systems (iCS) score %.1f", stu->score.ics);
    speak(msg);
    msg[0] = '\0';
    
    printf("Computer Systems (iCS) score [%.1f]: ", stu->score.ics);

    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &stu->score.ics);
    }

    snprintf(msg, sizeof(msg),"Programming Practice (PDP) score %.1f ", stu->score.pdp);
    speak(msg);
    msg[0] = '\0';

    printf("Programming Practice (PDP) score [%.1f]: ", stu->score.pdp);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &stu->score.pdp);
    }
    
    printf("Data Structures (DS) score [%.1f]: ", stu->score.ds);
    
    snprintf(msg, sizeof(msg),"Data Structures (DS) score %.1f", stu->score.ds);
    speak(msg);
    msg[0] = '\0';
    
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &stu->score.ds);
    }
        
    snprintf(msg, sizeof(msg),"Digital Logic (DL) score %.1f", stu->score.dl);
    speak(msg);
    msg[0] = '\0';

    printf("Digital Logic (DL) score [%.1f]: ", stu->score.dl);

    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &stu->score.dl);
    }
    
    printf("Student record modified successfully.\n");
    
    snprintf(msg, sizeof(msg),"Student record modified successfully.\n");
    speak(msg);
    msg[0] = '\0';

    
}

void delete_by_id() {
    char msg[256];    
    char id[ID_LENGTH];
    printf("Enter student ID to delete: ");

    snprintf(msg, sizeof(msg),"Enter student ID to delete: ");
    speak(msg);
    msg[0] = '\0';

    scanf("%s", id);
    
    int index = search_by_id(id);
    if (index == -1) {
        printf("Student with ID '%s' not found.\n", id);
        
        snprintf(msg, sizeof(msg),"Student with ID '%s' not found.\n", id);
        speak(msg);
        msg[0] = '\0';

        return;
    }
    
    printf("\nDeleting student:\n");
    print_header();
    print_student(&students[index]);
    
    snprintf(msg, sizeof(msg),"Deleting student: %s", id);
    speak(msg);
    msg[0] = '\0';

    
    // 移动后续元素
    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    
    student_count--;
    printf("Student record deleted successfully.\n");
    
    snprintf(msg, sizeof(msg),"Student record deleted successfully.\n");
    speak(msg);
    msg[0] = '\0';

}

void sort_by_course_menu() {
    char msg[256];

    printf("\nSelect course to sort by:\n");
         
    snprintf(msg, sizeof(msg),"Select course to sort by");
    speak(msg);
    msg[0] = '\0';

    printf("1. Computer Systems (iCS)\n");

         
    snprintf(msg, sizeof(msg),"1. Computer Systems (iCS)");
    speak(msg);
    msg[0] = '\0';

    printf("2. Programming Practice (PDP)\n");

         
    snprintf(msg, sizeof(msg),"2. Programming Practice (PDP)");
    speak(msg);
    msg[0] = '\0';

    printf("3. Data Structures (DS)\n");
         
    snprintf(msg, sizeof(msg),"3. Data Structures (DS)");
    speak(msg);
    msg[0] = '\0';

    printf("4. Digital Logic (DL)\n");
    
         
    snprintf(msg, sizeof(msg),"4. Digital Logic (DL)");
    speak(msg);
    msg[0] = '\0';

    printf("Enter choice: ");
         
    snprintf(msg, sizeof(msg),"Enter choice: ");
    speak(msg);
    msg[0] = '\0';

    
    
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
        
    snprintf(msg, sizeof(msg),"Students sorted by selected course");
    speak(msg);
    msg[0] = '\0';

    print_all_students();
}

void save_to_text_file_menu() {
    char msg[256];
    char filename[100];
    printf("Enter filename to save (e.g., scoresheet.txt): ");
     
    snprintf(msg, sizeof(msg),"Enter filename to save (e.g. scoresheet.txt)");
    speak(msg);
    msg[0] = '\0';


    scanf("%s", filename);
    
    if (save_to_text_file(filename) == 0) {
        printf("Data saved to %s successfully.\n", filename);

        snprintf(msg, sizeof(msg),"Enter filename to save (e.g. scoresheet.txt)");
        speak(msg);
        msg[0] = '\0';

    } else {
        printf("Failed to save data to %s.\n", filename);
        
        snprintf(msg, sizeof(msg),"Failed to save data to %s", filename);
        speak(msg);
        msg[0] = '\0';

    }
}

void load_from_text_file_menu() {
    char msg[256];
    char filename[100];
   
    snprintf(msg, sizeof(msg),"Enter filename to load:");
    speak(msg);
    msg[0] = '\0';

    printf("Enter filename to load: ");

    scanf("%s", filename);
    
    if (load_from_text_file(filename) == 0) {
        printf("Data loaded from %s successfully.\n", filename);

        printf("Loaded %d student records.\n", student_count);

        snprintf(msg, sizeof(msg),"Data loaded from %s successfully", filename);
        speak(msg);
        msg[0] = '\0';

        snprintf(msg, sizeof(msg),"Loaded %d student records.\n", student_count);
        speak(msg);
        msg[0] = '\0';

    } else {
        printf("Failed to load data from %s.\n", filename);

        snprintf(msg, sizeof(msg),"Failed to load data from %s.\n", filename);
        speak(msg);
        msg[0] = '\0';
    }
}

void save_to_binary_file_menu() {
    char msg[256];
    char filename[100];
    printf("Enter filename to save: ");

    snprintf(msg, sizeof(msg),"Enter filename to save");
    speak(msg);
    msg[0] = '\0';

    scanf("%s", filename);
    
    if (save_to_binary_file(filename) == 0) {
        printf("Data saved to %s successfully.\n", filename);
        
        snprintf(msg, sizeof(msg),"Data saved to %s successfully.\n", filename);
        speak(msg);
        msg[0] = '\0';

    } else {
        printf("Failed to save data to %s.\n", filename);

        snprintf(msg, sizeof(msg),"Failed to save data to %s.\n", filename);
        speak(msg);
        msg[0] = '\0';

    }
}

void load_from_binary_file_menu() {
    char msg[256];
    char filename[100];
    printf("Enter filename to load: ");

    snprintf(msg, sizeof(msg),"Enter filename to load");
    speak(msg);
    msg[0] = '\0';

    scanf("%s", filename);
    
    if (load_from_binary_file(filename) == 0) {
        printf("Data loaded from %s successfully.\n", filename);
        printf("Loaded %d student records.\n", student_count);
        
        snprintf(msg, sizeof(msg),"Data loaded from %s successfully.Loaded %d student records.\n", filename, student_count);
        speak(msg);
        msg[0] = '\0';

    } else {
        printf("Failed to load data from %s.\n", filename);

        snprintf(msg, sizeof(msg),"Failed to load data from %s.\n", filename);
        speak(msg);
        msg[0] = '\0';

    }
}
