#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const std::string ru_alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя";

int main() {
    // Чтение слов из файла
    std::ifstream file("ru_words.txt");
    std::vector<std::string> words;
    std::string line;
    while (std::getline(file, line)) {
        words.push_back(line);
    }
    file.close();
    
    std::cout << words.size() << std::endl;

    std::string coded_msg = "йсагофрем";
    int total_words = words.size();

    for (int i = 0; i < total_words; i++) {
        std::string key = words[i];
        std::string decoded_msg;
        
        for (int j = 0; j < coded_msg.length(); j++) {
            char ch = coded_msg[j];
            size_t pos = ru_alphabet.find(ch);
            if (pos != std::string::npos) {
                char key_ch = key[j % key.length()];
                size_t key_pos = ru_alphabet.find(key_ch);
                if (key_pos != std::string::npos) {
                    int new_pos = (pos - key_pos + ru_alphabet.length()) % ru_alphabet.length();
                    decoded_msg += ru_alphabet[new_pos];
                } else {
                    decoded_msg += ch;
                }
            } else {
                decoded_msg += ch;
            }
        }

        for (const auto& word : words) {
            if (word.length() > 5 && decoded_msg.find(word) != std::string::npos) {
                std::cout << decoded_msg << " " << i << " / " << total_words << std::endl;
            }
        }
    }

    return 0;
}