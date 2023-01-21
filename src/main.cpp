#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;
using std::vector;

int bykSolusi = 0;
int NUM[4]; //array isi angka actualnya

// ---- PROTOTYPES ----
void combinations(const string &s, vector<int> &pos, int n);
void StartInput(int n, int k, string numSt);
void GameSolver(string dS[], int numA[]);
void lexicograph(char *str, char *data, int last, int index);
void printRec(char set[], string prefix, int n, int k, int numA2[]);
void printAll(char set[], int k, int n, int numA2[]);
int calculate(char a, int a1, int a2);
int factorial(int n);
void permutation(string& str, int i);

// ---- MAIN ----
int main() {
    string inputUser;
    string isSave;
    float timer;
    cout << "=============== 24 GAME SOLVER ===============" << endl;
    cout << "Masukkan kartu ^^ : ";
    cin >> inputUser;

    int faktorial = factorial(inputUser.length());
    int a = faktorial/((inputUser.length()-1));

    cout << "Apakah anda ingin menyimpan solusi [Y / N] ? :  ";
    cin >> isSave;

    timer = clock();
    for (int i = 0; i < a; i++){
        StartInput(4, 3, inputUser);
        permutation(inputUser, 3);
    }
    if (isSave == "Y"){        
        ofstream myFile;
        myFile.open("solusi.txt", ofstream::app);
        myFile << "Jadi, terdapat " << bykSolusi << " solusi";
    }
    else if (isSave == "N"){
        char filename[] = "solusi.txt";
        int result = remove(filename);
        cout << result;
    }
    else {
        cout << "perintah salah !" << endl;
        char filename[] = "solusi.txt";
        int result = remove(filename);
        cout << result;    
    }

    timer = (clock() - timer) / CLOCKS_PER_SEC;
    printf(" --- EXECUTION TIME: %.5f s ---\n", timer);

    if (bykSolusi == 0){
        cout << "Tidak ada solusi" << endl;
    }
    return 0;
}

// ---- FUNCTIONS ----
void StartInput(int n, int k, string userInput) {
    char arrayChar[4 + 1];
    int arrayNum[4];
    bool valid = true;
    string cc;
    strcpy(arrayChar, userInput.c_str());

    for (int i = 0; i < n; i++) {
        cc = arrayChar[i];

        //klo inputnya huruf
        if (cc == "J"){
            NUM[i] = 11;
        }
        else if (cc == "Q"){
            NUM[i] = 12;
        }
        else if (cc == "K"){
            NUM[i] = 13;
        }
        else if(cc == "A"){
            NUM[i] = 1;
        }      
   
        else {
            arrayNum[i] = stoi(cc); //ubah jd int
            NUM[i] = arrayNum[i];        
            if (NUM[i] < 2 || NUM[i] > 9){
                valid = false;
            }
        }
    }
    char Operators[] = {'+', '-', '*', '/'};
    if (!valid || userInput.length() >= 5){
        cout << "Input tidak valid!" << endl;
    }
    else {
        printAll(Operators, k, n, NUM);
    }
}

void permutation(string& str, int i){
    for (int j = 0; j < i; j++) {
        swap(str[j], str[j+1]);
        //cout << str << endl;
    }
}

int factorial(int n){
    int hasil;
    if (n != 1) {
        hasil = n*factorial(n-1);
    }
    else {
        hasil = n;
    }
    return hasil;
}

void lexicograph(char *inputStr, char *data, int terakhir, int index) {
    
    int i;
    for (i = 0; i < 4; i++) {
        data[index] = inputStr[i];
        if (index == terakhir)
            cout << data << endl;
        else
            lexicograph(inputStr, data, terakhir, index + 1);
    }
}

void combinations(const string &s, vector<int> &arr, int n) {
    if (n == s.size()) {
        for (int i = 0; i != n; i++) {
            cout << s[arr[i]] << endl;
        }
        return;
    }
    for (int i = 0; i < s.size(); i++) {
        arr[n] = i;
        combinations(s, arr, n + 1);
    }
}
void GameSolver(string arrStr[], int arrNum[]) {
    char a;
    char cc[1];
    int total = 0, num = 0;

    for (int i = 0; i < 3; i++) {

        strcpy(cc, arrStr[i].c_str());
        a = cc[0];

        if (i == 0) {
            total = arrNum[0];
            num = arrNum[1];
            total = calculate(a, total, num);
        }
        if (i == 1) {
            num = arrNum[2];
            total = calculate(a, total, num);
        }
        if (i == 2) {
            num = arrNum[3];
            total = calculate(a, total, num);
        }
    }
    
    if (total == 24) {
        bykSolusi++;
        cout << "solusi " << bykSolusi << ": ";
        cout << "[(" << arrNum[0] << "";
        cout << arrStr[0];
        cout << "" << arrNum[1] << ")";
        cout << arrStr[1];
        cout << "" << arrNum[2] << "]";
        cout << arrStr[2];
        cout << "" << arrNum[3] << "";
        cout << " = 24" << endl;

        // save ke txt
        ofstream myFile;
        myFile.open("solusi.txt", ofstream::app);
        myFile << "[(" << arrNum[0] << "";
        myFile << arrStr[0];
        myFile << "" << arrNum[1] << ")";
        myFile << arrStr[1];
        myFile << "" << arrNum[2] << "]";
        myFile << arrStr[2];
        myFile << "" << arrNum[3] << "";
        myFile << " = " << total << endl;
        myFile.close();
    }
}

int calculate(char a, int b, int c) {
    int hasil = 0;
    
    switch (a) {
        case '+':
            hasil = b + c;
            break;

        case '*':
            hasil = b * c;
            break;

        case '-':
            if(b > c){
                hasil = b-c;
            }
            else {
                hasil = 0;
                c = 0;
            }
            break;

        case '/':
            if (b < c) {
                if (b != 0) {
                    if ((c % b) == 0)
                        hasil = c / b;
                    else
                        hasil = 0;
                    c = 0;
                } else
                    hasil = 0;
                c = 0;
            } else {
                if (c != 0) {
                    if ((b % c) == 0)
                        hasil = b / c;
                    else
                        hasil = 0;
                    c = 0;
                } 
                else
                    hasil = 0;
                c = 0;
            }
            break;
    }
    return hasil;
}

void printRec(char set[], string inputStr, int n, int k, int arrNum[]) {
    if (k == 0) {
        char char_array[5];
        string num2[5];
        string cc;
        strcpy(char_array, inputStr.c_str());

        for (int i = 0; i < 3; i++) {
            cc = char_array[i];
            num2[i] = cc;
        }
        GameSolver(num2, NUM);
        return;
    }
    for (int j = 0; j < n; j++) {
        printRec(set, (inputStr + set[j]), n, k - 1, arrNum);
    }
}

void printAll(char set[], int k, int n, int arrNum[]) {
    printRec(set, "", n, k, arrNum);
}