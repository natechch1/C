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
*/

#include<stdio.h>
#include<stdlib.h>
#define IMAGE_SIZE 10


// this function prints the array
void printImgArray(int array[IMAGE_SIZE][IMAGE_SIZE])
{
  
    printf("------ Image Contents -------\n");
    for (int i=0; i<IMAGE_SIZE; i++)
    {
    for (int j=0; j<IMAGE_SIZE; j++)
        printf("%02d, ",array[i][j]);
    printf("\n");
    }
    printf("-----------------------------\n");
}

/**
 * This function counts the number of distinct 
 * number (i.e. the number of cells)
 **/
int cellCount(int image[IMAGE_SIZE][IMAGE_SIZE]){
    // insert your code for task1.1 here
    // you may want to change the return value. 
    int cell = 0; 
    for(int i = 0; i < IMAGE_SIZE; i++) {                    //this is to find the image number, let cell count = image number
        for(int j = 0; j < IMAGE_SIZE; j++) {
            if(cell > image[i][j]){
                cell = cell;
            }else{
                cell = image[i][j];                  
            }
        }
    } 
    return cell - 1;                                          //the image number is start from 2 so cell count = the largest image number - 1
}
/**
 * This function colors each cell with a unique color
 * (i.e. unique number)
 **/


int inRange(int row,int col){                                 //this helper method is used to make sure this direction is in ranged
    return row >= 0 && row < IMAGE_SIZE && col >= 0 && col < IMAGE_SIZE;
} 

//this helper method is used to find cell number 1 and change each cell from 1 to other number
void change(int image[IMAGE_SIZE][IMAGE_SIZE], int currentRow, int currentCol, int cellColor){
    int dCol[] = {1, 1, 1, 0, 0, -1, -1, -1, 1, 1, 1};            //direction of column found
    int dRow[] = {0, 0, 1, 1,-1, 0, 1, -1, 0, 1, -1};             //direction of row found
    image[currentRow][currentCol] = cellColor;
    int row;
    int col;
    for(int i = 0; i < 11; i++) {                            //i < 11 because sometimes one direction need more than one times to find 
        row = currentRow + dRow[i];                          //find the direction which around this image[currentRow][currentCol]
        col = currentCol + dCol[i];                          //find the direction which around this image[currentRow][currentCol]
        if(image[row][col] == 1 && inRange(row,col) == 1){   //find cell number 1
            image[row][col] = cellColor;                     //let the new cell point change to its cell number
            currentRow = row;                                //let this new cell point be the current direction and fing next cell number 1 which around current direction
            currentCol = col;                                //let this new cell point be the current direction and fing next cell number 1 which around current direction
            i = 0;                                           //use the new direction to find ohter 1 and change it
        }  
    }   
}

void color(int image[IMAGE_SIZE][IMAGE_SIZE]){
    // insert your code for task 1.2 here
    int startCell = 2;
    for(int i = 0; i < IMAGE_SIZE; i++){                     //row
        for(int j = 0; j < IMAGE_SIZE; j++){                 //column
           if(image[i][j] == 1){
            change(image,i,j,startCell++);                   //use helper method to change the cell number from 1 to other number
           }
        }
    }
}



/**
 * This function colors each cell with a unique color
 * (i.e., unique number). This function works with 
 * pointers
 * currentRow: shows the current row that is processed
 * currentCol: shows the current column that is process
 * currentIndex: show the index that is processed
 * color: is an integer that represents a color
 **/
 
 //this recursively helper method is used to change the cell number from 1 to other number
void changeRecursive(int image[IMAGE_SIZE][IMAGE_SIZE], int currentRow, int currentCol, int cellColor, int i){
    image[currentRow][currentCol] = cellColor;
    int row;
    int col;
    int dCol[] = {1, 1, 1, 0, 0, -1, -1, -1, 1, 1, 1};               //direction of column found
    int dRow[] = {0, 0, 1, 1,-1, 0, 1, -1, 0, 1, -1};                //direction of row found
    if(i < 11){
        row = currentRow + dRow[i];                                  //find the direction which around this image[currentRow][currentCol]
        col = currentCol + dCol[i];
        if(image[row][col] == 1 && inRange(row,col) == 1){           //find cell number 1
            changeRecursive(image,row,col,cellColor,0);              //use the new direction to find ohter 1 and change it
        }
        i++;
        changeRecursive(image,currentRow,currentCol,cellColor,i);    //find the other direction
    }
       
}

int colorRecursively(int image[IMAGE_SIZE][IMAGE_SIZE], int currentRow, int currentCol, int currentIndex, int color) {
    // insert your code for task 2.1 here, in case you decided to complete this task
    // you may want to change the return value
    color += 2;
    int cell = 0;
   
    for(int i = 0; i < IMAGE_SIZE; i++){                       //row
        for(int j = 0; j < IMAGE_SIZE; j++){                   //column
           if(image[i][j] == 1){
            changeRecursive(image,i,j,color++,0);              //use recursively helper method to change the cell number from 1 to other number
           }
        }
    }
    cell = cellCount(image);                                   //return the cell count of this function
    return cell; 
}

void colorPtr(int* image){
    // insert your code for task 2.2 here

}
 

#ifndef __testing
int main(){

    // DO not change anything in main(), it will confuse the
    // auto-checker.  
    puts("testing the code with color() function");
    int count = 0;
    int cellImg[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};

    printImgArray(cellImg);
    color(cellImg);
    printImgArray(cellImg);
    count=cellCount(cellImg);
    printf("Total number of cells in the image: %d\n",count);
 

    puts("Testing the code with colorPtr");
    int cellImg_[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};

    int* ptr = cellImg_;
    printImgArray(ptr);
    colorPtr(ptr);
    printImgArray(ptr);
    count=cellCount(ptr);
    printf("Total number of cells in the image: %d\n",count); 
    puts("Testing the code with colorRecursively");
    int cellImg__[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};
    printImgArray(cellImg__);
    colorRecursively(cellImg__, 0, 0, 1, 0);
    printImgArray(cellImg__);
    count=cellCount(cellImg__);
    printf("Total number of cells in the image: %d\n",count);
    return 0;
}
#endif