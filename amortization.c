/*
* Program Name: Amortization Table Generator
* Description: Generate amortization table based on inputted loan information
*/
#include <stdio.h>
#include <math.h>

// Defined constants
#define LOAN_TERM_MIN 3
#define LOAN_TERM_MAX 40
#define LOAN_RATE_MIN 1
#define LOAN_RATE_MAX 20
#define LOAN_AMT_MIN 10000
#define LOAN_AMT_MAX 2000000

// Function prototypes
int getLoanTerm();
double getLoanRate();
int getLoanAmount();
double calculateP(double interest, int loanAmount, int totalPayments);

int hasQuit = 0;

int main() {
    do {
        printf(">> Enter the following. Enter 0 to exit at any time. <<\n\n");

        // Get length of loan
        int loan_term = getLoanTerm() * 12;
        if (hasQuit == 1) {
            break; // Break loop if user enters 0
        }

        // Get interest rate of loan (annual)
        double loan_rate = getLoanRate();
        if (hasQuit == 1) {
            break; // Break loop if user enters 0
        }

        // Get amount of loan
        int loan_amt = getLoanAmount();
        if (hasQuit == 1) {
            break; // Break loop if user enters 0
        }

        // Calculate and print amortization table
        calculateP(loan_rate, loan_amt, loan_term);

    } while (1); // Loop after each completed table

    printf("Program terminated.");
    return 0;
}

/*******************************
*   Function Name: getLoanTerm
*   Input Parameters: N/A
*   Description: Asks for how long in years the loan will be for
*   Return Value: loanTerm
********************************/
int getLoanTerm() {
    int loanTerm = 0;

    printf("Loan term (3-40 years): ");
    scanf("%d", &loanTerm);

    // Check if quit value entered, and if input is within parameters
    if (loanTerm == 0) {
        hasQuit = 1; // Stop program loop
        return 0;
    } else if (loanTerm < LOAN_TERM_MIN || loanTerm > LOAN_TERM_MAX) {
        printf(">> Invalid input. Please ensure your value as an integer between 3 and 40.\n\n");
        return 0;
    }
    return loanTerm; // Return length of loan in years
}

/*******************************
*   Function Name: getLoanRate
*   Input Parameters: N/A
*   Description: Asks for interest rate of the loan
*   Return Value: loanRate
********************************/
double getLoanRate() {
    double loanRate = 0;

    printf("Loan interest rate (1-20): ");
    scanf("%lf", &loanRate);

    // Check if quit value entered, and if input is within parameters
    if (loanRate == 0) {
        hasQuit = 1; // Stop program loop
        return 0;
    } else if (loanRate < LOAN_RATE_MIN || loanRate > LOAN_RATE_MAX) {
        printf(">> Invalid input. Please ensure your value as an integer between 3 and 40.\n\n");
        return 0;
    }
    return loanRate / 1200; // Return MONTHLY interest rate
}

/*******************************
*   Function Name: getLoanAmount
*   Input Parameters: N/A
*   Description: Asks for how much the loan is for
*   Return Value: loanAmount
********************************/
int getLoanAmount() {
    int loanAmount = 0;

    printf("Loan amount (10000-2000000): ");
    scanf("%d", &loanAmount);

    // Check if quit value entered, and if input is within parameters
    if (loanAmount == 0) {
        hasQuit = 1; // Stop program loop
        return 0;
    } else if (loanAmount < LOAN_AMT_MIN || loanAmount > LOAN_AMT_MAX) {
        printf(">> Invalid input. Please ensure your value as an integer between 3 and 40.\n\n");
        return 0;
    }
    return loanAmount; // Return total amount of loan
}

/*******************************
*   Function Name: calculateP
*   Input Parameters: Interest rate, amount of loan, how many payments there are in months
*   Description: Calculate all aspects of the loan and then print amortization table
*   Return Value: N/A
********************************/
double calculateP(double interest, int loanAmount, int totalPayments) {
    int month = 1;
    double balance = loanAmount, payment, interestMonth, principle;
    double power = 1 + interest;
    payment = loanAmount * (interest + (interest / (pow(power, totalPayments)-1))); // Amortization (monthly payment) formula
    double totalInterest;
    double totalPrinciple;

    printf("Mnt    Int\tPrinc\t\tBalance\n"); // Amortization table header

    // Loop through each month & calculate interest/principle and print
    for (int i = totalPayments; i > 0; i--) {
        balance = balance - principle; // Update balance
        interestMonth = interest * balance; // Calculate this month's interest
        principle = payment - interestMonth; // Calculate principle by subtracting monthly interest from payment
        totalPrinciple = totalPrinciple + principle; // Calculate total principle paid through monthly payments
        totalInterest = totalInterest + interestMonth; // Calculate total interest paid through monthly payments
        printf("%3d  \t%.2lf   %.2lf\t\t %.2lf\n", month, interestMonth, principle, balance); // Print row
        month++; // Move to next month
    }

    printf("The total cost of this loan is: \t$%.2lf\n", loanAmount + totalInterest); // Cost of loan + interest
    printf("The total interest of this loan is: \t$%.2lf\n", totalInterest); // Total of interest paid
    printf("The total principle of this loan is: \t$%.2lf\n", totalPrinciple); // Total of principle paid (should == loanAmount)

    return 0;
}
