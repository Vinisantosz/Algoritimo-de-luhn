#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

// Função para exibir o menu e obter a escolha do usuário
int menu() {
    int choice;

    // Exibe o cabeçalho do menu
    std::cout << "==========================================" << std::endl;
    std::cout << "|           Escolha uma Bandeira         |" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "|  1 - VISA                              |" << std::endl;
    std::cout << "|  2 - MASTERCARD                        |" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "\nEscolha uma bandeira: ";

    // Laço para garantir uma escolha válida
    while (true) {
        std::cin >> choice;

        if (choice >= 1 || choice <= 2) { 
            break;
        } else {
            std::cout << "Opção inválida. Por favor, escolha uma das opções (1-3): ";
        }
    }

    return choice;
}

// Função para gerar um número de cartão com base na escolha do usuário
std::string generateCardNumber(int choice) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int prefix = 0;
    switch (choice) {
        case 1:
            prefix = 4; // Prefixo para VISA
            break;
        case 2:
            prefix = 5; // Prefixo para MASTERCARD
            break;
        default:
            break; // Poderia lançar uma exceção para escolha inválida
    }

    std::string cardNumber = std::to_string(prefix);

    // Gera os dígitos aleatórios do cartão
    for (int i = 0; i < 14; i++) {
        int digit = std::rand() % 10;
        cardNumber += std::to_string(digit);
    }

    int sum = 0;
    bool doubleDigit = true;

    // Calcula o dígito de verificação e anexa-o ao número do cartão
    for (int i = cardNumber.length() - 1; i >= 0; i--) {
        int digit = cardNumber[i] - '0';

        if (doubleDigit) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
        doubleDigit = !doubleDigit;
    }

    int checksum = (10 - (sum % 10)) % 10;
    cardNumber += std::to_string(checksum);

    return cardNumber;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int choice = menu();
    std::string cardNumber = generateCardNumber(choice);

    // Exibe o número do cartão gerado
    std::cout << "\nNúmero do cartão gerado: " << cardNumber << std::endl;
    system("pause");
    return 0;
}