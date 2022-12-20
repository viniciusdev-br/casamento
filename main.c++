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

void shift_and_function(const string &t, const string &p) {
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
        if(d & mask) cout<<(i - p.size() + 1);
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

void BMHS(string T, long n, string P, long m){
    long i, j, k, d[MAXCHAR + 1];
    for(j=0;j<=MAXCHAR;j++)d[j]=m+1;
    for(j=1;j<=m;j++)d[P[j-1]]=m-j+1;
    i=m;
    while(i<=n){
        k=i;
        j=m;
        while(T[k-1]==P[j-1] && j>0){k--;j--;}
        if(j==0)
        cout<<"Casou em "<<k+1<<endl;
        i+=d[T[i]];
    }
}

void Shift_And_Aproximado(string T, long n, string P, long m, long k){
    long Masc[MAXCHAR],i,j,Ri,Rant,Rnovo;
    long R[2+1];
    for(i=0;i<MAXCHAR;i++)Masc[i]=0;
    for(i=1;i<=m;i++){Masc[P[i-1] + 127] |= 1 << (m-i);}
    R[0] = 0; Ri = 1 << (m-1);
    for(j=1;j<=k;j++)R[j]=(1 << (m-j)) | R[j-1];
    for(i=0;i<n;i++){
        Rant= R[0];
        Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & Masc[T[i] + 127];
        R[0] = Rnovo;
        for(j=1;j<=k;j++){
            Rnovo=((((unsigned long)R[j]) >> 1) & Masc[T[i]+127]) | Rant |(((unsigned long)(Rant | Rnovo)) >> 1 );
            Rant= R[j];R[j]= Rnovo | Ri;
        }
        if((Rnovo & 1) != 0) cout<<"Casou em "<<i<<endl;
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

    float brutal_force[50], bmh[50], bmhs[50], shift_and[50], shift_and_aproxk1[50], shift_and_aproxk2[50];

    array<array<int, 10>, 5> matrixBrutalForce, matrixBMH, matrixBMHS, matrixShiftAnd, matrixShiftAndK1, matrixShiftAndK2;

    for(int i = 0; i < 5; i++) {
        for(int j=0; j<10; j++) {
            auto start = chrono::high_resolution_clock::now();
            int posi = brute_force("chimporimpola", textos[i]);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed = end - start;
            brutal_force[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();

            auto start1 = chrono::high_resolution_clock::now();
            BMH(textos[i], textos[i].length(), "chimporimpola", 14);
            auto end1 = chrono::high_resolution_clock::now();
            auto elapsed1 = end1 - start1;
            bmh[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed1).count();

            start = chrono::high_resolution_clock::now();
            BMHS(textos[i], textos[i].length(), "chimporimpola", 14);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            bmhs[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();

            start = chrono::high_resolution_clock::now();
            shift_and_function(textos[i], "chimporimpola");
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            shift_and[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();

            start = chrono::high_resolution_clock::now();
            Shift_And_Aproximado(textos[i], textos[i].length(), "chimporimpola", 14, 1);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            shift_and_aproxk1[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
            
            start = chrono::high_resolution_clock::now();
            Shift_And_Aproximado(textos[i], textos[i].length(), "chimporimpola", 14, 2);
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
            shift_and_aproxk2[i * 10 + j] = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
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
    float media;
    float Y_brutal_force[5];
    for (int i=0; i<5; i++) {
        media = 0;
        for (int j=0; j<10; j++) {
            media = media + matrixBrutalForce[i][j];
        }
        Y_brutal_force[i] = media/10;
    }
    for (int i = 0; i < 5; i++) {
        cout << Y_brutal_force[i] << " ";
    }
    cout << '\n';
    cout << '\n';
    // ============================== BMH ====================================== 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++){
            matrixBMH[i][j] = bmh[i * 10 + j];
        }
    }

    for (const auto& row : matrixBMH) {
        for (int i : row)
            cout << i << ' ';
        cout << '\n';
    } 
    float Y_bmh[5];
    for (int i=0; i<5; i++) {
        media = 0;
        for (int j=0; j<10; j++) {
            media = media + matrixBMH[i][j];
        }
        Y_bmh[i] = media/10;
    }
    for (int i = 0; i < 5; i++) {
        cout << Y_bmh[i] << " ";
    }
    cout << '\n';
    cout << '\n';
    // ============================== BMHS ====================================== 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++){
            matrixBMHS[i][j] = bmhs[i * 10 + j];
        }
    }

    for (const auto& row : matrixBMHS) {
        for (int i : row)
            cout << i << ' ';
        cout << '\n';
    } 
    float Y_bmhs[5];
    for (int i=0; i<5; i++) {
        media = 0;
        for (int j=0; j<10; j++) {
            media = media + matrixBMHS[i][j];
        }
        Y_bmhs[i] = media/10;
    }
    for (int i = 0; i < 5; i++) {
        cout << Y_bmhs[i] << " ";
    }
    cout << '\n';
    cout << '\n';
    // ============================== SHIFT AND ====================================== 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++){
            matrixShiftAnd[i][j] = shift_and[i * 10 + j];
        }
    }

    for (const auto& row : matrixShiftAnd) {
        for (int i : row)
            cout << i << ' ';
        cout << '\n';
    } 
    
    float Y_SHIF_AND[5];
    for (int i=0; i<5; i++) {
        media = 0;
        for (int j=0; j<10; j++) {
            media = media + matrixShiftAnd[i][j];
        }
        Y_SHIF_AND[i] = media/10;
    }
    for (int i = 0; i < 5; i++) {
        cout << Y_SHIF_AND[i] << " ";
    }
    cout << '\n';
    cout << '\n';
    
    // ============================== SHIFT AND APROXIMADO COM K = 1 ====================================== 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++){
            matrixShiftAndK1[i][j] = shift_and_aproxk1[i * 10 + j];
        }
    }

    for (const auto& row : matrixShiftAndK1) {
        for (int i : row)
            cout << i << ' ';
        cout << '\n';
    } 
    
    float Y_SHIF_AND_K1[5];
    for (int i=0; i<5; i++) {
        media = 0;
        for (int j=0; j<10; j++) {
            media = media + matrixShiftAnd[i][j];
        }
        Y_SHIF_AND_K1[i] = media/10;
    }
    for (int i = 0; i < 5; i++) {
        cout << Y_SHIF_AND_K1[i] << " ";
    }
    cout << '\n';
    cout << '\n';
    
    // ============================== SHIFT AND APROXIMADO COM K = 2 ====================================== 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++){
            matrixShiftAndK2[i][j] = shift_and_aproxk2[i * 10 + j];
        }
    }

    for (const auto& row : matrixShiftAndK2) {
        for (int i : row)
            cout << i << ' ';
        cout << '\n';
    } 
    
    float Y_SHIF_AND_K2[5];
    for (int i=0; i<5; i++) {
        media = 0;
        for (int j=0; j<10; j++) {
            media = media + matrixShiftAndK2[i][j];
        }
        Y_SHIF_AND_K2[i] = media/10;
    }
    for (int i = 0; i < 5; i++) {
        cout << Y_SHIF_AND_K2[i] << " ";
    }
    cout << '\n';
    cout << '\n';


    return 0;
}