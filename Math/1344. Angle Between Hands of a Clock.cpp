//Problem: 1344. Angle Between Hands of a Clock
//Topic: Math (Geometry / Simulation)
//Pattern: Medium

class Solution {
public:
    double angleClock(int hour, int minutes) {
        double hourAngle = (hour % 12) * 30 + minutes * 0.5;
        double minuteAngle = minutes * 6;

        double diff = abs(hourAngle - minuteAngle);

        return min(diff, 360.0 - diff);
    }
};
