// week_1_lab_activities.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
//using namespace std; //inefficient for a lot of code due to loading a lot of unused functions

int square(int x) {
    return pow(x,2);
}

int PowerOf(int val, int power) {
    int output = val;
    for (int i = 1; i < power; i++) {
        output *= val;
    }
    return output;
    //return pow(val, power);
}

bool StringCheck(std::string str1, std::string str2) {
    return str1 == str2;
}

void Collatz(int value) {
    //assuming that input parameter is positive
    int output = value;
    int counter = 0;
    std::cout << "---" << std::endl;
    while (output != 1) {
        counter += 1;
        if (output % 2 == 0) {
            output /= 2;
        }
        else {
            output = output * 3 + 1;
        }
        std::cout << output << std::endl;
    }
    std::cout << "for a value of "<< value <<", the Collatz sequence length is "<<counter<<".\n---" << std::endl;
}

void Exercise8() { //indefinite loop until user willingly ends the loop with an input
    std::string temps1 = "a", temps2;

    while (not StringCheck(temps1, "end")) {
        // casting errors arise when attempting to use toupper() function withn the while loop for case insensitivity.
        std::cout << "Enter 'end' to stop loop: ";
        std::cin >> temps1;

    }
    std::cout << "bye\n";
}

void Exercise9() {
    
    int coordinates[2] = {0,0};

}

//void Bwah() {
//    std::string inp;
//    std::cout << "Bwah!\nResponce: ";
//    std::cin >> inp;
//    if (inp != ":3") {
//        std::cout << "D:";
//    }
//    else {
//        std::cout << ":D";
//    }
//    std::cout << std::endl;
//}

int main()
{
    int temp;
    std::string t = "This is a test string assigment to a variable";

    std::cout << "Hello World!\n:3"<< std::endl;
    //Bwah();
    std::cout << "Ex1: The square of 3 is: " << square(3) << std::endl;

    std::cout << "Ex2: N^x operation, in this example, 5^3 is equal: " << PowerOf(5, 3) << std::endl;

    std::cout << "Ex5 & 6: Collatz sequence\n Enter a positive integer: "<< std::endl;
    std::cin >> temp;
    Collatz(temp);
    std::cout << "Ex 7: Enter 'end' to end the loop" << std::endl;
    Exercise8();
    Exercise9();
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
