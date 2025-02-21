# Write a Shell Script to Calculate Sum of Integers from 1 to n

echo -n "Enter the number: "
read n

sum=0  # Initialize sum as 0

for ((i=1; i<=n; i++))  # Loop from 1 to n
do
    sum=$((sum + i))  # Add i to sum
done

echo "The sum of integers from 1 to $n is: $sum"


: <<'COMMENT'

SAMPLE OUTPUT

Enter the number: 5
The sum of integers from 1 to 5 is: 15

COMMENT
