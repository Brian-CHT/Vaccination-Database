#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define STRING_SIZE 20

typedef struct people {                   // declaring this struct type globally
    char firstname[STRING_SIZE];
    char lastname[STRING_SIZE];
    char dob[STRING_SIZE];
    char vaccinevendor[STRING_SIZE];
    char vaccinationstatus[STRING_SIZE];
    char vaccinationdate[STRING_SIZE];
    char underlyingcondition[STRING_SIZE];
    int id;
} people;      // declaring the nuig array of structs of type

int count = 0; // Setting this variable as global so it can be used across functions
people* load_data();
int display_menu();
people* add_new_record();
int view_all_records();
int modify_record();
int display_seniors_with_condition();
int save_data();
int display_percent_unvaccinated();
int sort_vaccinated_by_name();
int sort_unvaccinated_by_name();
int sort_vaccinated_by_date();

int main(){
    int n, i;
    char choice;
    load_data();
      while(choice != '9'){
        display_menu();
        scanf("%s", &choice);
        switch(choice){
            case '1':
                add_new_record();
                break;
            case '2':
                view_all_records();
                break;
            case '3':
                modify_record();
            case '4':
                sort_vaccinated_by_name();
                break;
            case '5':
                sort_unvaccinated_by_name();
                break;
            case '6':
                sort_vaccinated_by_date();
                break;
            case '7':
                display_percent_unvaccinated();
                break;
            case '8':
                display_seniors_with_condition();
                break;
            case '9':
                save_data();
                printf("\nYou have chosen to exit. Goodbye!\n");
                break;
            default:
                printf("\nError, this does not match any of the options\n");
                printf("You will be redirected to the start of the menu\n\n\n");
            }
          }
      return 0;
  }

people* load_data(){
    int i;
    char c;
    count =0;
    FILE *fptr;
    people* nuig = malloc(count * sizeof(people));
    if((fptr = fopen("records.txt", "r+")) == NULL) {
        printf("This file does not exist\n");
        printf("It will be created for you. You will need to add records to the file through the menu.\n");

    } else{
    while(!feof(fptr)){
    c = fgetc(fptr);
        if(c == '\n'){
            count++;
        }
    }
    rewind(fptr);
    for(i = 0; i<count; i++){
    fscanf(fptr,"%s%s%s%s%s%s%s%d", nuig[i].firstname, nuig[i].lastname, nuig[i].dob, nuig[i].vaccinevendor, nuig[i].vaccinationstatus, nuig[i].vaccinationdate, nuig[i].underlyingcondition, &nuig[i].id);
    }

    fclose(fptr);
    }
    return nuig;
}

int display_menu(){
    printf("\t\tMAIN MENU\n");
    printf("***Please choose from one of the following options***\n\n");
    printf("1. Add a new person\n");
    printf("2. view vaccincation status for all students and staff\n");
    printf("3. Modify existing record\n");
    printf("4. Sort vaccinated people by name\n");
    printf("5. Sort unvaccinated people by name\n");
    printf("6. Sort vaccinated people by date\n");
    printf("7. Display percentage of unvaccinated people\n");
    printf("8. Display a list of people with an underlying condition older than 65\n");
    printf("9. Exit\n\n");
    return 0;
}

people* add_new_record(){
    count = count + 1;
    people* nuig = realloc(nuig, (count * sizeof(people)));
    printf("You have chosen to add a new record\n");
    printf("Please enter the details for the person and press enter after each variable\n");
    printf("first Name\nlast Name\nDate of Birth(Format yyyy/dd/mm)\nvaccine vendor\nvaccination status\nvaccination date\nunderlying condition\nid\n");
    scanf("%s %s %s %s %s %s %s %d",nuig[count].firstname, nuig[count].lastname, nuig[count].dob, nuig[count].vaccinevendor, nuig[count].vaccinationstatus, nuig[count].vaccinationdate, nuig[count].underlyingcondition, &nuig[count].id);
    printf("The details of the person you entered are as follows: \nName:%s\n lastName:%s\n dob:%s\n vaccinationvendor:%s\n vaccinationStatus%s\n vaccinationDate%s\n underlying condition%s\n id%d\n", nuig[count].firstname, nuig[count].lastname, nuig[count].dob, nuig[count].vaccinevendor, nuig[count].vaccinationstatus, nuig[count].vaccinationdate, nuig[count].underlyingcondition, nuig[count].id);
    printf("You will now be returned to the main menu\n\n");
    FILE *fptr;
    fptr = fopen("records.txt", "a");    // Appending it to file at this point so its not forgotten about!
    fprintf(fptr,"%s %s %s %s %s %s %s %d\n",nuig[count].firstname, nuig[count].lastname, nuig[count].dob, nuig[count].vaccinevendor, nuig[count].vaccinationstatus, nuig[count].vaccinationdate, nuig[count].underlyingcondition, nuig[count].id);
    fclose(fptr);
    return nuig;
}

