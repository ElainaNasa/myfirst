#include "calculate.h"
#include <stdio.h>

/**
 * @brief 计算每个学生的总分和平均分
 */
void calculate_student_scores() {
    char msg[256];

    MYSQL_RES *res;
    DBConfig config;
    DBConnection db;

    initDBConfig(&config, "localhost", "student", "11111111", "testdb", 3306);
    
    if (!dbConnect(&db, &config)) {
    printf("failed to connect to Database\n");
    return;
    }
    
    printf("\nStudent Total and Average Scores:\n");
    printf("---------------------------------\n");
    
    snprintf(msg, sizeof(msg),"Student Total and Average Scores");
    speak(msg);
    msg[0] = '\0';

    res = totalAndAveragePerStudent(&db);

    if (res != NULL) {
        MYSQL_ROW row = mysql_fetch_row(res);
    if(row == NULL) {
        printf("No data found for student scores.\n");
    }
    else{
        
        print_students_from_query(res);
        
    }
    } else {
        printf("Failed to retrieve student scores.\n");
        
        snprintf(msg, sizeof(msg),"Failed to retrieve student scores");
        speak(msg);
        msg[0] = '\0';
    }
/*
    for (int i = 0; i < student_count; i++) {
        STUDENT *stu = &students[i];
        float total = stu->score.ics + stu->score.pdp + stu->score.ds + stu->score.dl;
        float average = total / 4.0f;
        
        printf("%s (%s): Total = %.1f, Average = %.1f\n", 
               stu->stu_name, stu->stu_id, total, average);
    }
    printf("\n");
    */
}

/**
 * @brief 计算每门课程的平均分
 */
void calculate_course_averages() {
    char msg[256];

    MYSQL_RES *res;
    DBConfig config;
    DBConnection db;

    initDBConfig(&config, "localhost", "student", "11111111", "testdb", 3306);
    
    if (!dbConnect(&db, &config)) {
    printf("failed to connect to Database\n");
    return;
    }

    printf("\nCourse Average Scores:\n");
    printf("----------------------\n");
        
    snprintf(msg, sizeof(msg),"Course Average Scores");
    speak(msg);
    msg[0] = '\0';

    res = averagePerCourse(&db);
    if (res != NULL) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            printf("Computer Systems (iCS): %.1f\n", atof(row[0]));
            snprintf(msg, sizeof(msg),"Computer Systems (iCS): %.1f\n", atof(row[0]));
            speak(msg);
            msg[0] = '\0';

            printf("Programming Practice (PDP): %.1f\n", atof(row[1]));
            snprintf(msg, sizeof(msg),"Programming Practice (PDP): %.1f\n", atof(row[1]));
            speak(msg);
            msg[0] = '\0';

            printf("Data Structures (DS): %.1f\n", atof(row[2]));
            snprintf(msg, sizeof(msg),"Data Structures (DS): %.1f\n", atof(row[2]));
            speak(msg);
            msg[0] = '\0';

            printf("Digital Logic (DL): %.1f\n", atof(row[3]));
            snprintf(msg, sizeof(msg),"Digital Logic (DL): %.1f\n", atof(row[3]));
            speak(msg);
            msg[0] = '\0';
        } else {
            printf("No data found for course averages.\n");
            snprintf(msg, sizeof(msg),"No data found for course averages");
            speak(msg);
            msg[0] = '\0';
        }
    } else {
        printf("Failed to retrieve course averages.\n");
        snprintf(msg, sizeof(msg),"Failed to retrieve course averages");
        speak(msg);
        msg[0] = '\0';
    }   
    /*
    if (student_count == 0) {
        printf("No students to calculate course averages.\n");
         
        snprintf(msg, sizeof(msg),"No students to calculate course averages");
        speak(msg);
        msg[0] = '\0';

        return;
    }
    
    float ics_total = 0, pdp_total = 0, ds_total = 0, dl_total = 0;
    
    for (int i = 0; i < student_count; i++) {
        ics_total += students[i].score.ics;
        pdp_total += students[i].score.pdp;
        ds_total += students[i].score.ds;
        dl_total += students[i].score.dl;
    }
    
    float ics_avg = ics_total / student_count;
    float pdp_avg = pdp_total / student_count;
    float ds_avg = ds_total / student_count;
    float dl_avg = dl_total / student_count;
    
  

    printf("Computer Systems (iCS): %.1f\n", ics_avg);

    snprintf(msg, sizeof(msg),"Computer Systems (iCS): %.1f\n", ics_avg);
    speak(msg);
    msg[0] = '\0';

    printf("Programming Practice (PDP): %.1f\n", pdp_avg);

    snprintf(msg, sizeof(msg),"Programming Practice (PDP): %.1f\n", pdp_avg);
    speak(msg);
    msg[0] = '\0';

    printf("Data Structures (DS): %.1f\n", ds_avg);
    
    snprintf(msg, sizeof(msg),"Data Structures (DS): %.1f\n", ds_avg);
    speak(msg);
    msg[0] = '\0';

    printf("Digital Logic (DL): %.1f\n", dl_avg);
    
    snprintf(msg, sizeof(msg),"Digital Logic (DL): %.1f\n", dl_avg);
    speak(msg);
    msg[0] = '\0';

    printf("\n");
    */
}
