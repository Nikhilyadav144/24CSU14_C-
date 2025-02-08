#include <iostream>
using namespace std;
int main() {
    int n;
    cout<<"enter the number of elements: ";
    cin>>n;
    int arr[n];
    cout << "enter "<<n<< " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "array elements are: ";
    for (int j=0;j<n;j++) {
        cout<<arr[j]<<" ";
    }
    cout<<endl;
    cout<<"reverse of the array is: ";
    for (int j=n-1;j>=0;j--) {
        cout<<arr[j]<< " ";
    }
    cout<<endl;
    int largest,secondlargest;
    int smallest,secondsmallest;

    for(int i=0;i<n;i++) {
        if(arr[i]>largest) {
            secondlargest=largest;
            largest=arr[i];
        } else if(arr[i]>secondlargest&&arr[i]<largest) {
            secondlargest=arr[i];
        }
        if(arr[i]<smallest) {
            secondsmallest=smallest;
            smallest=arr[i];
        } else if(arr[i]<secondsmallest&&arr[i]>smallest) {
            secondsmallest=arr[i];
        }
    }
    cout<<"\nsecond largest element: "<<secondlargest<<endl;
    cout<<"second smallest element: "<<secondsmallest<<endl;

return 0;
}