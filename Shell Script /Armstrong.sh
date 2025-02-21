# Write a Shell Script to check whether the given number is armstrong or not

#!/bin/bash

echo -n "Enter a number: "
read n
temp=$n
digits=${#n}  
sum=0        

while [ $temp -gt 0 ]  
do
    d=$((temp % 10))    
    sum=$((sum + d**digits))
    temp=$((temp / 10)) 
done

if [ $sum -eq $n ]  
then 
    echo "Number is an Armstrong number"
else
    echo "Number is not an Armstrong number"
fi


: <<'COMMENT'

SAMPLE OUTPUT

Enter a number: 153
Number is an Armstrong number

COMMENT
