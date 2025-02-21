# Write a Shell Script to Calculate Factorial of a Number

echo -n "Enter the number: "
read n

f=1

for ((i=1; i<=n; i++))  # Loop from 1 to n
do
    f=$((f * i))  # Multiply f by i
done

echo "The Factorial of $n is: $f"

: <<'COMMENT'

SAMPLE OUTPUT

Enter the number: 5
The Factorial of 5 is: 120

COMMENT
