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

    // Morse code Array
    //A-Z 0-25
    //26-35 digits
string MORSE[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", "--..--", ".-.-.-", "..--..", "-..-.", "-....-", "-.--.", "-.--.-"};

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

    ofstream outStream;             // Input stream
    ifstream inStream;              // Output stream

    string inFormat = argv[2];         // int variable to get the input file format
    string outFormat = argv[3];        // int variable to get the output file format

    std::cout<<"input file name : ";
    std::cout<<argv[1]<<endl;

    inStream.open(argv[1]);             // "connected" to input file

    outStream.open("outFile.txt");   // "connected" to output file

    char temp;          //Store the last char from file
    int ind = 0;        //int val of temp
    string morseTemp;   //store intermediate morse code

    /*UTF8 to Morse*/

    if (outFormat == "m") //add smaller characters
    {
        while(inStream.get(temp))
        {
            if (temp != ' ')
            {
                ind = temp;
                if (ind>=95 && ind <=122)
                {
                    outStream << MORSE[ind-97] << " ";
                }
                else
                {
                    std::cout<<ind<<endl;
                    outStream << MORSE[ind-65] << " ";
                }
            }
    
            if (temp == ' ')
                outStream << temp;
        }
    }

    /* 
    
    Morse to UTF8 
    
    make strings of morse alphabets and then at a space character 
    convert them to utf8 by comparing with the global MORSE array 
    and then concat that to a word, seperate words when double spaces show up
    
    */

    char daAlphabet ;   //A
    bool wasSpace = false;          //true if last character was a space
    if (inFormat == "m") 
    {
        while(inStream.get(temp))  //get dots and dashes
        {
            if (temp != ' ')       //check space char
            {
                morseTemp = morseTemp + temp;  //make a string until a space arrives
 //               std::cout<<morseTemp << endl;
                wasSpace = false;
            }

            if (temp == ' ')       // when space
            {
                if(wasSpace)
                {
                    wasSpace = false;
                    outStream << " ";
                    morseTemp = "";
                }
                else 
                {
                    for (int i = 0; i <= 35 ; i++)  //morse to utf8
                    {
                        if(morseTemp == MORSE[i])
                        {
                            daAlphabet = 'A'+i;
                            outStream << daAlphabet;
                            i = 36;
                        }
                    }
                }
                wasSpace = true;
                morseTemp = "";
            }        
        }
    }

//    std::cout << sizeof(string)<<endl;

    //check end of file
    if(inStream.eof())
    {
        std::cout<<"EOF here\n";
    }

    inStream.close();
    outStream.close();

//    std::cout<< "input : " <<inFormat<<"\noutput : " <<outFormat<<endl;

    return 0;
}