int view_all_records(){
  int i;
  people* nuig = load_data();
  printf("\nYou have chosen to view all records\n\n");
  printf("%-10s|%-10s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10s\n", "first Name", "last Name", "dob", "vaccine vendor", "vaccination Status", "vaccination date", "underlying condition", "Staff/Student id");
  for(i=0; i< count; i++){
    printf("%-10s|%-10s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10d\n", nuig[i].firstname, nuig[i].lastname, nuig[i].dob, nuig[i].vaccinevendor, nuig[i].vaccinationstatus, nuig[i].vaccinationdate, nuig[i].underlyingcondition, nuig[i].id);
}

  return 0;
}

int modify_record(){
  int record, i,n;
  people* nuig = load_data();
  printf("You have chosen to modify a record\n");
  printf("Please enter the persons id number\n");
  scanf("%d", &record);
  for(i=0; i< count; i++){
        if( nuig[i].id == record){
        printf("The current details of the person you entered are as follows: \nName:%s\n lastName:%s\n dob:%s\n vaccinationvendor:%s\n vaccinationStatus:%s\n vaccinationDate:%s\n underlying condition:%s\n id:%d\n", nuig[i].firstname, nuig[i].lastname, nuig[i].dob, nuig[i].vaccinevendor, nuig[i].vaccinationstatus, nuig[i].vaccinationdate, nuig[i].underlyingcondition, nuig[i].id);
        printf("You can now modify this record. Please enter the details for the person and press enter after each variable\n");
        printf("first Name\nlast Name\nDate of Birth(Format dd/mm/yyyy)\nvaccine vendor\nvaccination status\nvaccination date\nunderlying condition\nid\n");
        scanf("%s %s %s %s %s %s %s %d",nuig[i].firstname, nuig[i].lastname, nuig[i].dob, nuig[i].vaccinevendor, nuig[i].vaccinationstatus, nuig[i].vaccinationdate, nuig[i].underlyingcondition, &nuig[i].id);
        printf("The new details of the person you entered are as follows: \nName:%s\n lastName:%s\n dob:%s\n vaccinationvendor:%s\n vaccinationStatus:%s\n vaccinationDate:%s\n underlying condition:%s\n id:%d\n", nuig[i].firstname, nuig[i].lastname, nuig[i].dob, nuig[i].vaccinevendor, nuig[i].vaccinationstatus, nuig[i].vaccinationdate, nuig[i].underlyingcondition, nuig[i].id);
        printf("\nYou will now be returned to the main menu\n");
        }
  }
  FILE *fptr;
  fptr = fopen("records.txt", "r+");
  for(int n=0; n<count; n++){
  fprintf(fptr,"%s %s %s %s %s %s %s %d\n",nuig[n].firstname, nuig[n].lastname, nuig[n].dob, nuig[n].vaccinevendor, nuig[n].vaccinationstatus, nuig[n].vaccinationdate, nuig[n].underlyingcondition, nuig[n].id);
  }
  fclose(fptr);
  return 0;
}

int sort_vaccinated_by_name(void){
    int i, j;
    people* temp = malloc(count * sizeof(people));
    people* nuig = load_data();
    for(i=0;i<count;i++)
      for(j=i+1;j<count;j++){
         if(strcmp(nuig[i].lastname,nuig[j].lastname)>0){
             temp[i] = nuig[i];
             nuig[i] = nuig[j];
             nuig[j] = temp[i];
         }
      }
    for(int k=0; k <count; k++){
        if(strcmp(nuig[k].vaccinationstatus, "N" ) != 0){
            printf("%-10s|%-12s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10s\n", "first Name", "last Name", "dob", "vaccine vendor", "vaccination Status", "vaccination date", "underlying condition", "Staff/Student id");
            printf("%-10s|%-12s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10d\n", nuig[k].firstname, nuig[k].lastname, nuig[k].dob, nuig[k].vaccinevendor, nuig[k].vaccinationstatus, nuig[k].vaccinationdate, nuig[k].underlyingcondition, nuig[k].id);
        }
    }
    free(temp);
    return 0;
}

