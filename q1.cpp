#include <iostream>
using namespace std;
int main() {
    int n;
    cout<<"enter a  number: ";
    cin>>n;
    int prime=1;
    if(n<=1) {
        prime=0;
    } else {
        for (int i=2;i<n;i++) {
            if(n%i==0) {
                prime=0;
                break;
            }
        }
    }

    if(prime==1) {
        cout<<n<<" is a prime number"<<endl;
        int next=n+1;
        while(true){
            int nextprime=1;
            for(int i=2;i<next;i++) {
                if (next%i==0) {
                    nextprime=0;
                    break;
                }
            }
            if(nextprime==1) {
                cout<<"the next prime number after "<<n<<" is "<<next<<endl;
                break;
            }
            next++;
        }
    } else {
        cout<<n<<"is not a prime number"<<endl;
        cout<<"factors of "<<n<<" are: ";
        for(int i=1;i<=n;i++) {
            if(n%i==0) {
                cout<<i<<" " ;
            }
        }
        cout<<endl;
    }

    return 0;
}