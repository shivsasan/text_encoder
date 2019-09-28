#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fstream>
#include<limits.h>

using namespace std;

void toU8();

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

string BC_LETTERS[] = {"NULL", "E", " ", "A", " ", "S", "I", "U"," ", "D", "R", "J", "N", "F", "C", "K", "T", "Z", "L", "W", "H", "Y", "P", "Q","O", "B", "G", "Figures", "M", "X", "V", "Letters"};
string BC_FIGURES[] = {"NULL", "3", " ", "-", " ", "'", "8", "7"," ", " ", "4", "BELL", ",", "!", ":", "(", "5", "+", ")", "2", "$", "6", "0", "1","9", "?", "&", "Figures", ".", "/", "=", "Letters"};

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
        if(wasSpace2){}
        char mode = 'L';           //mode bit defaults to letters
        int lastIndex;
        string lastString;

 //     char daAlphabet;
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
                for(int i = 0; i <= 31 ; i++)     //get index form BC
                {
                    if(bcTemp == BC[i])           //
                    {
                        cout<< BC[i]<<endl;
                        if(mode == 'L')
                        {
                            cout<< BC_LETTERS[i]<<endl;
                            if(i==27)
                            {
                                mode = 'F';
                            }
                            if(i==31)
                            {
                                mode = 'L';
                            }
                            if(i!=27)
                            {
                                outStream << BC_LETTERS[i];
                            }
                        }

                        if(mode == 'F')
                        {
                            cout<< BC_FIGURES[i]<<endl;
                            if(i==31)
                            {
                                mode = 'L';
                            }
                            if(i==27)
                            {
                                mode = 'F';
                            }
                            if(i!= 31)
                            {
                                outStream<< BC_FIGURES[i];
                            }
                        }
                        bcTemp = "";
                        i=32;
                        lastIndex = i;
                    }
                }

                wasSpace2 = true;
 //               bcTemp = "";
            }
            lastString = bcTemp;        
        }

        for(int j = 0; j <= 31 ; j++)     //get index form BC
                {
                    if(lastString == BC[j])           //
                    {
                        cout<< BC[j]<<endl;
                        if(mode == 'L')
                        {
                            cout<< BC_LETTERS[j]<<endl;
                            if(j==27)
                            {
                                mode = 'F';
                            }
                            if(j==31)
                            {
                                mode = 'L';
                            }
                            if(j!=27)
                            {
                                outStream << BC_LETTERS[j];
                            }
                        }

                        if(mode == 'F')
                        {
                            cout<< BC_FIGURES[j]<<endl;
                            if(j==31)
                            {
                                mode = 'L';
                            }
                            if(j==27)
                            {
                                mode = 'F';
                            }
                            if(j!= 31)
                            {
                                outStream<< BC_FIGURES[j];
                            }
                        }
                    }
                }

       /* if (lastIndex != 0)
        {
            if(mode == 'L')
            {
                cout<<BC_LETTERS[lastIndex]<<endl;
                outStream << BC_LETTERS[lastIndex];
            }

            if(mode == 'F')
            {
                cout<<BC_FIGURES[lastIndex]<<endl;
                outStream << BC_FIGURES[lastIndex];
            }
        }*/
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
