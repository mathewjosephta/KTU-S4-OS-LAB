# Write a Shell Script to Calculate Armstrong numbers between 1 to n

echo -n "Enter the first number: "
read n
echo -n "Enter the second number: "
read m

sum=$((n + m))

echo "The sum is: $sum"


: <<'COMMENT'

SAMPLE OUTPUT

Enter a number: 153
Armstrong numbers up to 153 are:
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


COMMENT
