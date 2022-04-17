// This c program gets a credit card number input and checks to see if
// it is valid by calculating the Luhn's checksum for its digits,
// checking for an appropriate first or first two digits, and
// checking for an appropriate total number of digits. It prints
// the name of the card issuer (AMEX, MASTERCARD, VISA) if it passes
// all of the validation checks or INVALID if it fails to pass any
// of the validation checks.

// Richard Mays CS50x
// Completed 4/15/2022

// Include cs50.h for the get_long
// Inclue stdio.h for printf
#include <cs50.h>
#include <stdio.h>


// Function prototypes
long get_credit_card_number(void);
void validate_card(long credit_card_number);

int main(void)
{
// Get credit card number
    long credit_card_number = get_credit_card_number();
// Validate credit card number
    validate_card(credit_card_number);
}

long get_credit_card_number(void)
// Gets credit card number from console
{
    long credit_card_number;
    do
    {
        credit_card_number = get_long("Please enter your credit card number: ");
    }
    while (credit_card_number < 1);
    return credit_card_number;
}

void validate_card(long credit_card_number)
// Validates credit card number
{
    int digit_count = 0;
    int sum_digits_multiplied_by_two = 0;
    int sum_digits_not_multiplied_by_two = 0;
    int digits_total = 0;
// The following four variables are used to check whether the first or
// first and second digits are valid. During the while loop current and
// previous digit are used and when the while loop is complete they are
// used to assign the first digit and first two digits for validation.
    int previous_digit = 0;
    int current_digit = 0;
    int first_digit = 0;
    int first_two_digits = 0;

// The purpose of the boolean multiply_by_two is used to alternate
// between the card digits that need to be multiplied by two (or not)
// in the application of Luhn's Algorithm. It is initially set to
// false because the first digit (lowest order) is not multiplied by
// two.
    bool multiply_by_two = false;

// The reason for credit_card_number !=0 here is that the repeated
// dividing of the credit card number by 10 to discard each lower
// order digit ultimately results in the credit card number becoming
// 0, meaning that all of the digits have been processed.

    while (credit_card_number != 0)
    {
        previous_digit = current_digit;
        current_digit = credit_card_number % 10;
        digit_count ++;

        if (multiply_by_two == true)
        {
// The following if is needed because multiplying digit 5 or greater
// results in a two digit number and we have to separate those into
// individual digits and add them together per the Luhn's Algorithm.
            if (current_digit >= 5)
            {
// In this while loop, mod (%) 10 division is used to isolate each digit of
// the credit card number and normal division by 10 is used to discard
// each digit after it has been processed.
                sum_digits_multiplied_by_two += (current_digit * 2) % 10;
                sum_digits_multiplied_by_two += (current_digit * 2) / 10;
            }
            else
            {
                sum_digits_multiplied_by_two += current_digit * 2;
            }
        }
        else
        {
            sum_digits_not_multiplied_by_two += current_digit;
        }

        credit_card_number = credit_card_number / 10;
// This reverses the boolean multiply_by_two so we alternate between
// digits that need to be multiplied by two and those that don't.
        multiply_by_two = !(multiply_by_two);
    }
    digits_total = sum_digits_multiplied_by_two + sum_digits_not_multiplied_by_two;
// Assigning these two variables helps keep the if statements below a
// little easier to read.
    first_digit = current_digit;
    first_two_digits = current_digit * 10 + previous_digit;
// A valid VISA card number will have a Luhn's checksum ending in 0,
// its first digit will be a 4, and it will have a lenght of 13 or 16
// digits.
    if (digits_total % 10 == 0 && first_digit == 4 && (digit_count == 13 || digit_count == 16))
    {
        printf("VISA\n");
    }
// A valid Mastercard card number will have a Luhn's checksum ending
// in 0, its first two digits will be in the range 51 - 55 and it will
// have 16 digits.
    else if (digits_total % 10 == 0 && (first_two_digits >= 51 && first_two_digits <= 55) && digit_count == 16)
    {
        printf("MASTERCARD\n");
    }
// A valid American Express card number will have a Luhn's checksum
// ending in 0, its first two digits will be 34 or 37, and it will
// hand 15 digits.
    else if (digits_total % 10 == 0 && (first_two_digits == 34 || first_two_digits == 37) && digit_count == 15)
    {
        printf("AMEX\n");
    }
// For the purposes of this program any card number not matching the
// above criteria will be considered invalid.
    else
    {
        printf("INVALID\n");
    }
}