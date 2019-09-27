#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fstream>
#include<limits.h>

using namespace std;

#define INPUT_FORMAT 0
#define OUTPUT_FORMAT 1

int main(int argc ,char* argv[])
{
    if(argc < 4){
		fprintf( stderr, "Error: Unsufficient arguments!\n" );
		exit(EXIT_FAILURE); 
	} 
	else if(argc > 4){
		fprintf( stderr, "Error: Too many arguments!\n" );
		exit(EXIT_FAILURE);
	}

    /* Input and output format numbers

        1 :-    UTF-8
        2 :-    UTF-32
        3 :-    Baudot Code
        4 :-    Morse Code

    */

	int args[2] = {}; //replace this later 
	for(int ii = 0 ; ii < 2; ii++ )
    {
		char *p;
		errno = 0;
		//convert argv to base 10 integer;
		long conv = strtol(argv[ii + 2], &p, 10);

		// Check for errors: e.g., the string does not represent an integer
		// or the integer is larger than int
		if (errno != 0 || *p != '\0') 
        {
		    // Put here the handling of the error, like exiting the program with
		    // an error message
		    fprintf( stderr, "Error: ERROR for casting number!\n" );
		    exit(EXIT_FAILURE);
		}

        if (conv > 4)
        {
            fprintf(stderr, "Error: Argument numbers must be smaller than 4!\n");
            exit(EXIT_FAILURE);
        }
        
        else 
        {
		    // No error
		    if(conv <= 0)
            {
		    	fprintf( stderr, "Error: All arguments must be positive.\n" );
		    	exit(EXIT_FAILURE);
		    }

		    args[ii] = conv;
		}
	}

    ofstream outStream;             // Input stream
    ifstream inStream;              // Output stream

    string infile;                  // string variable to store the name of the input file

    int inFormat = args[0];         // int variable to get the input file format
    int outFormat = args[1];        // int variable to get the output file format
    string exit = "exit";

    cout<<"input file name : ";
    cout<<argv[1]<<endl;

    inStream.open(argv[1]);             // "connected" to input file

    outStream.open("outputFile.txt");   // "connected" to output file

    char temp ;
    while(!inStream.eof())
    {
        inStream >> temp;
        temp += temp;
    }

    if(inStream.eof())
    {
        cout<<"EOF here\n";
    }

    cout << temp << endl;
    outStream<<"sum: "<<temp;
    //inStream >> f >> s >> t;
    //outStream << "sum : " << f + s + t << endl;

    inStream.close();
    outStream.close();

    cout<< "input : " <<inFormat<<"\noutput : " <<outFormat<<endl;

    return 0;
}

string morse(int index)
{
    string temp[26];
    temp[0] =".-";
    temp[1] ="-...";
    temp[2] ="-.-.";
    temp[3] ="-..";
    temp[4] =".";
    temp[5] ="..-.";
    temp[6] ="--.";
    temp[7] ="....";
    temp[8] ="..";
    temp[9] =".---";
    temp[10] ="-.-";
    temp[11] =".-..";
    temp[12] ="--";
    temp[13] ="-.";
    temp[14] ="---";
    temp[15] =".--.";
    temp[16] ="--.--";
    temp[17] =".-.";
    temp[18] ="...";
    temp[19] ="-";
    temp[20] ="..-";
    temp[21] ="...-";
    temp[22] =".--";
    temp[23] ="-..-";
    temp[24] ="-.--";
    temp[25] ="--..";
    temp[26] =".......";

    temp[27] =".----" // 1
    temp[28] ="..---" // 2
    temp[29] ="...--" // 3
    temp[30] ="....-" // 4
    temp[31] ="....." // 5
    temp[32] ="-...." // 6
    temp[33] ="--..." // 7
    temp[34] ="---.." // 8
    temp[35] ="----." // 9
    temp[36] ="-----" // 0
    
}