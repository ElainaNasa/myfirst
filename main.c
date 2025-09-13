#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include "student.h"
#include "fileop.h"
#include "sort.h"
#include "print.h"
#include "calculate.h"
#include "analysis.h"
#include "search.h"
#include "speak.h"
#include "menu.h"

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
