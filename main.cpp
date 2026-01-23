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
        cout << "\n=== БАЗА ДАННЫХ ПРОДУКТОВ ===\n";
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