#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <array>
#include <bits/stdc++.h>
using namespace std;

int b[128]; // printable chars ranged in [0x20, 0x7f] in ASCII
const int ALPHABET_SIZE = 256;
static long MAXCHAR = 256;

int brute_force(string pattern, string text) {
    for(int i = 0; i < text.length() - pattern.length() + 1; ++i) {
        int j = 0;
        while (j < pattern.length() && text[i+j] == pattern[j]) {
            j += 1;
        }
        if (j == pattern.length()) {
            return i;
        }
    }
    return -1;
}

void shift_and(const string &t, const string &p) {
    int shift = 1;
    memset(b, 0, sizeof(b));
    for(int i = 0; i < p.size(); ++i) {
        b[p[i]] |= shift;
        shift <<= 1;
    }

    int d = 0;
    int mask = 1 << (p.size() - 1);
    for(int i = 0; i < t.size(); ++i) {
        d = ((d << 1) | 1) & b[t[i]];
        if(d & mask) printf("%d ", i - p.size() + 1);
    }
    putchar(10);
}

void BMH(string T, long n, string P, long m){
    long i, j, k, d[MAXCHAR + 1];
    for(j=0;j<=MAXCHAR; j++)d[j] = m;
    for(j=1;j<m;j++)d[P[j-1]] = m-j;
    i=m;
    while(i<=n){
        k=i;
        j=m;
        while(T[k-1]==P[j-1] && j>0){
            k--;j--;
        }
        if(j==0) cout<<"Casou em "<<k+1<<endl; 
        i+=d[T[i-1]];
    }
}

int main() {
    // LENDO ARQUIVOS DE TEXTO
    ifstream file("T500.txt");
    string T500;
    T500 = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    ifstream file2("T1000.txt");
    string T1000;
    T1000 = string((istreambuf_iterator<char>(file2)), istreambuf_iterator<char>());
    file2.close();

    ifstream file3("T1500.txt");
    string T1500;
    T1500 = string((istreambuf_iterator<char>(file3)), istreambuf_iterator<char>());
    file3.close();

    ifstream file4("T2000.txt");
    string T2000;
    T2000 = string((istreambuf_iterator<char>(file4)), istreambuf_iterator<char>());
    file4.close();

    ifstream file5("T5000.txt");
    string T5000;
    T5000 = string((istreambuf_iterator<char>(file5)), istreambuf_iterator<char>());
    file5.close();

    // CRIA VETOR COM OS TEXTOS
    string textos[5] = {T500, T1000, T1500, T2000, T5000};

    float brutal_force[50], bmh[50], bmhs[50], shift_and[50], shift_and_aprox[50];

    array<array<int, 10>, 5> matrixBrutalForce, matrixBMH, matrixBMHS, matrixShiftAnd, matrixShiftAndK1, matrixShiftAndK2;

    for(int i = 0; i < 5; i++) {
        for(int j=0; j<10; j++) {
            auto start = chrono::high_resolution_clock::now();
            int posi = brute_force("sociis", textos[i]);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed = end - start;
            brutal_force[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();

            /* cout<<"1\n";
            auto start1 = chrono::high_resolution_clock::now();
            cout<<textos[i].length();
            BMH(textos[i], textos[i].length(), "chimporimpola", 14);
            cout<<"3";
            auto end1 = chrono::high_resolution_clock::now();
            auto elapsed1 = end1 - start1;
            bmh[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed1).count(); */

            /* auto start = chrono::high_resolution_clock::now();
            int posi = brute_force("chimporimpola", textos[i]);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed = end - start;
            brutal_force[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();

            auto start = chrono::high_resolution_clock::now();
            int posi = brute_force("chimporimpola", textos[i]);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed = end - start;
            brutal_force[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();

            auto start = chrono::high_resolution_clock::now();
            int posi = brute_force("chimporimpola", textos[i]);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed = end - start;
            brutal_force[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed).count(); */
        } 
    }

    // ============================= FORÇA BRUTA ======================================  
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++){
            matrixBrutalForce[i][j] = brutal_force[i * 10 + j];
        }
    }

    for (const auto& row : matrixBrutalForce) {
        for (int i : row)
            std::cout << i << ' ';
        std::cout << '\n';
    }
    // ============================== BMH ======================================  
/*     for(int i = 0; i<50; i++) {
        cout<<bmh[i] << " ";
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++){
            matrixBMH[i][j] = bmh[i * 10 + j];
        }
    }

    for (const auto& row : matrixBMH) {
        for (int i : row)
            cout << i << ' ';
        cout << '\n';
    } */

/*     auto start2 = chrono::high_resolution_clock::now();
    cout << brute_force("chimporimpola", T500) << endl;
    auto end2 = chrono::high_resolution_clock::now();
    auto elapsed2 = end2 - start2;
    cout << "Tempo de execução: " << chrono::duration_cast<chrono::milliseconds>(elapsed2).count() << "ms" << endl;
    cout << "Tempo de execução: " << chrono::duration_cast<chrono::nanoseconds>(elapsed2).count() << "ns" << endl;

    auto start3 = chrono::high_resolution_clock::now();
    cout << brute_force("chimporimpola", T1000) << endl;
    auto end3 = chrono::high_resolution_clock::now();
    auto elapsed3 = end3 - start3;
    cout << "Tempo de execução: " << chrono::duration_cast<chrono::milliseconds>(elapsed3).count() << "ms" << endl;
    cout << "Tempo de execução: " << chrono::duration_cast<chrono::nanoseconds>(elapsed3).count() << "ns" << endl;

    auto start = chrono::high_resolution_clock::now();
    cout << brute_force("chimporimpola", T5000) << endl;
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    cout << "Tempo de execução: " << chrono::duration_cast<chrono::milliseconds>(elapsed).count() << "ms" << endl;
    cout << "Tempo de execução: " << chrono::duration_cast<chrono::nanoseconds>(elapsed).count() << "ns" << endl;


    string text = "O algoritmo de comparação shift-and é um algoritmo eficiente para realizar buscas de padrões em strings.";
    string pattern = "shift-and";

    cout << "-------------------------------- \n";
    auto start14 = chrono::high_resolution_clock::now();
    shift_and("Gamo Vâmos", "d");
    auto end14 = chrono::high_resolution_clock::now();
    auto elapsed14 = end14 - start14;
    cout << "Tempo de execução: " << chrono::duration_cast<chrono::milliseconds>(elapsed14).count() << " ms" << endl;
    cout << "Tempo de execução: " << chrono::duration_cast<chrono::nanoseconds>(elapsed14).count() << " ns" << endl;
 */
    return 0;
}