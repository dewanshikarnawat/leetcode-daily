//Problem: 3622. Check Divisibility by Digit Sum and Product
//Topic: Mathematics
//Pattern: Easy

class Solution {
public:
    bool checkDivisibility(int n) {
        int sum = 0, prod = 1;
        int temp = n;

        while (temp > 0) {
            int digit = temp % 10;
            sum += digit;
            prod *= digit;
            temp /= 10;
        }

        return n % (sum + prod) == 0;
    }
};
