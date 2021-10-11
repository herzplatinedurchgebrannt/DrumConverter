#include <iostream>

using namespace std;


void printArray(int *a, int size){
    for (int i = 0; i < size; i++){
        cout << a[i] << endl;
    }
}

void changeArray(int *a, int size){
    for (int i = 0; i < size; i++){
        a[i] = a[i]+10;
    }
}

void changeInt(int *a){
    *a = 10;
}

void doNothing(int a){
    a = 20;
}

int main(){

    int a = 50;
    int b[3] = {1,4,5};

/*
    cout << &b << endl;
    cout << *&a << endl;


    cout << *b << endl;
    cout << *(b+1) << endl;*/

    // change array
    printArray(b,3);
    changeArray(b, 3);
    printArray(b,3);
    cout << "-------" << endl;
    cout << a << endl;
    changeInt(&a);
    cout << a << endl;
    doNothing(a);
    cout << a << endl;

    //*&a = 5;

    //change(a);


/*
    cout << sizeof(b) << endl;


    for (int i = 0; i < sizeof(b); i++){
        cout << b[i] << endl;
    }
*/


    return 1;
}

