# Write a Shell Script to Calculate sum of Digits of a Number

echo -n "Enter the number: "
read n

sum=0

while [ $n -gt 0 ]  
do
    d=$((n % 10))    
    sum=$((sum + d))
    n=$((n / 10))    
done

echo "The sum of digits is: $sum"



: <<'COMMENT'

SAMPLE OUTPUT

Enter the number: 56
The sum of digits is: 11

COMMENT
