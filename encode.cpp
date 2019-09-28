#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fstream>
#include<limits.h>

using namespace std;

    /*
      utf8   ->    u8
      utf32  ->    u32
      baudot code ->  bc
      morsecode -> mc
    */

    // Morse code Array
    //A-Z 0-25
    //26-35 digits
string MORSE[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", "--..--", ".-.-.-", "..--..", "-..-.", "-....-", "-.--.", "-.--.-"};

// 0-31
string BC[] = {"00000000","00000001","00000010","00000011","00000100","00000101","00000110","00000111","00001000","00001001","00001010","00001011","000001100","00001101","00001110","00001111","00010000","00010001","00010010","00010011","00010100","00010101","00010110","00010111","00011000","00011001","00011010","00011011","00011100","00011101","00011110","00011111"};

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

    string inFormat = argv[2];         // int variable to get the input file format
    string outFormat = argv[3];        // int variable to get the output file format

    //CHECKING INPUTS
    
    if (inFormat != "mc" && inFormat != "bc" && inFormat != "u8" && inFormat != "u32")
    {
        cout<<"ERROR: INVALID FORMAT!\n";
        exit(1);
    }

    if (outFormat != "mc" && outFormat != "bc" && outFormat != "u8" && outFormat != "u32")
    {
        cout<<"ERROR: INVALID FORMAT!\n";
        exit(1);
    }

    if (outFormat == inFormat)
    {
        cout<<"OUTPUT is already the same format as INPUT\n";
        return 0;
    }

    ofstream outStream;             // Input stream
    ifstream inStream;              // Output stream

    std::cout<<"input file name : ";
    std::cout<<argv[1]<<endl;

    inStream.open(argv[1]);             // "connected" to input file

    outStream.open("outFile.txt");   // "connected" to output file

    char temp;          //Store the last char from file
    int ind = 0;        //int val of temp
    string morseTemp;   //store intermediate morse code
    string bcTemp;      //store intermediate bc code

    /*   
    UTF8 to Morse   
    */

    if (outFormat == "mc") //add smaller characters
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

    if (inFormat == "mc")  //morse to utf8
    {
        char daAlphabet ;   //A
        bool wasSpace = false;          //true if last character was a space

        while(inStream.get(temp))  //get dots and dashes
        {
            if (temp != ' ')       //check space char
            {
                morseTemp = morseTemp + temp;  //make a string until a space arrives
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
   
    if(inFormat == "bc") //bc to utf8
    {
        bool wasSpace2 = true;
        if(wasSpace2)
        {}
 //       char daAlphabet;
        while(inStream.get(temp))  //get 0 and 1
        {
            if (temp != ' ')       //check space char
            {
                bcTemp = bcTemp + temp;  //make a string until a space arrives
                std::cout<<bcTemp<<"!"<<endl;
                wasSpace2 = false;
            }

            if (temp == ' ')       // when space
            {
                for(int i = 0; i <= 31 ; i++)
                {
                    if(bcTemp == BC[i])
                    {
                        cout<< BC[i]<<endl;
                        bcTemp = "";
                        i=32;
                    }
                }

                wasSpace2 = true;
 //               bcTemp = "";
            }        
        }
        //add outStream here
    }

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