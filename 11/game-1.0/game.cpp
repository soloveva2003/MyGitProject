#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <clocale>
#include <cwctype>

// Устанавливаем локаль для поддержки кириллицы
void setLocale() {
    std::setlocale(LC_ALL, "");
}

// Список слов для игры
std::vector<std::wstring> words = {L"программирование", L"компьютер", L"алгоритм", L"виселица", L"разработка"};

// Функция для выбора случайного слова
std::wstring chooseWord() {
    std::srand(std::time(0));
    int randomIndex = std::rand() % words.size();
    return words[randomIndex];
}

// Функция для отображения текущего состояния слова
void displayWord(const std::wstring& secretWord, const std::vector<wchar_t>& guessedLetters) {
    for (wchar_t letter : secretWord) {
        if (std::find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end()) {
            std::wcout << letter << L" ";
        } else {
            std::wcout << L"_ ";
        }
    }
    std::wcout << std::endl;
}

int main() {
    setLocale(); // Устанавливаем локаль

    std::wstring secretWord = chooseWord(); // Загаданное слово
    std::vector<wchar_t> guessedLetters;   // Угаданные буквы
    int attemptsLeft = 6;                  // Количество оставшихся попыток
    bool wordGuessed = false;              // Флаг, угадано ли слово
    int score = 0;                         // Счет игрока

    std::wcout << L"Добро пожаловать в игру 'Виселица'!\n";
    std::wcout << L"У вас есть " << attemptsLeft << L" попыток, чтобы угадать слово.\n";

    while (attemptsLeft > 0 && !wordGuessed) {
        std::wcout << L"\nСлово: ";
        displayWord(secretWord, guessedLetters);

        wchar_t guess;
        std::wcout << L"Введите букву: ";
        std::wcin >> guess;
        guess = std::towlower(guess); // Приводим букву к нижнему регистру

        // Проверка, была ли буква уже угадана
        if (std::find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            std::wcout << L"Вы уже вводили эту букву. Попробуйте другую.\n";
            continue;
        }

        guessedLetters.push_back(guess);

        // Проверка, есть ли буква в загаданном слове
        if (secretWord.find(guess) == std::wstring::npos) {
            attemptsLeft--;
            std::wcout << L"Неверно! Осталось попыток: " << attemptsLeft << L"\n";
        } else {
            std::wcout << L"Верно!\n";
            score += 5; // Награда за угаданную букву
        }

        // Проверка, угадано ли слово полностью
        wordGuessed = true;
        for (wchar_t letter : secretWord) {
            if (std::find(guessedLetters.begin(), guessedLetters.end(), letter) == guessedLetters.end()) {
                wordGuessed = false;
                break;
            }
        }
    }

    // Вывод результата игры
    if (wordGuessed) {
        std::wcout << L"\nПоздравляю! Вы угадали слово: " << secretWord << L"\n";
        score += 50; // Награда за угаданное слово
    } else {
        std::wcout << L"\nВы проиграли! Загаданное слово было: " << secretWord << L"\n";
    }

    std::wcout << L"Ваш счет: " << score << L"\n";

    return 0;
}
