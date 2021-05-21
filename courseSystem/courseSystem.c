/* PLEASE DO NOT MODIFY A SINGLE STATEMENT IN THE TEXT BELOW.
READ THE FOLLOWING CAREFULLY AND FILL IN THE GAPS

I hereby declare that all the work that was required to 
solve the following problem including designing the algorithms
and writing the code below, is solely my own and that I received
no help in creating this solution and I have not discussed my solution 
with anybody. I affirm that I have read and understood
the Senate Policy on Academic honesty at 
https://secretariat-policies.info.yorku.ca/policies/academic-honesty-senate-policy-on/
and I am well aware of the seriousness of the matter and the penalties that I will face as a 
result of committing plagiarism in this assignment.

BY FILLING THE GAPS,YOU ARE SIGNING THE ABOVE STATEMENTS.

Full Name: Hongce Chen
Student Number: 216792327
Course Section: M
eecs user id: natechc1
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200


#define diskFile "diskFile.dat"
#define courseFile "course.txt"

struct db_type
{
   char name[fieldLength];
   int age;
   char course1[fieldLength];
   char course2[fieldLength];
   char status[fieldLength];
 };

struct courseInfo
{ 
  char code [20]; // e.g., EECS2030
  char title [fieldLength];
  char  date [20];
  char time_start [20];
  char time_end [20];
  char  location [20]; 
};
 
 
struct courseInfo courseArr[SIZE]; // global variable  array of struc
int dbLocation = 0;  // global variable  index for pArr

char prompt_menu(void);
void init_list(struct db_type * pArr[]); 
void clearDB(struct db_type * pArr[]);
void init_courseArr(void);
void displayCourses(void);
int timeConflict(int index1, int index2);       //helper function to check if there is a time conflict
int findCourse(struct db_type * pArr[dbLocation],char course[SIZE]);     //this is helper function to search the course name and store it in the pArr
void enterNew(struct db_type * pArr[SIZE]);
void displayDB(struct db_type * pArr[]);
int findRecord(struct db_type * pArr[], char student[], int r); //helper function for function removeRecord, r is index
void removeRecord (struct db_type * pArr[]);
void swap(struct db_type * pArr[]);
void sort(struct db_type * pArr[]);
void writeDisk(struct db_type * pArr[]); 
void emptyDisk(void); 
void loadDisk(struct db_type * pArr[]); 





int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    init_courseArr();  // load course from diskfile
    
    char choice;
    for(int i = 0; i < SIZE; i++){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
         case 'w': writeDisk(db_pArr);  break;    
         case 'l': loadDisk(db_pArr); break;
         case 's': sort(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
         case 'e': emptyDisk();break;

         case 'v': displayCourses();break;
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}

void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

void clearDB(struct db_type * pArr[]){
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
 
   fgets(c3,3,stdin);
   
   if(! strcmp(c3, "y\n"))  
      init_list(pArr);
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
    printf("|    %-20s","(L)oad disk");
    printf("%-20s","(W)rite disk");
    printf("(E)mpty disk\t|\n");
  
    printf("|    %-20s", "(V)iew courses");//|\tSwa(p) record\t(Q)uit\t\t\t\t|\n");
    printf("%-20s","(Q)uit");
    printf("*Case Insensitive*\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
   
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}

/* display all or specified course */
void displayCourses(void){   
  char courseName[SIZE];
  int count = 0;
  char after[SIZE];

  printf("Enter course code (or 'all')? ");
  fgets(courseName,50, stdin);
  courseName[strlen(courseName)-1] = '\0';

  
  strcpy(after,"EECS");
  strcat(after,courseName);

  if(strcmp(courseName,"all") == 0){
    printf("\n");
    printf("=================================================================================\n");
    while(strcmp(courseArr[count].code, "EECS0000") != 0){
      printf("%s\t%-40s%-5s %s-%s   %s\n",courseArr[count].code, courseArr[count].title, courseArr[count].date, courseArr[count].time_start, courseArr[count].time_end, courseArr[count].location);
      count++;
    }
    printf("==================================================================================\n");
    count = 0;
  }
  else{
    while(strcmp(courseArr[count].code, "EECS0000") != 0){
      if(strcmp(courseName,courseArr[count].code) == 0 || strcmp(after,courseArr[count].code) == 0){
        printf("%s\t%-40s%-5s %s-%s   %s\n",courseArr[count].code, courseArr[count].title, courseArr[count].date, courseArr[count].time_start, courseArr[count].time_end, courseArr[count].location);
        return;
      }
      count++;
    }
    printf("error! course does not exist\n");
  }
  // the provide PE2.out uses "%s\t%-40s%-5s %s-%s   %s\n" as formatting string for printing each course info   
}


