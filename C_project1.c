#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   //  Needed for random shuffle

int main() {

    int rows, cols, totalSeats, studentCount;    // vairable decleralation
    int i, r, c;  

    struct Student {                 // structure intaillazation
        char name[50];
        int roll;
        int seatRow;
        int seatCol;
    };

    struct Student *students = NULL;

    FILE *fp;                  // file pointer decleration

    printf("\n  welcome to our project \n");
    printf("\n Dynamic student seating allocator with file based histopry \n");

    printf("\nEnter number of rows in hall: ");    // hall intilazation
    scanf("%d", &rows);

    printf("\nEnter number of columns in hall: ");
    scanf("%d", &cols);

    totalSeats = rows * cols;       // for available seats

    printf("\nTotal seats available: %d\n", totalSeats);

    printf("\nEnter number of students: ");
    scanf("%d", &studentCount);

    if(studentCount > totalSeats) {              // condition for checking no of students are sufficient for seats
        printf("\n students is more than available seats \n");
        return 0;
    }

    students = malloc(studentCount * sizeof(struct Student));     // dynamic memory allocation

    printf("\nEnter student details:\n");

    
    for(i = 0; i < studentCount; i++) {         // for reading student details like name roll no

        printf("\nStudent %d:\n", i+1);
        printf("Enter Name: ");
        scanf("%s", students[i].name);

        again:
        printf("Enter Roll Number: ");
        scanf("%d", &students[i].roll);

        //  Check for duplicates
        for(int j=0; j<i; j++){
            if(students[j].roll == students[i].roll){
                printf(" Roll number already exists Enter another\n");
                goto again;
            }
        }
    }
    // SIMPLE RANDOM SHUFFLE 
    srand(time(NULL));   
    
    for(int k=studentCount-1; k>0; k--){       // Fisher-Yates shuffle logic
        int j = rand() % (k+1);

        int temp = students[k].roll;
        students[k].roll = students[j].roll;
        students[j].roll = temp;
    }


    //  AUTO SEAT ALLOCATION 
    int seatIndex = 0;

    for(r = 0; r < rows; r++) {
        for(c = 0; c < cols; c++) {
            if(seatIndex < studentCount) {
                students[seatIndex].seatRow = r + 1;
                students[seatIndex].seatCol = c + 1;
                seatIndex++;
            }
        }
    }

    //  DISPLAY SEATING 
    printf("\n      FINAL SEATING ARRANGEMENT         \n");

    for(i = 0; i < studentCount; i++) {
        printf("%d) %s | Roll: %d | Seat: Row %d, Col %d\n",
            i+1,
            students[i].name,
            students[i].roll,
            students[i].seatRow,
            students[i].seatCol
        );
    }

    
    printf("\n\n       HALL SEATING          \n\n");

    for(r = 0; r < rows; r++) {
        for(c = 0; c < cols; c++) {
            int found = 0;
            for(i = 0; i < studentCount; i++) {
                if(students[i].seatRow == r+1 && students[i].seatCol == c+1) {
                    printf("%3d ", students[i].roll);
                    found = 1;
                    break;
                }
            }
            if(!found) printf(" -- ");
        }
        printf("\n");
    }

    
    fp = fopen("seating_details.txt", "w");              // file creation for seating details

    fprintf(fp, "       STUDENT SEATING RECORD      \n");
    fprintf(fp, "Hall Size: %d Rows x %d Columns\n\n", rows, cols);

    for(i = 0; i < studentCount; i++) {
        fprintf(fp, "%d) Name: %s | Roll: %d | Seat: Row %d, Col %d\n",
            i+1,
            students[i].name,
            students[i].roll,
            students[i].seatRow,
            students[i].seatCol
        );
    }

    fprintf(fp, "\n\n        HALL VIEW        \n");

    for(r = 0; r < rows; r++) {
        for(c = 0; c < cols; c++) {
            int found = 0;
            for(i = 0; i < studentCount; i++) {
                if(students[i].seatRow == r+1 && students[i].seatCol == c+1) {
                    fprintf(fp, "%3d ", students[i].roll);
                    found = 1;
                    break;
                }
            }
            if(!found) fprintf(fp, " -- ");
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    printf("\n Seating data saved to: seating_details.txt\n");

    // SEARCH FEATURE
    int searchRoll;
    printf("\n Enter roll number to search seat: ");      // for searching seat by roll no
    scanf("%d", &searchRoll);

    int found = 0;
    for(i = 0; i < studentCount; i++){
        if(students[i].roll == searchRoll){
            printf("\n Seat Found!\nName: %s\nSeat: Row %d, Col %d\n",
                students[i].name, students[i].seatRow, students[i].seatCol);
            found = 1;
            break;
        }
    }

    if(!found){
        printf("\n Roll number not found.\n");
    }

    free(students);       // free allocated memory
    printf("\nProgram completed successfully\n");
    return 0;
    

}
