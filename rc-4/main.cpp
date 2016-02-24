#include <iostream>
#include <string>


void rc4_encrypt(unsigned char *text, unsigned char *key, unsigned char *target_text);
void ksa(unsigned char *key, unsigned char *S);
void swap(int &a, int &b);
unsigned char next_byte(unsigned char *S, int &x, int &y);

using namespace std;

int main(int argc, const char * argv[]) {
    
    string s_text, s_key;
    
    getline(cin, s_text);
    getline(cin, s_key);
    
    unsigned char *text = new unsigned char[strlen(s_text.c_str())];
    unsigned char *key = new unsigned char[strlen(s_key.c_str())];
    unsigned char *c_text = new unsigned char[strlen(s_text.c_str())];
    
    for(int i = 0; i < strlen(s_text.c_str()); i++)
    {
        text[i] = (unsigned char) s_text[i];
    }
    
    cout << "Inputed text len is " << strlen((char *) text) << endl;
    
    for(int i = 0; i < strlen(s_key.c_str()); i++)
    {
        key[i] = (unsigned char) s_key[i];
    }
    
    rc4_encrypt(text, key, c_text);
    
    cout << "Text len after rc4 encryption: " << strlen((char *) text) << endl;
    cout << text <<endl;
    
    rc4_encrypt(text, key, text);
    
    cout << strlen((char *) text) << endl;
    cout << text <<endl;
    
    delete [] text;
    delete [] c_text;
    
    return 0;
}

void rc4_encrypt(unsigned char *text, unsigned char *key, unsigned char *target_text)
{
    int i=0, j=0;
    unsigned char S[256];
    ksa(key, S);
    for(int c = 0; c < strlen((char *)text); c++)
    {
        //cout << "Text len during enctypting iteration " << c << " is: " << strlen((char *) text) << endl;
        unsigned char k = next_byte(S, i, j);
        //target_text[c] = text[c] ^ k;
        text[c] ^= k;
    }
}

void ksa(unsigned char *key, unsigned char *S)
{
    int L = sizeof(key);
    for(int i = 0; i < 256; i++)
    {
        S[i] = i;
    }
    
    int j = 0;
    for(int i = 0; i < 256; i++)
    {
        j = (j + S[i]  + key[i % L]) % 256;
        swap(S[i], S[j]);
    }
}

unsigned char next_byte(unsigned char *S, int &i, int &j)
{
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    
    swap(S[i], S[j]);
    
    int t = (S[i] + S[j]) % 256;
    
    unsigned char k = S[t];
    return k;
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}