/* helper function */
int timeConflict(int index1, int index2){
  int i, j;
  char* date1 = courseArr[index1].date;
  char* date2 = courseArr[index2].date;

  for(i = 0; i < strlen(date1); i++){
    for(j = 0; j < strlen(date2); j++){
      if(date1[i] == date2[j]){
        if(strcmp(courseArr[index1].time_start, courseArr[index2].time_end) >= 0 || strcmp(courseArr[index1].time_end, courseArr[index2].time_start) <= 0){
          printf("SUCCESSFUL! no time conflict\n");
          return 0;
        }
        else{
          printf("ATTENTION! time conflict\n");
          return 1;
        }
      }
    }
  }
  printf("SUCCESSFUL! no time conflict\n");
  return 0;
  
}

/* this is helper function to search the course name and store it in the pArr*/
int findCourse(struct db_type * pArr[],char course[SIZE]){
  int count = 0;
  char after[SIZE];
  
  strcpy(after, "EECS");
  strcat(after, course);
  
  while(strcmp(courseArr[count].code, "EECS0000") != 0){
    if(strcmp(course,courseArr[count].code) == 0 || strcmp(after,courseArr[count].code) == 0){
      return count;
    }
    count++;
  }
  printf("course does not exist, enter again: ");
  fgets(course,50, stdin);
  course[strlen(course)-1] = '\0';
  return findCourse(pArr,course);
}

/* input items into the list */
void enterNew(struct db_type * pArr[SIZE]){  
  char courseName1[SIZE], courseName2[SIZE], name[SIZE], c;
  int age;
  int time = 0;
  int index = 0;
  int index1 = 0;
  int index2 = 0;

  if(pArr[0] == NULL){
    dbLocation = 0;
  }

  pArr[dbLocation] = (struct db_type *) malloc(sizeof(struct db_type));
  printf("name: ");
  fgets(name, 100, stdin); 
  name[strlen(name)-1] = '\0';
  strcpy(pArr[dbLocation]->name, name);

  printf("age: ");
  scanf("%d", &age);
  pArr[dbLocation]->age = age;
  c = getchar();
  while(c != '\n' && c != EOF) {
    c = getchar();
  }

  printf("course-1: ");
  fgets(courseName1,50, stdin);
  courseName1[strlen(courseName1)-1] = '\0';
  index = findCourse(pArr, courseName1);
  index1 = index;
  sprintf(pArr[dbLocation]->course1,"%s\t%-40s%-5s %s-%s   %s", courseArr[index].code, courseArr[index].title, courseArr[index].date, courseArr[index].time_start, courseArr[index].time_end, courseArr[index].location);
  


  printf("course-2: ");
  fgets(courseName2,50, stdin);
  courseName2[strlen(courseName2)-1] = '\0';
  index = findCourse(pArr, courseName2);
  index2 = index;
  sprintf(pArr[dbLocation]->course2,"%s\t%-40s%-5s %s-%s   %s", courseArr[index].code, courseArr[index].title, courseArr[index].date, courseArr[index].time_start, courseArr[index].time_end, courseArr[index].location);

  time = timeConflict(index1,index2);
  if(time == 0){
    strcpy(pArr[dbLocation]->status, "SUCCESSFUL! no time conflict");
  }
  else{
    strcpy(pArr[dbLocation]->status, "ATTENTION! time conflict");  
  }
  
   dbLocation++;
}

/* display records */
void displayDB(struct db_type * pArr[]){
  int i;
  
  printf("\n");
  printf("================================\n");
  if(pArr[0] != NULL){
    for(i = 0; i < dbLocation; i++){
      printf("name: %s\n", pArr[i]->name);
      printf("age: %d\n", pArr[i]->age);
      printf("course1: %s\n", pArr[i]->course1);
      printf("course2: %s\n", pArr[i]->course2);
      printf("remarks: %s\n", pArr[i]->status);
      printf("\n");
    }
  }
  else{
    dbLocation = 0;
  }
  printf("===========%d records ===========\n", dbLocation);
  
}

/* helper function for removeRecord, r is index*/
int findRecord(struct db_type * pArr[], char student[], int r)
{
  if(pArr[r] == NULL){
    return -1;
  } 
  if(strcmp(pArr[r]->name, student) == 0){
     return r;
  }
  else {
    return findRecord(pArr, student, r+1);
  }
}

