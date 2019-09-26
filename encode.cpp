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

	int args[2] = {};
	for(int ii = 0 ; ii < 2; ii++ )
    {
		char *p;
		errno = 0;
		//convert argv to base 10 integer;
		long conv = strtol(argv[ii + 2], &p, 10);

        // cout << conv << endl;

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

 //   cout << "format inputs : " << args [0] << "\t" << args [1]<< endl;

    ofstream outStream;         //Input stream
    ifstream inStream;          //Output stream

    string infile;              // string variable to store the name of the input file

    int inFormat = args[0];     //int variable to get the input file format
    int outFormat = args[1];    //int variable to get the output file format
    string exit = "exit";

    cout<<"input file name : ";
    cout<<argv[1]<<endl;

//    cout << "Please enter the name of the input file : ";
//    getline(cin,infile);        // Get the name of the input file

    //while(file!=exit)
/*    do{
        cout <<"\n1 :-\tUTF-8\n2 :-\tUTF-32\n3 :-\tBaudot Code\n4 :-\tMorse Code\n\n";
        cout << "Please enter the NUMBER of the input file inFormat : ";
        //getline(cin,inFormat);
        
        cin >> inFormat;
        cout << endl;

        if (inFormat == 99)
        {
            cout << "CODE 99...EXITING\n";
            return 0;
        }

        if (inFormat <= 0 || inFormat > 4)
        {
            cout<<"WRONG inFormat\nPlease try again\n";
            //return 0;
        }

    }while (inFormat <= 0 || inFormat > 4);*/

    cout<< "input : " <<inFormat<<"\noutput : " <<outFormat<<endl;

    return 0;
}