#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <windows.h>

using namespace std;
using namespace filesystem;

int randomInRange(int min, int max) {
    static unsigned seed = time(nullptr);
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return min + (seed % (max - min + 1));
}
string createPassword(int length, bool withDigits, bool withSpecials) {
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string specials = "!@#$%^&*";
    string charPool = letters;
    if (withDigits) charPool += digits;
    if (withSpecials) charPool += specials;   
    string password;
    for (int i = 0; i < length; i++) {
        password += charPool[randomInRange(0, charPool.size() - 1)];
    }
    return password;
}
void checkPasswordStrength(const string& password) {
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    for (char c : password) {
        if (c >= 'a' && c <= 'z') hasLower = true;
        else if (c >= 'A' && c <= 'Z') hasUpper = true;
        else if (c >= '0' && c <= '9') hasDigit = true;
        else hasSpecial = true;
    }
    int strength = hasLower + hasUpper + hasDigit + hasSpecial;
    cout << "Сложность пароля: ";
    if (strength == 1) cout << "Очень простой";
    else if (strength == 2) cout << "Простой";
    else if (strength == 3) cout << "Средний";
    else cout << "Сложный";
    cout << endl;
}
bool savePassword(const std::string& password) {
    std::ofstream file("passwords.txt", std::ios::app);
    if (!file.is_open()) {
        return false;
    }
    file << password << '\n';
    if (!file.good()) {
        return false;
    }
    file.close();
    return true;
}
void showMenu() {
    cout << "\n=== Генератор паролей ===" << endl;
    cout << "1. Создать пароль" << endl;
    cout << "2. Выход" << endl;
    cout << "Выберите действие: ";
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    showMenu();
    int choice;
    cin >> choice;
    while (true){    
        if (choice == 2){
            cout << "Вы вышли из программы" << endl;
            break;
        }
        if (choice == 1) {
            int length;
            char answer;
            bool digits, specials;
            cout << "Длина пароля (8-32): ";
            cin >> length;
            length = max(8, min(32, length));           
            cout << "Включать цифры? (y/n): ";
            cin >> answer;
            digits = (answer == 'y' || answer == 'Y');            
            cout << "Включать спецсимволы? (y/n): ";
            cin >> answer;
            specials = (answer == 'y' || answer == 'Y');            
            string password = createPassword(length, digits, specials);
            cout << "\nВаш пароль: " << password << endl;
            checkPasswordStrength(password);
            cout << "Сохранить пароль? (y/n): ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y') {
                if (savePassword(password)) {
                    cout << "Пароль сохранен в файл passwords.txt" << endl;
                } else {
                    cout << "Ошибка сохранения файла" << endl;
                }
            }  
        }
        cout << "Вы успешно сгенерировали пароль" << endl;
        break;
    }
    return 0;
}