/* remove an existing item */
void removeRecord (struct db_type * pArr[]){ 
  int i;
  int flag = 0;
  char studentName[SIZE], tempcpy[SIZE];

  printf("enter full name to remove: ");
  fgets(studentName,50, stdin);
  studentName[strlen(studentName)-1] = '\0';
  strcpy(tempcpy, studentName);
  flag = findRecord(pArr, tempcpy, 0);

  if(flag == -1){
    printf("record not found\n");
  }
  else{
    i = flag;
    while(1){
      if(pArr[i+1] == NULL){
        pArr[i] = NULL;
        dbLocation--;
        break;
      }
      pArr[i] = pArr[i+1];
      i++;
    }
    printf("record [%s] removed successfully.\n", tempcpy);
  }
}

/* swap records */
void swap(struct db_type * pArr[]){
  int i;
  struct db_type * temp[SIZE];
  init_list(temp);

  if(dbLocation % 2 == 0){
    for(i = 0; i < dbLocation; i+=2){
      temp[0] = pArr[i];
      pArr[i] = pArr[i+1];
      pArr[i+1] = temp[0];
    }
  }
  else{
    for(i = 0; i < dbLocation; i+=2){
      if(i + 1 == dbLocation){
        break;
      }
      temp[0] = pArr[i];
      pArr[i] = pArr[i+1];
      pArr[i+1] = temp[0];
    }
  }
	
} 

/* load from course.txt, store into (global) array of courses  */
void init_courseArr(void){ 
 
   FILE *fr; //file pointer
   fr = fopen (courseFile, "r");
   char arr[50];  
   int count = 0;
   while ((fgets(arr,100,fr)) != NULL)
   {  
     strncpy(courseArr[count].code,  arr, strlen(arr)-1); // remove \n  
     courseArr[count].code[strlen(arr)-1] = '\0';  //to be safe
	 
     fgets(arr,100,fr);  
     strncpy(courseArr[count].title ,  arr, strlen(arr)-1);
     courseArr[count].title[strlen(arr)-1] = '\0';  //to be safe
     
          
     fgets(arr,100,fr); 
     strncpy(courseArr[count].date,  arr, strlen(arr)-1);
     courseArr[count].date[strlen(arr)-1] = '\0';  //to be safe
	   
     // other ways, remove \n before
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_start,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_end,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].location,  arr); 
	  
     count++;
     fgets(arr,100,fr); // read the empty line
   }

   strcpy(courseArr[count].code, "EECS0000"); // a terminator token structure

   fclose(fr);
	 
 }
    
/************************ DISK IO *****************************************************************/

void writeDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;

  if ( (fp=fopen(diskFile,"ab")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  
  for (i=0; i< SIZE ; i++)
  {
     if ( pArr[i] != NULL)
     {  
       if (fwrite( pArr[i], sizeof(struct db_type), 1, fp) != 1)
       { 
          printf("file write error\n");
       }
     } 
   }
   fclose(fp);

}

void emptyDisk(void){

  FILE *fp;
  
  char c3[3];
  printf("are you sure to empty disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;
 
  //else
  if ( (fp = fopen(diskFile,"w")) == NULL)
  {
     printf("no file to open\n");
     return;
  }
  fclose(fp); // open close, will empty the file
}


void loadDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;
  char c3[3];
  printf("will overwrite current records. are you sure to load disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;

  struct db_type * tmp;  
  
  if ( (fp = fopen(diskFile,"r")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  init_list(pArr);
  for (i=0; i < SIZE ; i++)
  {    
     
     tmp =  (struct db_type *) malloc (sizeof(struct db_type));   
	   
     if (fread( tmp, sizeof(struct db_type), 1, fp) != 1)
     {
       if (feof(fp))
       { fclose(fp); 
         return;
       }
       printf("file read error\n");
     }
     else pArr[i] = tmp;
  }
}

/****bonus*************************************************************************************/

/* sort the records by ages */
void sort(struct db_type * pArr[])
{
  int i,j;
  struct db_type * temp[SIZE];
  init_list(temp);

  if(pArr[0] != NULL){
    for(i = 0; i < dbLocation; i++){
      for(j = i + 1; j <= dbLocation; j++){
        if(pArr[j] == NULL){
          break;
        }
        if(pArr[j]->age < pArr[i]->age){
          temp[0] = pArr[i];
          pArr[i] = pArr[j];
          pArr[j] = temp[0];
        }
      }
    }
  }
}  

 
 
