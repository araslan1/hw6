#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <ctime> 
#include <cstdlib>
#include <random>
#include <chrono>

//longest string is 28 letters 
// only contain letters and '0' - '9' (not case sensitive)

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w_array[5] {0, 0, 0, 0, 0}; 
        int power_5 = pow(36, 5); 
        int power_4 = pow(36, 4); 
        int power_3 = pow(36, 3);
        int power_2 = pow(36, 2); 
        int power_1 = 36; 
        int power_0 = 1; 
        int rValue_counter = 4;
        HASH_INDEX_T sum = 0; 
        int sub_string_counter = 0;  
        for (int i = k.size() - 1; i >= 0; i--){ 
            if (i == 0){
                sum += pow(36, sub_string_counter) * letterDigitToNumber(k[i]);
                w_array[rValue_counter] = sum; 
                rValue_counter--;
                break;
            }
            if (sub_string_counter == 0){
                sum += power_0*letterDigitToNumber(k[i]); 
                sub_string_counter++;
            }else if (sub_string_counter == 1){
                sum += power_1*letterDigitToNumber(k[i]); 
                sub_string_counter++;
            }else if (sub_string_counter == 2){
                sum += power_2*letterDigitToNumber(k[i]); 
                sub_string_counter++;
            }else if (sub_string_counter == 3){
                sum += power_3*letterDigitToNumber(k[i]); 
                sub_string_counter++;
            }else if (sub_string_counter == 4){
                sum += power_4*letterDigitToNumber(k[i]); 
                sub_string_counter++;
            }else{
                sum += power_5*letterDigitToNumber(k[i]); 
                w_array[rValue_counter] = sum; 
                // std::cout << rValue_counter << " " << sum << std::endl; 
                rValue_counter--;
                sub_string_counter = 0; 
                sum = 0; 
            }
            //check if you're getting to end of string?
    
        }
        return rValues[0]*w_array[0] + rValues[1]*w_array[1] + rValues[2]*w_array[2] + rValues[3]*w_array[3] + rValues[4]*w_array[4]; 
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T my_index;
        if (letter > 'Z'){
            //lowercase letterletter
            my_index = letter - 97; 
        }else if(letter > '?') {
            //uppercase
            my_index = letter - 65; 
        }else{
            //number
            my_index = letter - 22; 
        }
        return my_index; 
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
