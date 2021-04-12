#include <iostream>
#include <math.h>
#include <string>

// Precondition: number and base are greater than 0
// Postcondition: returns the highest nth value
int getHighestNth(double number, double base) {

    int exponent = 0;

    double numOne = number;
    double numTwo = number / base;

    while (abs(1 - numOne) > abs(1 - numTwo)) {

        numOne = numTwo;
        numTwo = numTwo / base;

        exponent++;
    }

    return exponent - 1;
}

// Precondition: number, base, and precision are greater than 0
// Postcondition: returns the log[base](number) at precision [precision]
std::string logMethodOne(double number, double base, int precision) {

    std::string result = "";

    // find the highest nth value
    int nth = getHighestNth(number, base);

    // add the initial nth to the string and add "."
    result += std::to_string(nth) + ".";

    // divide number by base^nth
    number /= std::pow(base, nth);

    // raise the divided number to the base
    number = std::pow(number, base);

    // for loop to precision value
    for (int i = 0; i < precision; i++) {
        // find the highest nth value
        int nth = getHighestNth(number, base);

        // add the nth to the string
        result += std::to_string(nth);

        // divide number by base^nth
        number /= std::pow(base, nth);

        // raise the divided number to the base
        number = std::pow(number, base);
    }

    return result;
}

// Precondition: number is greater than 0
// Postcondition: returns the natural log of that number
// Reference: Logarithm Power Series Formula
// Link: https://en.wikipedia.org/wiki/Logarithm#Power_series
// Based on the formula that was extracted from the Taylor Series formula
// Formula: ln(z) = 2 * ∑n=0 to ∞ ((1/2n+1)((z−1/z+1)^(2n+1)))
double getNaturalLog(double number) {

    double totalSum = 0;

    // Only used for holding the value of the
    // repeating equation 2n+1
    double u = 0;

    // ∑n=0 to ∞
    for (int n = 0; n < 2000000; n++) {
        // (1/2n+1)
        u = (2 * n) + 1;

        // (z−1/z+1)^(2n+1)
        totalSum += ((1 / (u)) * (std::pow((number - 1) / (number + 1), u)));
    }

    // 2 * ∑n=0 to ∞ ((1/2n+1)((z−1/z+1)^(2n+1)))
    return 2 * totalSum;
}

// Precondition: number is greater than 0
// Postcondition: returns the log of the number
// Reference:
// Link: https://en.wikipedia.org/wiki/Logarithm#Logarithmic_identities
// Formula: log[base][number] = (log[k][number])/(log[k][base])
// k is supposed to be an arbitrary base value, so I used natural log instead
// since I have the formula for it list in the getNaturalLog function
double logMethodTwo(double number, double base, int precision) {

    double logValue = getNaturalLog(number) / getNaturalLog(base);

    return logValue;
}

int main() {

    double number = 29.0;
    double base = 9.0;
    int precision = 8;

    std::cout << "Log Method One: " << logMethodOne(number, base, precision) << std::endl;
    std::cout << "Log Method Two: " << logMethodTwo(number, base, precision) << std::endl;

    return 0;
}