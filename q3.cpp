#include <iostream>
using namespace std;
void reversestring(string &str) {
    int len=str.length();
    for (int i=0;i<len/2;i++) {
        char temp=str[i];
        str[i]=str[len-1-i];
        str[len-1-i]=temp;
    }
}
bool palindrome(string str) {
    string reversed = str;
    reversestring(reversed);
    return str==reversed;
}
void countfrequencies(string str) {
    int freq[256]={0};
    for (int i=0;i<str.length();i++) {
        if (str[i]!=' ')
            freq[(int)str[i]]++;
    }
    cout <<"\ncharacter frequencies:\n";
    for (int i=0;i<256;i++) {
        if (freq[i]>0) {
            cout<<char(i)<<": "<<freq[i]<<endl;
        }
    }
}
void replacevowels(string &str, char symbol) {
    for (int i=0;i<str.length();i++) {
        if (str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'||
            str[i]=='A'||str[i]=='E'||str[i]=='I'||str[i]=='O'||str[i]=='U') {
            str[i]=symbol;
        }
    }
}
int main() {
    string str;
    cout<< "Enter a string: ";
    getline(cin, str);
    if (palindrome(str))
        cout<< "string is a palindrome!!\n";
    else
        cout<< "string is NOT a palindrome!!\n";
    countfrequencies(str);
    char symbol;
    cout<<"\nenter the symbol to replace vowels: ";
    cin>>symbol;
    replacevowels(str, symbol);
    cout<<"updated string with vowels replaced: "<<str<<endl;
    return 0;
}