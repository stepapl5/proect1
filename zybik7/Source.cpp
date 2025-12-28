#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

struct Symbol {
    string name;
    vector<string> art;
};

static void print_line(const vector<string>& parts) {
    for (const auto& part : parts) {
        cout << part;
    }
    cout << '\n';
}

static void print_reels(const Symbol& a, const Symbol& b, const Symbol& c) {
    cout << "+-----------+-----------+-----------+\n";
    for (size_t i = 0; i < a.art.size(); ++i) {
        cout << "|" << a.art[i] << "|" << b.art[i] << "|" << c.art[i] << "|\n";
    }
    cout << "+-----------+-----------+-----------+\n";
    cout << setw(13) << left << (" " + a.name) << setw(12) << (" " + b.name) << setw(12) << (" " + c.name) << '\n';
}

int main() {
    setlocale(LC_ALL, "ru");

    vector<Symbol> symbols = {
        {"Вишня", {"   .-.   ", "  (o o)  ", "  / V \\  ", " /(   )\\ ", "  ^^ ^^  "}},
        {"Лимон", {"  .---.  ", " /     \\ ", "|  .-.  |", " \\     / ", "  '---'  "}},
        {"Семь",  {"  ####  ", "     #  ", "    #   ", "   #    ", "  #     "}},
        {"Колокол", {"  _____  ", " /     \\ ", "|  ()  |", " \\_____/ ", "   ||   "}},
        {"Алмаз", {"   /\\   ", "  /  \\  ", " < /\\ > ", "  \\  /  ", "   \\/   "}}
    };

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<size_t> dist(0, symbols.size() - 1);

    int credits = 100;
    int bet = 10;

    cout << "Слот-казино: стартовый баланс " << credits << " монет.\n";
    cout << "Ставка по умолчанию: " << bet << " монет.\n";
    cout << "Нажмите Enter для вращения, 'b' чтобы изменить ставку, 'q' чтобы выйти.\n\n";

    while (credits > 0) {
        cout << "Баланс: " << credits << " | Ставка: " << bet << "\n";
        cout << "> ";
        string input;
        getline(cin, input);

        if (input == "q" || input == "Q") {
            break;
        }
        if (input == "b" || input == "B") {
            cout << "Введите новую ставку (1 - " << credits << "): ";
            string bet_input;
            getline(cin, bet_input);
            int new_bet = stoi(bet_input);
            if (new_bet >= 1 && new_bet <= credits) {
                bet = new_bet;
            } else {
                cout << "Некорректная ставка.\n";
            }
            continue;
        }

        if (bet > credits) {
            cout << "Недостаточно монет для ставки.\n";
            continue;
        }

        credits -= bet;

        size_t r1 = dist(gen);
        size_t r2 = dist(gen);
        size_t r3 = dist(gen);

        print_reels(symbols[r1], symbols[r2], symbols[r3]);

        if (r1 == r2 && r2 == r3) {
            int win = bet * 5;
            credits += win;
            cout << "Джекпот! Выигрыш: " << win << " монет.\n\n";
        } else if (r1 == r2 || r1 == r3 || r2 == r3) {
            int win = bet * 2;
            credits += win;
            cout << "Две одинаковые! Выигрыш: " << win << " монет.\n\n";
        } else {
            cout << "Не повезло. Попробуйте снова.\n\n";
        }
    }

    if (credits == 0) {
        cout << "Монеты закончились. Игра окончена.\n";
    }

    cout << "Спасибо за игру!\n";
    return 0;
}
