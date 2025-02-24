# Write a Shell Script to Calculate Armstrong numbers between 1 to n

#!/bin/bash

echo -n "Enter the upper limit: "
read n

echo "Armstrong numbers between 1 and $n are:"

for (( num=1; num<=n; num++ ))
do
    digits=${#num}  # Count the number of digits
    sum=0
    temp=$num

    while [ $temp -gt 0 ]
    do
        d=$((temp % 10))   # Get last digit
        sum=$((sum + d**digits))  # Raise it to power of digits and add to sum
        temp=$((temp / 10))  # Remove last digit
    done

    if [ $sum -eq $num ]
    then
        echo $num
    fi
done




: <<'COMMENT'

SAMPLE OUTPUT

Enter the upper limit: 500
Armstrong numbers between 1 and 500 are:
1
2
3
4
5
6
7
8
9
153
370
371
407

COMMENT
