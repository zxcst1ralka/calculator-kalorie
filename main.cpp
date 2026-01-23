#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;
struct FoodItem {
    string name;
    double calories;
    double proteins;
    double fats;
    double carbs;
};
struct MealRecord {
    string timestamp;
    string foodName;
    double quantity;
    double totalCalories;
};

class CalorieCalculator {
private:
    vector<FoodItem> foodDatabase;
    vector<MealRecord> dailyRecords;
    string logFilename;
    double dailyCalorieGoal;

public:
    CalorieCalculator() : dailyCalorieGoal(2000.0) {
        logFilename = "calorie_log.txt";
        initializeDatabase();
    }
}
