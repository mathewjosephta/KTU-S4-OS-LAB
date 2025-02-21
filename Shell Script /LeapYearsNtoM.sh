# Write a Shell Script to print leap years from 1 to N
echo -n "Enter the starting year : "
read n
echo -n "Enter the ending year : "
read m

echo "Leap years from $n to $m are:"

for (( year=n; year<=m; year++ ))
do
    if (( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )); then
        echo $year
    fi
done


: <<'COMMENT'

SAMPLE OUTPUT

Enter the starting year : 2000
Enter the ending year : 2024
Leap years from 2000 to 2024 are:
2000
2004
2008
2012
2016
2020
2024

COMMENT
