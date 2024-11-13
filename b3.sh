#!/bin/bash

# Function to perform addition
add() {
    result=$(echo "$1 + $2" | bc)
    echo "Result: $result"
}

# Function to perform subtraction
subtract() {
    result=$(echo "$1 - $2" | bc)
    echo "Result: $result"
}

# Function to perform multiplication
multiply() {
    result=$(echo "$1 * $2" | bc)
    echo "Result: $result"
}

# Function to perform division
divide() {
    if [ "$2" -eq 0 ]; then
        echo "Error: Division by zero is not allowed!"
    else
        result=$(echo "scale=2; $1 / $2" | bc)
        echo "Result: $result"
    fi
}

# Main program
echo "Enter first number:"
read -r num1

echo "Enter second number:"
read -r num2

echo "Choose an operation (+, -, *, /):"
read -r operator

# Validate input
if ! [[ "$num1" =~ ^-?[0-9]+(\.[0-9]+)?$ ]] || ! [[ "$num2" =~ ^-?[0-9]+(\.[0-9]+)?$ ]]; then
    echo "Invalid input: Please enter numeric values."
    exit 1
fi

case $operator in
    +)
        add "$num1" "$num2"
        ;;
    -)
        subtract "$num1" "$num2"
        ;;
    \*)
        multiply "$num1" "$num2"
        ;;
    /)
        divide "$num1" "$num2"
        ;;
    *)
        echo "Invalid operation selected!"
        ;;
esac
