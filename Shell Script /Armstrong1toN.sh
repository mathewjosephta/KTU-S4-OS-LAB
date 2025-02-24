# Write a Shell Script to Calculate Armstrong numbers between 1 to n

echo -n "Enter the upper limit: "
read n

echo "Armstrong numbers between 1 and $n are:"

for (( num=1; num<=n; num++ ))
do
    temp=$num
    digits=0
    sum=0

    # Find number of digits
    temp2=$temp
    while [ $temp2 -gt 0 ]
    do
        temp2=$((temp2 / 10))
        digits=$((digits + 1))
    done

    # Calculate sum of each digit raised to the power of digits
    temp=$num
    while [ $temp -gt 0 ]
    do
        d=$((temp % 10))
        sum=$(echo "$sum + $d^$digits" | bc)  # Using bc for power calculation
        temp=$((temp / 10))
    done

    # Check if the number is an Armstrong number
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
