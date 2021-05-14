clear
mkdir 216792327_hongce_chen
cd 216792327_hongce_chen
echo '#include <stdio.h>
int main(){
    printf("%s\n","Hello World");
    return 0;
}' > helloWorld.c
gcc -o helloWorld helloWorld.c
./helloWorld > lab9.txt
echo "***************" >> lab9.txt
date '+Date = %m-%d-%y%n%H:%M:%S' >> lab9.txt
echo "***************" >> lab9.txt
wc -w lab9.txt >> lab9.txt
echo "***************" >> lab9.txt
cp lab9.txt findDif.txt
grep "hello world" lab9.txt > step8.txt
cat step8.txt >> lab9.txt
grep "Hello World" lab9.txt > step9.txt
cat step9.txt >> lab9.txt
echo "***************" >> lab9.txt
diff findDif.txt lab9.txt >> lab9.txt
echo "***************" >> lab9.txt
chmod 624 lab9.txt
ls -l lab9.txt >> lab9.txt
echo "***************" >> lab9.txt