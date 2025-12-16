#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

vector<string> history_log;
int operation_counter = 1;

const double RUB_RATE = 1.0;
const double USD_RATE = 73.02;
const double EUR_RATE = 85.50;
const double CNY_RATE = 10.88;

double get_rate_to_rub(string currency) {
    if (currency == "RUB") return RUB_RATE;
    if (currency == "USD") return USD_RATE;
    if (currency == "EUR") return EUR_RATE;
    if (currency == "CNY") return CNY_RATE;
    return 1.0;
}

void show_menu() {
    cout << "\n=== КОНВЕРТЕР ВАЛЮТ ===" << endl;
    cout << "1. Выполнение (Конвертация)" << endl;
    cout << "2. Тестирование" << endl;
    cout << "3. Выход" << endl;
    cout << "=======================" << endl;
    cout << "Выберите действие (1-3): ";
}

void perform_conversion(string source, string target, double amount, bool quiet = false) {
    vector<string> valid_currencies = {"RUB", "USD", "EUR", "CNY"};
    bool source_valid = false, target_valid = false;
    
    for(const auto& c : valid_currencies) {
        if(c == source) source_valid = true;
        if(c == target) target_valid = true;
    }
    
    if(!source_valid || !target_valid) {
        if(!quiet) cout << "Ошибка: недопустимая валюта. Используйте: RUB, USD, EUR, CNY" << endl;
        return;
    }

    if(amount < 0.01 || amount > 1000000) {
        if(!quiet) cout << "Ошибка: сумма должна быть от 0.01 до 1000000" << endl;
        return;
    }

    double rate_src = get_rate_to_rub(source);
    double rate_tgt = get_rate_to_rub(target);
    double final_rate = rate_src / rate_tgt;

    double result = amount * final_rate;

    stringstream ss;
    ss << fixed << setprecision(2);
    ss << operation_counter << ". " << source << "->" << target 
       << " " << amount << "->" << result;
    
    string entry = ss.str();
    history_log.push_back(entry);
    operation_counter++;
    
    if (history_log.size() > 5) {
        history_log.erase(history_log.begin());
    }
    
    if (!quiet) {
        cout << fixed << setprecision(2);
        cout << "\nРезультат: " << result << " " << target << endl;
        cout << "Курс: " << final_rate << " " << source << "/" << target << endl;
        cout << "История: " << endl;
        for (size_t i = 0; i < history_log.size(); ++i) {
            cout << history_log[i];
            if (i < history_log.size() - 1) cout << endl;
        }
        cout << "\n" << endl;
    }
}

void get_user_input() {
    string source, target;
    double amount;
    vector<string> valid_currencies = {"RUB", "USD", "EUR", "CNY"};
    
    while(true) {
        cout << "\nВведите исходную валюту (RUB, USD, EUR, CNY): ";
        cin >> source;
        
        bool found = false;
        for(const auto& c : valid_currencies) {
            if(c == source) {
                found = true;
                break;
            }
        }
        
        if(found) break;
        cout << "Ошибка: недопустимая валюта. Используйте: RUB, USD, EUR, CNY" << endl;
    }
    
    while(true) {
        cout << "Введите целевую валюту (RUB, USD, EUR, CNY): ";
        cin >> target;
        
        bool found = false;
        for(const auto& c : valid_currencies) {
            if(c == target) {
                found = true;
                break;
            }
        }
        
        if(found) break;
        cout << "Ошибка: недопустимая валюта. Используйте: RUB, USD, EUR, CNY" << endl;
    }
    
    while(true) {
        cout << "Введите сумму (0.01 - 1000000): ";
        if(cin >> amount) {
            if(amount >= 0.01 && amount <= 1000000) {
                break;
            }
            cout << "Ошибка: сумма должна быть в диапазоне от 0.01 до 1000000" << endl;
        } else {
            cout << "Ошибка: введите корректное число" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    perform_conversion(source, target, amount);
}

void test_system() {
    cout << "\n=== ЗАПУСК АВТОМАТИЧЕСКИХ ТЕСТОВ ===" << endl;
    
    cout << "\nТест 1: RUB -> USD (5000)" << endl;
    perform_conversion("RUB", "USD", 5000);
    
    cout << "Тест 2: EUR -> CNY (100)" << endl;
    perform_conversion("EUR", "CNY", 100);
    
    cout << "Тест 3: Одинаковые валюты RUB -> RUB (1000)" << endl;
    perform_conversion("RUB", "RUB", 1000);
    
    cout << "Тест 4: Граничное значение - минимальная сумма USD -> EUR (0.01)" << endl;
    perform_conversion("USD", "EUR", 0.01);
    
    cout << "Тест 5: Граничное значение - максимальная сумма CNY -> USD (1000000)" << endl;
    perform_conversion("CNY", "USD", 1000000);
    
    cout << "Тест 6: Проверка переполнения истории (добавляем 6-ю операцию)" << endl;
    perform_conversion("USD", "RUB", 100);
    
    cout << "\nТест 7: Некорректная валюта GBP -> USD (100)" << endl;
    perform_conversion("GBP", "USD", 100);
    
    cout << "Тест 8: Некорректная сумма RUB -> USD (-100)" << endl;
    perform_conversion("RUB", "USD", -100);
    
    cout << "Тест 9: Сумма вне диапазона RUB -> USD (2000000)" << endl;
    perform_conversion("RUB", "USD", 2000000);
    
    cout << "\n=== ТЕСТЫ ЗАВЕРШЕНЫ ===" << endl;
}

int main() {
    int choice;
    
    cout << "Добро пожаловать в систему мультивалютных трансформаций!" << endl;
    cout << "Доступные валюты: RUB, USD, EUR, CNY" << endl;
    
    while(true) {
        show_menu();
        
        if (cin >> choice) {
            if (choice == 1) {
                get_user_input();
            }
            else if (choice == 2) {
                test_system();
            }
            else if (choice == 3) {
                cout << "\nВыход из программы. До свидания!" << endl;
                return 0;
            }
            else {
                cout << "Ошибка: введите число от 1 до 3" << endl;
            }
        }
        else {
            cout << "Ошибка: некорректный ввод. Введите число от 1 до 3" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    return 0;
}
