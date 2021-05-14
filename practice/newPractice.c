#include <stdio.h>
#include <string.h>
int total(char str[], int start, int end){
    if(start == end) return str[start] - 48;
    return (str[start] - 48) + total(str,start + 2, end);
}

void main() {
  
   printf("%s  %4.1f\n", "EECS2030",3.0);
   printf("%s\t%4.1f\n", "EECS2030",3.0);
    //printf("%d\n", total(str, 0, strlen(str) - 1));

}


