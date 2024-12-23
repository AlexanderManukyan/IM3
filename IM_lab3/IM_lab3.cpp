#include <iostream>

int main(){
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    // Закупка
    int account = 10000;
    int volumeOfLot;
    int priceOfUnitOfLot;
    int priceOfLot;

    // Склады
    int basicStore = 80;
    int inTransfer = 0;
    int shopStore = 30;
    int volumeOfTransfer;

    // Торговля
    int demand;
    int retailPrice;

    // Принятие решений
    bool buyEnabled;
    bool transferEnabled;
    bool tradingEnabled;

    for (int modelTime = 0; modelTime < 101; modelTime++) {
        std::cout << "Модельное время: " << modelTime << "/100\n";
        std::cout << "Расчетный счет: " << account << "\n";

        volumeOfLot = 30 + rand() % 21;
        priceOfUnitOfLot = (35 + rand() % 31) + round(35.0 * modelTime * (0.03 + 0.01 * (rand() % 2)));
        priceOfLot = volumeOfLot * priceOfUnitOfLot;
        std::cout << "Объем партии: " << volumeOfLot << "\n"
            << "Цена за ед.: " << priceOfUnitOfLot << "\n"
            << "Цена партии: " << priceOfLot << "\n";
        std::cout << "Покупаем товар?(да - 1/ нет - 0):\n";
        std::cin >> buyEnabled;

        std::cout << "Основной склад: " << basicStore << "/500\n"
            << "В машине: " << inTransfer << "/100\n"
            << "Склад магазина: " << shopStore << "/100\n";
        if (!inTransfer) {
            std::cout << "Перевозим товар?(да - 1/ нет - 0):\n";
            std::cin >> transferEnabled;
            if (transferEnabled) {
                std::cout << "Введите объем перевозки [20 - 100]:\n";
                std::cin >> volumeOfTransfer;
            }
        }

        std::cout << "Продаем товар?(да - 1/ нет - 0):\n";
        std::cin >> tradingEnabled;

        // действия
        if (buyEnabled) {
            if (priceOfLot <= account) {
                account -= priceOfLot;
                if ((basicStore + volumeOfLot) > 500) {
                    basicStore = 500;
                }
                else {
                    basicStore += volumeOfLot;
                }
            }
        }

        if (transferEnabled) {
            if (inTransfer) {
                if ((shopStore + inTransfer) > 100) {
                    shopStore = 100;
                }
                else {
                    shopStore += inTransfer;
                }
                inTransfer = 0;
            }
            else {
                if ((basicStore - volumeOfTransfer) > 0) {
                    inTransfer = volumeOfTransfer;
                    basicStore -= volumeOfTransfer;
                }
                else {
                    inTransfer = basicStore;
                    basicStore = 0;
                }
            }
        }
        if (tradingEnabled) {
            std::cout << "Введите розничную цену [100 - 200]:\n";
            std::cin >> retailPrice;
            demand = round((double)(21 + rand() % 16) * (1.0 - (1.0 / (1 + exp(-0.05 * (retailPrice - 100))))));
            std::cout << "Спрос: " << demand << "\n";
            if (shopStore > demand) {
                shopStore -= demand;
                account += retailPrice * demand;
            }
            else {
                account += retailPrice * shopStore;
                shopStore = 0;
            }
        }
        std::cout << "---------------------\n";
    }
}
