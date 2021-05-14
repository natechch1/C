#!/bin/bash
echo "xxx21
xyxzw
vveeww1
xy123 " > username.txt
echo "xxx21 100
xyxzw 90
vww1 85
vveeww1 80
xy123 70" > grades.txt
userN="username.txt"
gradeF="grades.txt"
while read -r user; do
grade=`grep $user $gradeF | cut -d " " -f 2`
>$user
echo "Dear $user" >> $user
echo "Your grade for this exam is $grade." >> $user
done < $userN