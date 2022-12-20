// Bitap (shift-or, shift-and) algorithm
// Preprocessing takes O(m), matching takes O(n),
// where n is the length of the text, m is the length of the pattern
// Require m < the number of bits of integer variable
#include <bits/stdc++.h>
using namespace std;

int b[128]; // printable chars ranged in [0x20, 0x7f] in ASCII

// shift_and use 1 represents valid bit.
void shift_and(const string &t, const string &p)
{
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

int main() {
    string text = "Why does this happen my program says", pattern = "program";
    shift_and(text, pattern);
}