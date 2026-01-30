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

    void initializeDatabase() {
        foodDatabase = {
            {"Яблоко", 52, 0.3, 0.2, 14.0},
            {"Банан", 96, 1.3, 0.3, 21.0},
            {"Куриная грудка", 165, 31.0, 3.6, 0.0},
            {"Рис вареный", 130, 2.7, 0.3, 28.0},
            {"Яйцо куриное", 155, 13.0, 11.0, 1.1},
            {"Хлеб пшеничный", 265, 9.0, 3.2, 49.0},
            {"Молоко 2.5%", 52, 2.8, 2.5, 4.7},
            {"Сыр", 402, 25.0, 33.0, 1.3},
            {"Картофель вареный", 82, 2.0, 0.1, 17.0},
            {"Гречка", 110, 4.2, 0.9, 21.3}
        };
    }

    string getCurrentTimestamp() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        
        stringstream ss;
        ss << put_time(localTime, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    void displayFoodDatabase() {
        cout << "\nБАЗА ДАННЫХ ПРОДУКТОВ\n";
        cout << "№  Название\t\tКкал\tБелки\tЖиры\tУглеводы\n";
        cout << "------------------------------------------------\n";
        
        for (size_t i = 0; i < foodDatabase.size(); i++) {
            cout << i + 1 << ". " 
                 << left << setw(15) << foodDatabase[i].name 
                 << "\t" << foodDatabase[i].calories
                 << "\t" << foodDatabase[i].proteins
                 << "\t" << foodDatabase[i].fats
                 << "\t" << foodDatabase[i].carbs << endl;
        }
    }

    void addMeal() {
        displayFoodDatabase();
        
        int choice;
        cout << "\nВыберите продукт (номер): ";
        cin >> choice;
        
        if (choice < 1 || choice > static_cast<int>(foodDatabase.size())) {
            cout << "Неверный выбор!\n";
            return;
        }
        
        FoodItem selectedFood = foodDatabase[choice - 1];
        
        double quantity;
        cout << "Введите количество (в граммах): ";
        cin >> quantity;
        
        double totalCalories = (selectedFood.calories * quantity) / 100.0;
        
        MealRecord record;
        record.timestamp = getCurrentTimestamp();
        record.foodName = selectedFood.name;
        record.quantity = quantity;
        record.totalCalories = totalCalories;
        
        dailyRecords.push_back(record);
        
        logToFile(record);
        
        cout << "Добавлено: " << selectedFood.name 
             << " (" << quantity << "г) - " 
             << totalCalories << " ккал\n";
    }

    void logToFile(const MealRecord& record) {
        ofstream logFile(logFilename, ios::app);
        
        if (logFile.is_open()) {
            logFile << record.timestamp << " | "
                    << record.foodName << " | "
                    << record.quantity << "г | "
                    << record.totalCalories << " ккал\n";
            logFile.close();
        } else {
            cout << "Ошибка открытия файла для логирования!\n";
        }
    }

    void viewDailyStats() {
        if (dailyRecords.empty()) {
            cout << "За сегодня еще не было приемов пищи.\n";
            return;
        }
        
        double totalCalories = 0;
        double totalProtein = 0;
        double totalFat = 0;
        double totalCarbs = 0;
        
        cout << "\nСТАТИСТИКА ЗА ДЕНЬ\n";
        cout << "Время\t\t\tПродукт\t\tКол-во\tКкал\n";
        cout << "------------------------------------------------\n";
        
        for (const auto& record : dailyRecords) {
            cout << record.timestamp << "\t"
                 << left << setw(15) << record.foodName 
                 << "\t" << record.quantity << "г\t"
                 << record.totalCalories << endl;
            
            totalCalories += record.totalCalories;
            
            for (const auto& food : foodDatabase) {
                if (food.name == record.foodName) {
                    double ratio = record.quantity / 100.0;
                    totalProtein += food.proteins * ratio;
                    totalFat += food.fats * ratio;
                    totalCarbs += food.carbs * ratio;
                    break;
                }
            }
        }
        
        cout << "\n ИТОГО ЗА ДЕНЬ \n";
        cout << "Общие калории: " << totalCalories << " ккал\n";
        cout << "Белки: " << totalProtein << " г\n";
        cout << "Жиры: " << totalFat << " г\n";
        cout << "Углеводы: " << totalCarbs << " г\n";
        cout << "Дневная цель: " << dailyCalorieGoal << " ккал\n";
        
        if (totalCalories > dailyCalorieGoal) {
            cout << "Превышение дневной нормы на " 
                 << (totalCalories - dailyCalorieGoal) << " ккал\n";
        } else {
            cout << "Осталось до цели: " 
                 << (dailyCalorieGoal - totalCalories) << " ккал\n";
        }
    }

    void viewLogHistory() {
        ifstream logFile(logFilename);
        
        if (!logFile.is_open()) {
            cout << "Файл логов не найден или пуст.\n";
            return;
        }
        
        cout << "\nИСТОРИЯ ПРИЕМОВ ПИЩИ\n";
        string line;
        int lineCount = 0;
        
        while (getline(logFile, line)) {
            cout << line << endl;
            lineCount++;
        }
        
        if (lineCount == 0) {
            cout << "История пуста.\n";
        }
        
        logFile.close();
    }

    void setDailyGoal() {
        cout << "Текущая дневная цель: " << dailyCalorieGoal << " ккал\n";
        cout << "Введите новую цель: ";
        cin >> dailyCalorieGoal;
        cout << "Цель обновлена!\n";
    }

    void addNewFood() {
        FoodItem newFood;
        
        cout << "\n=== ДОБАВЛЕНИЕ НОВОГО ПРОДУКТА ===\n";
        cout << "Название продукта: ";
        cin.ignore();
        getline(cin, newFood.name);
        
        cout << "Калорийность на 100г: ";
        cin >> newFood.calories;
        
        cout << "Белки на 100г: ";
        cin >> newFood.proteins;
        
        cout << "Жиры на 100г: ";
        cin >> newFood.fats;
        
        cout << "Углеводы на 100г: ";
        cin >> newFood.carbs;
        
        foodDatabase.push_back(newFood);
        cout << "Продукт добавлен в базу данных!\n";
    }

    void run() {
        int choice;
        
        do {
            cout << "\n=== КАЛЬКУЛЯТОР КАЛОРИЙ ===\n";
            cout << "1. Добавить прием пищи\n";
            cout << "2. Просмотреть статистику за день\n";
            cout << "3. Просмотреть историю из файла\n";
            cout << "4. Установить дневную цель\n";
            cout << "5. Добавить новый продукт\n";
            cout << "6. Показать базу продуктов\n";
            cout << "0. Выход\n";
            cout << "Выберите действие: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    addMeal();
                    break;
                case 2:
                    viewDailyStats();
                    break;
                case 3:
                    viewLogHistory();
                    break;
                case 4:
                    setDailyGoal();
                    break;
                case 5:
                    addNewFood();
                    break;
                case 6:
                    displayFoodDatabase();
                    break;
                case 0:
                    cout << "Выход из программы. Все данные сохранены в файле '" 
                         << logFilename << "'\n";
                    break;
                default:
                    cout << "Неверный выбор! Попробуйте снова.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    CalorieCalculator calculator;
    calculator.run();
    
    return 0;
}