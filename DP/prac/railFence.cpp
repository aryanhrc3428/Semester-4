#include <bits/stdc++.h>
using namespace std;

string encrypt(string plaintext, int rails) {
    if (rails <= 1) return plaintext; // Prevent division by zero or 1-rail no-op

    int col = static_cast<int>(ceil(static_cast<double>(plaintext.length()) / rails));
    vector<vector<char>> temp(rails, vector<char>(col, ' '));
    int textptr = 0;
    
    for(int i = 0; i < col; i++) {
        int counter = 0;
        while(counter < rails) { 
            if (textptr < plaintext.length()) { 
                temp[counter][i] = plaintext[textptr]; 
            }
            counter++;
            textptr++;
        }
    }

    string res = "";
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < col; j++) {
            res += temp[i][j]; 
        }
    }

    return res;
}

string decrypt(string cipher, int rails) {
    if (rails <= 1) return cipher;

    int col = static_cast<int>(ceil(static_cast<double>(cipher.length()) / rails));
    
    vector<vector<char>> temp(rails, vector<char>(col, ' '));
    int textptr = 0;

    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < col; j++) {
            if (textptr < cipher.length()) {
                temp[i][j] = cipher[textptr];
                textptr++;
            }
        }
    }

    string res = "";
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < rails; i++) {
            res += temp[i][j];
        }
    }

    while (!res.empty() && res.back() == ' ') {
        res.pop_back();
    }

    return res;
}

int main() {
    int choice, rails;
    string text;

    while (true) {
        cout << "\n=== Rail Fence Cipher Menu ===\n";
        cout << "1. Encrypt a message\n";
        cout << "2. Decrypt a message\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter text to encrypt: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, text);
                
                cout << "Enter number of rails: ";
                if (!(cin >> rails) || rails < 1) {
                    cout << "Invalid input! Rails must be an integer of 1 or greater.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                
                cout << "\n-> Encrypted text: [" << encrypt(text, rails) << "]\n";
                break;
                
            case 2:
                cout << "Enter text to decrypt: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, text);
                
                cout << "Enter number of rails: ";
                if (!(cin >> rails) || rails < 1) {
                    cout << "Invalid input! Rails must be an integer of 1 or greater.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                
                cout << "\n-> Decrypted text: [" << decrypt(text, rails) << "]\n";
                break;
                
            default:
                cout << "Invalid choice! Please select 1, 2, or 3.\n";
        }
    }
    
    return 0;
}