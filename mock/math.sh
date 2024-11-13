#!/bin/bash

# Function to perform addition
add() {
    echo "Result: $(($1 + $2))"
}

# Function to perform subtraction
subtract() {
    echo "Result: $(($1 - $2))"
}

# Function to perform multiplication
multiply() {
    echo "Result: $(($1 * $2))"
}

# Function to perform division
divide() {
    if [ "$2" -eq 0 ]; then
        echo "Error: Division by zero is not allowed."
    else
        echo "Result: $(($1 / $2))"
    fi
}

# Prompt the user to enter two numbers
read -p "Enter the first number: " num1
read -p "Enter the second number: " num2

# Display the menu for operation selection
echo "Select an operation:"
echo "1. Addition (+)"
echo "2. Subtraction (-)"
echo "3. Multiplication (*)"
echo "4. Division (/)"
read -p "Enter your choice (1/2/3/4): " choice

# Perform the operation based on user input
case $choice in
    1)
        add $num1 $num2
        ;;
    2)
        subtract $num1 $num2
        ;;
    3)
        multiply $num1 $num2
        ;;
    4)
        divide $num1 $num2
        ;;
    *)
        echo "Invalid choice. Please select a valid option."
        ;;
esac
