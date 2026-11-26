#include <stdio.h>
#include<string.h>
int nextID();
int applicationExists(int id);
void registration();
void verification();
void scheduling();
void tracking();
int nextID()
{
    FILE *fp;
    int id = 1000;
    fp = fopen("lastid.txt", "r");
    if (fp != NULL)
    {
        if (fscanf(fp, "%d", &id) != 1)
            id = 1000;
        fclose(fp);
    }
    id++;
    fp = fopen("lastid.txt", "w");
    if (fp == NULL)
    {
        printf("File Error!\n");
        return -1;
    }
    fprintf(fp, "%d", id);
    fclose(fp);
    return id;
}
int applicationExists(int id){
    FILE *fp;
    char filename[40];
    sprintf(filename, "app_%d.txt", id);
    fp = fopen(filename, "r");
    if (fp == NULL)
        return 0;
    fclose(fp);
    return 1;
}
void registration(){
    FILE *fp;
    int id;
    char filename[40];
    char docfile[40], datefile[40];
    char name[50], phone[15], address[100];
    int age;
    printf("\n--- APPLICANT REGISTRATION ---\n");
    id = nextID();
    if (id == -1)
        return;
    printf("Enter Name: ");
    scanf(" %49[^\n]", name);
    printf("Enter Age: ");
    scanf("%d", &age);
    if(age<=18){
        printf("registration not allowed");
        return ;
    }
    else{
        printf("Age eligible\n"); 
    }
    printf("Enter Phone: ");
    scanf("%14s", phone);
    printf("Enter Address: ");
    scanf(" %99[^\n]", address);
    sprintf(filename, "app_%d.txt", id);
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Unable to save details!\n");
        return;
    }
    fprintf(fp, "%s\n%d\n%s\n%s\n",
            name, age, phone, address);
    fclose(fp);
    sprintf(docfile, "doc_%d.txt", id);
    fp = fopen(docfile, "w");
    if (fp != NULL)
    {
        fprintf(fp, "Pending");
        fclose(fp);
    }
    sprintf(datefile, "date_%d.txt", id);
    fp = fopen(datefile, "w");
    if (fp != NULL)
    {
        fprintf(fp, "Not Scheduled");
        fclose(fp);
    }
    printf("\nRegistration Successful!\n");
    printf("Application ID: %d\n", id);
}
void verification(){
    FILE *fp;
    int id, choice;
    char filename[40];
    printf("\nEnter Application ID: ");
    scanf("%d", &id);
    if (applicationExists(id) == 0)
    {
        printf("Application Not Found!\n");
        return;
    }
    printf("\n1. Verify Documents\n");
    printf("2. Reject Documents\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    sprintf(filename, "doc_%d.txt", id);
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }
    if (choice == 1)
    {
        fprintf(fp, "Verified");
        printf("Documents Verified Successfully!\n");
    }
    else if (choice == 2)
    {
        fprintf(fp, "Rejected");
        printf("Documents Rejected!\n");
    }
    else
    {
        fprintf(fp, "Pending");
        printf("Invalid Choice!\n");
    }
    fclose(fp);
}
void scheduling(){
    FILE *fp;
    int id;
    char filename[40];
    char docfile[40];
    char status[20];
    char date[20];

    printf("\nEnter Application ID: ");
    scanf("%d", &id);
    if (applicationExists(id) == 0)
    {
        printf("Application Not Found!\n");
        return;
    }
    sprintf(docfile, "doc_%d.txt", id);
    fp = fopen(docfile, "r");
    if (fp == NULL)
        return;
    fscanf(fp, "%19s", status);
    fclose(fp);
    if (strcmp(status, "Verified") != 0)
    {
        printf("Documents Must Be Verified First!\n");
        return;
    }
    printf("Enter Appointment Date (DD-MM-YYYY): ");
    scanf("%19s", date);

    sprintf(filename, "date_%d.txt", id);

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }
    fprintf(fp, "%s", date);
    fclose(fp);

    printf("Appointment Scheduled Successfully!\n");
}
void tracking(){
    FILE *fp;
    int id;
    char filename[40];
    char docfile[40], datefile[40];
    char name[50], age[20];
    char phone[15], address[100];
    char status[20], date[30];

    printf("\nEnter Application ID: ");
    scanf("%d", &id);
    if (applicationExists(id) == 0)
    {
        printf("Application Not Found!\n");
        return;
    }
    sprintf(filename, "app_%d.txt", id);
    fp = fopen(filename, "r");
    if (fp == NULL)
        return;
    fgets(name, sizeof(name), fp);
    fgets(age, sizeof(age), fp);
    fgets(phone, sizeof(phone), fp);
    fgets(address, sizeof(address), fp);

    fclose(fp);
    sprintf(docfile, "doc_%d.txt", id);
    fp = fopen(docfile, "r");
    if (fp != NULL)
    {
        fscanf(fp, "%19s", status);
        fclose(fp);
    }
    else
        sprintf(status, "Pending");

    sprintf(datefile, "date_%d.txt", id);
    fp = fopen(datefile, "r");
    if (fp != NULL)
    {
        fscanf(fp, "%29s", date);
        fclose(fp);
    }
    else
        sprintf(date, "Not Scheduled");
    printf("\n--- APPLICATION DETAILS ---\n");
    printf("Application ID: %d\n", id);
    printf("Name: %s", name);
    printf("Age: %s", age);
    printf("Phone: %s", phone);
    printf("Address: %s", address);
    printf("Document Status: %s\n", status);
    printf("Appointment Date: %s\n", date);
}
int main(){
    int choice;
    do{
        printf("\n===== PASSPORT MANAGEMENT SYSTEM =====\n");
        printf("1. Applicant Registration\n");
        printf("2. Document Verification\n");
        printf("3. Appointment Scheduling\n");
        printf("4. Application Tracking\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                registration();
                break;
            case 2:
                verification();
                break;
            case 3:
                scheduling();
                break;
            case 4:
                tracking();
                break;
            case 5:
                printf("Thank You! Program Closed.\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 5);
    return 0;
}