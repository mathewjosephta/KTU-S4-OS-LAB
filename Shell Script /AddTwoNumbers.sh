# Write a Shell Script to Calculate Sum of Two Numbers

echo -n "Enter the first number: "
read n
echo -n "Enter the second number: "
read m

sum=$((n + m))

echo "The sum is: $sum"


: <<EOF
SAMPLE OUTPUT

Enter the first number: 10
Enter the second number: 20
The sum is: 30

EOF

