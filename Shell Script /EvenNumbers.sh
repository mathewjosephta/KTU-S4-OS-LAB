# Write a Shell Script to print Even numbers between 1 to n

echo -n "Enter the value of n: "
read n

echo "Even numbers from 1 to $n are:"

for ((i=1; i<=n; i++))
do
    if (( i % 2 == 0 )); then  # Check if i is even
        echo $i
    fi
done


: <<'COMMENT'

SAMPLE OUTPUT

Enter the value of n: 20
Even numbers from 1 to 20 are:
2
4
6
8
10
12
14
16
18
20


COMMENT
