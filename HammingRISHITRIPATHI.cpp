//
//  main.cpp
//  Hamming code
//
//  Created by Rishi Tripathi on 04/09/18.
//  Copyright © 2018 Rishi Tripathi. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

void convertToBinary(int n, int *array);

// To calculate no of parity bits(r).
int parityBits(int noOfBits){
    int m = noOfBits + 1;
    int s = 0;
    int r = 0;
    while (true) {
        s += 2*2;
        r++;
        if(s>m){
            return (r+1);
        }
    }
}

// To create an array of parity bits.
void parityBitsArray(string message, int newSize, int *newMessage){
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < newSize; i++){
        if(i + 1  == pow(2,count2)){
            *newMessage = 0;
            newMessage++;
            count2++;
        }
        else{
            if(message[count1] == '1'){
                *newMessage = 1;
                newMessage++;
            }
            else {
                *newMessage = 0;
                newMessage++;
            }
            count1++;
        }
    }
}

// To calculate ri.
int calculateRi(int newMessage[], int newSize, int r, int i){
    int binaryArray[r];
    int j = 1;
    int count = 0;
    while (j <= newSize) {
        convertToBinary(j, &binaryArray[r-1]);
        if(binaryArray[r-i-1] == 1) {
            if(newMessage[j-1] == 1) {
                count++;
            }
        }
        j++;
    }
    if(count % 2 != 0) {
        return 1;
    }
    return 0;
}

//void convertToBinary(int i);
void convertToBinary(int n, int *array)
{
    
    while(n!=0)
    {
        int r = n % 2;
        *array-- = r;
        n /= 2;
    }
}

int convertToDecimal(int array[], int r){
    int sum = 0;
    for (int i = 0, j = r-1-i; i < r; i++, j--) {
        sum += pow(2, i) * array[j];
    }
    return sum;
}

int main(int argc, const char * argv[]){
    string message;
    
    cout<<"Enter the bit message : ";
    cin>>message;
    cout<<"Original Message = "<<message<<endl;
    int sizeOfMessage = int(message.length());
    
    int noOfParityBits = parityBits(sizeOfMessage);
    cout<<"No Of parity Bits = "<<noOfParityBits<<endl;
    
    int newSize = sizeOfMessage + noOfParityBits;
    int newMessage[newSize];
    
    parityBitsArray(message,newSize, newMessage);
    cout<<"New Array of message with parity = ";
    for (int i = 0; i < newSize; i++) {
        cout<<newMessage[i];
    }
    cout<<endl;
    
    for (int i = 0; i < noOfParityBits; i++) {
        int Ri = calculateRi(newMessage, sizeOfMessage, noOfParityBits, i);
        cout<<"r"<<i+1<<" "<<Ri<<endl;
        newMessage[int(pow(2,i) - 1)] = Ri;
    }
    cout<<"Sending Data = ";
    for (int i = 0; i < newSize; i++){
        cout<<newMessage[i];
    }
    cout<<endl;
    
    int nth;
    cout<<"Which bit position you want to toggle (must be less than "<<newSize<<") = ";
    cin>>nth;
    // Toggling a bit
    newMessage[nth-1] ? newMessage[nth-1]=0 : newMessage[nth-1]=1;
    
    cout<<"Recieving Data (wrong "<<nth<<"th bit) = ";
    for (int i = 0; i < newSize; i++){
        cout<<newMessage[i];
    }
    cout<<endl;
    
    int toggledBitBinary[noOfParityBits];
    for (int i = 0, j = noOfParityBits-1; i < noOfParityBits; i++, j--) {
        toggledBitBinary[j] = calculateRi(newMessage, sizeOfMessage, noOfParityBits, i);
        cout<<"r"<<i+1<<" "<<toggledBitBinary[j]<<endl;
    }
    int toggledBitposition = convertToDecimal(toggledBitBinary, noOfParityBits);
    cout<<"Toggled Bit position = "<<toggledBitposition<<endl;
    cout<<"Toggled Bit index = "<<toggledBitposition-1<<endl;
    
    
    // correction of data
    newMessage[toggledBitposition-1] ? newMessage[toggledBitposition-1]=0 : newMessage[toggledBitposition-1]=1;
    
    cout<<"Recieving correct data = ";
    for (int i = 0; i<newSize; i++) {
        cout<<newMessage[i];
    }
    cout<<endl;
    
    return 0;
}



