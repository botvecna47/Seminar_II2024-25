const display = document.getElementById('display');
const buttons = document.querySelectorAll('button'); // Select all buttons
let currentInput = '';
let operator = null;
let firstOperand = null;
let secondOperand = null;
let result = null;

// Update the display with the given value
function updateDisplay(value) {
    display.value = value;
}

// Clear all inputs and reset the calculator
function clear() {
    currentInput = '';
    operator = null;
    firstOperand = null;
    secondOperand = null;
    result = null;
    updateDisplay('0');
}

// Append a number or decimal point to the current input
function appendNumber(number) {
    if (currentInput.length < 10) { // Limit input length
        currentInput += number;
        updateDisplay(currentInput);
    }
}

// Set the operator and prepare for the next operand
function setOperator(op) {
    if (currentInput === '') return;
    if (firstOperand === null) {
        firstOperand = parseFloat(currentInput);
    } else if (operator) {
        secondOperand = parseFloat(currentInput);
        calculate();
    }
    operator = op;
    currentInput = '';
}

// Perform the calculation based on the operator
function calculate() {
    if (firstOperand === null || operator === null || currentInput === '') return;
    secondOperand = parseFloat(currentInput);
    switch (operator) {
        case '+':
            result = firstOperand + secondOperand;
            break;
        case '-':
            result = firstOperand - secondOperand;
            break;
        case '*':
            result = firstOperand * secondOperand;
            break;
        case '/':
            if (secondOperand === 0) {
                alert("Cannot divide by zero");
                clear();
                return;
            }
            result = firstOperand / secondOperand;
            break;
        default:
            return;
    }
    updateDisplay(result);
    currentInput = '';
    firstOperand = result;
    operator = null;
}

// Handle button clicks
function handleButtonClick(event) {
    const buttonValue = event.target.value;
    if (buttonValue === 'C') {
        clear();
    } else if (buttonValue === '=') {
        calculate();
    } else if (['+', '-', '*', '/'].includes(buttonValue)) {
        setOperator(buttonValue);
    } else {
        appendNumber(buttonValue);
    }
}

// Add event listeners to all buttons
buttons.forEach(button => {
    button.addEventListener('click', handleButtonClick);
});

// Initialize the display
updateDisplay('0');

// Add keyboard support
document.addEventListener('keydown', (event) => {
    const key = event.key;
    if (!isNaN(key) || key === '.') {
        appendNumber(key);
    } else if (['+', '-', '*', '/'].includes(key)) {
        setOperator(key);
    } else if (key === 'Enter' || key === '=') {
        calculate();
    } else if (key === 'Escape' ||key === 'Delete' ||key === 'Backspace') {
        clear();
    }
});
