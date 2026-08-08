//Problem: 3345. Smallest Divisible Digit Product I
//Topic: Brute force
//Pattern: Easy

class Solution {
public:
    int smallestNumber(int n, int t) {
        while (true) {
            int x = n;
            int product = 1;

            while (x > 0) {
                product *= (x % 10);
                x /= 10;
            }

            if (product % t == 0)
                return n;

            n++;
        }
    }
};