int sort_unvaccinated_by_name(void){
    int i, j;
    people* temp = malloc(count * sizeof(people));
    people* nuig = load_data();
    for(i=0;i<count;i++)
      for(j=i+1;j<count;j++){
         if(strcmp(nuig[i].lastname,nuig[j].lastname)>0){
             temp[i] = nuig[i];
             nuig[i] = nuig[j];
             nuig[j] = temp[i];
         }
      }
    for(int k=0; k <count; k++){
        if((strcmp(nuig[k].vaccinationstatus, "Y" ) != 0) && nuig[k].id != 0){
            printf("%-10s|%-10s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10s\n", "first Name", "last Name", "dob", "vaccine vendor", "vaccination Status", "vaccination date", "underlying condition", "Staff/Student id");
            printf("%-10s|%-10s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10d\n", nuig[k].firstname, nuig[k].lastname, nuig[k].dob, nuig[k].vaccinevendor, nuig[k].vaccinationstatus, nuig[k].vaccinationdate, nuig[k].underlyingcondition, nuig[k].id);
        }
    }
    free (temp);
    return 0;
}

int sort_vaccinated_by_date(void){
    int i, j;
    people* temp = malloc(count * sizeof(people));
    people* nuig = load_data();
    for(i=0;i<count;i++)
      for(j=i+1;j<count;j++){
         if(strcmp(nuig[i].vaccinationdate,nuig[j].vaccinationdate)>0){
             temp[i] = nuig[i];
             nuig[i] = nuig[j];
             nuig[j] = temp[i];
         }
      }
    for(int k=0; k <count; k++){
        if((strcmp(nuig[k].vaccinationstatus, "Y" ) == 0) && nuig[k].id != 0){
            printf("%-10s|%-10s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10s\n", "first Name", "last Name", "dob", "vaccine vendor", "vaccination Status", "vaccination date", "underlying condition", "Staff/Student id");
            printf("%-10s|%-10s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10d\n", nuig[k].firstname, nuig[k].lastname, nuig[k].dob, nuig[k].vaccinevendor, nuig[k].vaccinationstatus, nuig[k].vaccinationdate, nuig[k].underlyingcondition, nuig[k].id);
        }
    }
    free(temp);
    return 0;
}

int display_percent_unvaccinated(void){
    people* nuig = load_data();
    int unvacc =0;
    double percentage;
    for(int i=0; i< count; i++){
        if((strcmp(nuig[i].vaccinationstatus, "Y") != 0) && nuig[i].id != 0){
            unvacc++;
        }
    }
    percentage = (int)unvacc / (double)count;
    printf("The percent unvaccinated is %lf\n", percentage);
    return 0;
}

int display_seniors_with_condition(void){
    int i,j, k;
    people* nuig = load_data();
    people* temp = malloc(count * sizeof(people));
     for(k=0;k<count;k++)
      for(j=k+1;j<count;j++){
         if(strcmp(nuig[i].vaccinationdate,nuig[j].vaccinationdate)>0){
             temp[k] = nuig[k];
             nuig[k] = nuig[k];
             nuig[k] = temp[k];
         }
      }
    for(int i =0; i< count; i++){
        if((strcmp(nuig[i].underlyingcondition, "none") != 0) && ((strncmp(nuig[i].dob, "1957", 4)) < 0)){
        printf("%-10s|%-10s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10s\n", "first Name", "last Name", "dob", "vaccine vendor", "vaccination Status", "vaccination date", "underlying condition", "Staff/Student id");
        printf("%-10s|%-10s|%-10s|%-16s|%-19s|%-16s|%-20s|%-10d\n", nuig[i].firstname, nuig[i].lastname, nuig[i].dob, nuig[i].vaccinevendor, nuig[i].vaccinationstatus, nuig[i].vaccinationdate, nuig[i].underlyingcondition, nuig[i].id);
        }
    }
    free(temp);
    return 0;
}

int save_data(void){
  FILE *fptr;
  people* nuig = load_data();
  fptr = fopen("records.txt", "r+");
  for(int n=0; n<count; n++){
  fprintf(fptr,"%s %s %s %s %s %s %s %d\n",nuig[n].firstname, nuig[n].lastname, nuig[n].dob, nuig[n].vaccinevendor, nuig[n].vaccinationstatus, nuig[n].vaccinationdate, nuig[n].underlyingcondition, nuig[n].id);
  }
  fclose(fptr);
  free(nuig);    // Free the array
  return 0;
}




