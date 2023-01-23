// ---- HEADERS ----
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
using namespace std;
using std::vector;

int bykSolusi = 0;
int arrInt[4]; //array isi angka actualnya

// ---- PROTOTYPES ----
void combinations(const string &s, vector<int> &arr, int n);
void StartInput(int n, int k, string userInput);
int calculate(char a, int b, int c);
void lexicograph(char *inputStr, char *data, int terakhir, int idx);
void GameSolver(string arrStr[], int arrNum[]);
void printRec(char set[], string inputStr, int n, int k, int arrNum[]);
void printAll(char set[], int k, int n, int arrNum[]);
void inputRandom();

// ---- MAIN ----
int main() {
    string inputUser;
    string isSave, isManual;
    float timer;

    cout <<" ___________________________________________________" << endl;
	cout <<"| __          __  _                                 |" << endl;
	cout <<"| \\ \\        / / | |                                |" << endl;
	cout <<"|  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___        |" << endl;
	cout <<"|   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ |       |" << endl;
	cout <<"|    \\  /\\  /  __/ | (_| (_) | | | | | |  __/       |" << endl;
	cout <<"|     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___        |" << endl;
	cout <<"|___________________________________________________|" << endl;
    cout << "================== 24 GAME SOLVER ==================" << endl;
    cout << "apakah anda ingin meng-input kartu secara manual [Y/N]?: ";
    cin >> isManual;

    if (isManual == "Y"){
        cout << "Masukkan kartu ^^ : ";
        cin >> inputUser;  
        timer = clock();
        do{
        StartInput(4, 3, inputUser);
        } while (next_permutation(inputUser.begin(), inputUser.end()));
        timer = (clock() - timer) / CLOCKS_PER_SEC;
    }
    else if (isManual == "N"){
        timer = clock();
        inputRandom();
        timer = (clock() - timer) / CLOCKS_PER_SEC;
    }
    else {
        cout << "perintah tidak valid !"<< endl;
    }

    cout << "Apakah anda ingin menyimpan solusi [Y / N] ? :  ";
    cin >> isSave;

    if (isSave == "Y"){        
        ofstream myFile;
        myFile.open("solusi.txt", ofstream::app);
        myFile << "Jadi, terdapat " << bykSolusi << " solusi" << endl;
        cout << "solusi berhasil disimpan :)" << endl;
    }
    else if (isSave == "N"){
        char filename[] = "solusi.txt";
        int result = remove(filename);
        cout << result;
        cout << "baik, sampai jumpa !" << endl;
    }
    else {
        cout << "perintah salah !" << endl;
        char filename[] = "solusi.txt";
        int result = remove(filename);
        cout << result;    
    }

    printf(" --- EXECUTION TIME: %.5f s ---\n", timer);

    if (bykSolusi == 0){
        cout << "Tidak ada solusi" << endl;
    }
    return 0;
}

// ---- FUNCTIONS ----
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

void StartInput(int n, int k, string userInput) {
    char arrayChar[5];
    int arrayNum[4];
    bool valid = true;
    string cc;
    strcpy(arrayChar, userInput.c_str());

    for (int i = 0; i < n; i++) {
        cc = arrayChar[i];

        //klo inputnya huruf
        if (cc == "J"){
            arrInt[i] = 11;
        }
        else if (cc == "Q"){
            arrInt[i] = 12;
        }
        else if (cc == "K"){
            arrInt[i] = 13;
        }
        else if(cc == "A"){
            arrInt[i] = 1;
        }      
   
        else {
            arrayNum[i] = stoi(cc); //ubah jd int
            arrInt[i] = arrayNum[i];        
            if (arrInt[i] < 2 || arrInt[i] > 9){
                valid = false;
            }
        }
    }
    char Operators[] = {'+', '-', '*', '/'};
    if (!valid || userInput.length() >= 5){
        cout << "Input tidak valid!" << endl;
    }
    else {
        printAll(Operators, k, n, arrInt);
    }
}

void inputRandom() {
    int random, res;
    string toStr, toStr2;
    
    int i = 1;
    srand(time(0));
    for (int i = 0; i < 4; i ++){
        random = 1 + (rand() % 9);
        arrInt[i] = random;
    }

    char Operators[] = {'+', '-', '*', '/'};
    printAll(Operators, 3, 4, arrInt);
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

void lexicograph(char *inputStr, char *data, int terakhir, int idx) {
    int i;
    for (i = 0; i < 4; i++) {
        data[idx] = inputStr[i];
        if (idx == terakhir)
            cout << data << endl;
        else
            lexicograph(inputStr, data, terakhir, idx + 1);
    }
}

void GameSolver(string arrStr[], int arrNum[]) {
    char a, b, cc[1];
    int total = 0, total2 = 0, num = 0, num2 = 0;
    int numAA = 0, numBB = 0, numCC = 0, numDD = 0, numAB = 0, numCD = 0;

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
        cout << " = " << total << endl;

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

    for (int i = 0; i < 3; i++){
        strcpy(cc, arrStr[i].c_str());
        b = cc[0];

        if (i == 0){
            numAA = arrNum[0];
            numBB = arrNum[1];
            numAB = calculate(b, numAA, numBB);
        }
        if (i == 1){
            numCC = arrNum[2];
            numDD = arrNum[3];
            numCD = calculate(b, numCC, numDD);
        }
        if (i == 2){
            total2 = calculate(b, numAB, numCD);
        }
    }
    if (total2 == 24){
        bykSolusi++;
        cout << "solusi " << bykSolusi << ": ";
        cout << "[(" << arrNum[0] << "";
        cout << arrStr[0];
        cout << "" << arrNum[1] << ")";
        cout << arrStr[1];
        cout << "" << arrNum[2] << "]";
        cout << arrStr[2];
        cout << "" << arrNum[3] << "";
        cout << " = " << total2 << endl;

        // save ke txt LAGI
        ofstream myFile;
        myFile.open("solusi.txt", ofstream::app);
        myFile << "[(" << arrNum[0] << "";
        myFile << arrStr[0];
        myFile << "" << arrNum[1] << ")";
        myFile << arrStr[1];
        myFile << "" << arrNum[2] << "]";
        myFile << arrStr[2];
        myFile << "" << arrNum[3] << "";
        myFile << " = " << total2 << endl;
        myFile.close();
    }
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
        GameSolver(num2, arrInt);
        return;
    }
    for (int j = 0; j < n; j++) {
        printRec(set, (inputStr + set[j]), n, k - 1, arrNum);
    }
}

void printAll(char set[], int k, int n, int arrNum[]) {
    printRec(set, "", n, k, arrNum);
}