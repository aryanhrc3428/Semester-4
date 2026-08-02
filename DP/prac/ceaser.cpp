#include <bits/stdc++.h>
using namespace std;

/*
65 - A
90 - Z
97 - a
122 - z
*/

string encrypt(string plaintext, int key) {
    // Normalize key to handle negative shifts safely
    key = ((key % 26) + 26) % 26;
    for (size_t i = 0; i < plaintext.length(); i++) {
        if (isupper(plaintext[i])) {
            plaintext[i] = ((static_cast<int>(plaintext[i]) + key - 65) % 26) + 65;
        } 
        else if (plaintext[i] == ' ' || isdigit(plaintext[i])) {
            continue;
        } 
        else if (islower(plaintext[i])) {
            plaintext[i] = ((((static_cast<int>(plaintext[i]) + key - 97) % 26) + 26) % 26) + 97;
        }
    }
    return plaintext;
}

string decrypt(string cipher, int key) {
    // Normalize key to handle negative shifts safely
    key = ((key % 26) + 26) % 26;
    for (size_t i = 0; i < cipher.length(); i++) {
        if (isupper(cipher[i])) {
            // Added safe modulo (+26)%26 to prevent negative ASCII values
            cipher[i] = ((((static_cast<int>(cipher[i]) - key - 65) % 26) + 26) % 26) + 65;
        } 
        else if (cipher[i] == ' ' || isdigit(cipher[i])) {
            continue;
        } 
        else if (islower(cipher[i])) {
            cipher[i] = ((((static_cast<int>(cipher[i]) - key - 97) % 26) + 26) % 26) + 97;
        }
    }
    return cipher;
}

int main() {
    int choice;
    do {
        cout << "\n====================================\n";
        cout << "       CAESAR CIPHER MENU           \n";
        cout << "====================================\n";
        cout << "1. Encrypt Text\n";
        cout << "2. Decrypt Text\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        // Handle invalid non-integer inputs gracefully
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 3.\n";
            continue;
        }

        if (choice == 1) {
            string text;
            int key;
            cout << "Enter plaintext to encrypt: ";
            cin >> ws; // Clear leading whitespace from buffer
            getline(cin, text);
            cout << "Enter shift key: ";
            cin >> key;
            
            string encrypted = encrypt(text, key);
            cout << "-> Encrypted Text: " << encrypted << "\n";
        } 
        else if (choice == 2) {
            string text;
            int key;
            cout << "Enter ciphertext to decrypt: ";
            cin >> ws;
            getline(cin, text);
            cout << "Enter shift key: ";
            cin >> key;
            
            string decrypted = decrypt(text, key);
            cout << "-> Decrypted Text: " << decrypted << "\n";
        } 
        else if (choice == 3) {
            cout << "Exiting program. Goodbye!\n";
        } 
        else {
            cout << "Invalid choice! Please select an option from 1 to 3.\n";
        }

    } while (choice != 3);

    return 0;
}