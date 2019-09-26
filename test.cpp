#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main( )
{
    string theFile;
    cout<<"file name : ";
    getline(cin,theFile);

    ofstream outStream;
    outStream.open(theFile);
    
    for (int i = 1; i <= 10; ++i)
        outStream << "Hello\t" << i << endl;
    outStream.close();
    return 0;
}