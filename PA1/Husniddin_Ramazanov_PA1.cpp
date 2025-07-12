#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

std::string generateRandomWord(int length) {
    
    std::ifstream file("alphabet.txt");
    if (!file) {
        cerr << "File not opened!" << endl;
        return 0;
    }

    std::string Alphabet = "";
    char character;
    bool isDuplicate;
    string word = "";
    while (file.get(character)) {  // Karakter karakter oku
        if (character != ' ' && character != '\n' && character != '\r' && character != ',') {  // Boşluk, yeni satır ve carriage return hariç
            isDuplicate = false;
            for (char control : Alphabet) {
                if (control == character) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate) {
                Alphabet += character;
                //std::cout << character;
            }
        }
    }
    file.close(); // Dosyayı kapatmayı unutma!

    // Eğer Alphabet boşsa, geri döndür
    if (Alphabet.empty()) 
        return "";

    for (int i = 0; i < length; ++i) {
        int index = rand() % Alphabet.size();  // Rastgele indeks seç
        word += Alphabet[index];  // Seçilen karakteri ekle
        Alphabet.erase(Alphabet.begin() + index);  // Seçilen karakteri sil
    }

    return word;
}

void evaluateGuess(const std::string& secret, const std::string& guess, int& C_exact, int& C_misplaced) {
    C_exact = 0;
    C_misplaced = 0;
    for (size_t i = 0; i < secret.size(); ++i) {
        if (guess[i] == secret[i]) {
            C_exact++;
        } else if (secret.find(guess[i]) != std::string::npos) {
            C_misplaced++;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " -r <word_length> OR -u <word>" << std::endl;
        return 1;
    }
    
    std::ifstream file("alphabet.txt");
    if (!file) {
        cerr << "File not opened!" << endl;
        return 0;
    }

    std::string Alphabet = "";
    char character;
    bool isDuplicate;

    while (file.get(character)) {  // Karakter karakter oku
        if (character != ' ' && character != '\n' && character != '\r' && character != ',') {  // Boşluk, yeni satır ve carriage return hariç
            isDuplicate = false;
            for (char control : Alphabet) {
                if (control == character) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate) {
                Alphabet += character;
                //std::cout << character;
            }
        }
    }
    file.close();
    std::string secretWord;
    srand(time(0));
    
    if (std::string(argv[1]) == "-r") {
        int wordLength = std::stoi(argv[2]);
        if (wordLength > Alphabet.size()) {
            std::cerr << "Error: Word length exceeds available unique characters." << std::endl;
            return 1;
        }
        secretWord = generateRandomWord(wordLength);
    } else if (std::string(argv[1]) == "-u") {
        secretWord = argv[2];
    } else {
        std::cerr << "Invalid mode! Use -r or -u." << std::endl;
        return 1;
    }
    
    std::string guess;
    int attempts = 0;
    int guesstot=1;
    // std::cout << "Alphabet = ["<< Alphabet << "] " << std::endl;
    //cout << secretWord << endl;
    std::cout << "Alphabet = [";
    for (size_t i = 0; i < Alphabet.size(); ++i) {
        std::cout << Alphabet[i];
        if (i < Alphabet.size() - 1) { // Add a comma after each character except the last one
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
   
    while (guesstot < 101) {   //  here controlled user input
        std::cout << "Enter your guess: ";
        std::cin >> guess;
    
        // Check if the guess length matches the secret word length
        if (guess.size() != secretWord.size()) {
            std::cout << "Invalid guess length! Try again." << std::endl;
            continue;
        }
    
        // Check if all characters in the guess are in the Alphabet
        bool isValid = true;
        for (char ch : guess) {
            if (Alphabet.find(ch) == std::string::npos) {
                isValid = false;
                std::cout << "Character '" << ch << "' not found in the alphabet string. Try again." << std::endl;
                break;
            }
        }
    
        if (!isValid) {
            continue; // Skip the rest of the loop and prompt for a new guess
        }
    
        // Evaluate the guess
        attempts++;
        int C_exact, C_misplaced;
        evaluateGuess(secretWord, guess, C_exact, C_misplaced);
        std::cout << C_exact << ", " << C_misplaced << std::endl;
    
        // Check if the guess is correct
        if (C_exact == secretWord.size()) {
            std::cout << "FOUND  " << guesstot << std::endl;
            break;
        }
    
        guesstot++;

        // Check if the maximum number of guesses has been reached
        if (guesstot == 100) {
            std::cout << "FAILED" << std::endl;
            break; // Exit the loop if the maximum guesses are reached
        }
    }
    return 0;
}
