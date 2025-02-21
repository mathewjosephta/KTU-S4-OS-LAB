# Write a Shell Script to Check whether th given year is leap or not

echo -n "Enter a year: "
read year

if (( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )); then
    echo "It's a leap year"
else
    echo "Not a leap year"
fi

: <<'COMMENT'

SAMPLE OUTPUT

Enter a year: 2024
It's a leap year


COMMENT
