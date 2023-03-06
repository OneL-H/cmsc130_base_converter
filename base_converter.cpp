#include <iostream>
using namespace std;

char determine_validity(string inp, int base);
string convert_bases(string init_number, int init_base, int target_base);
unsigned long long whole_to_base_10(string inp, int init_base);
string whole_base_10_to_another(unsigned long long inp, int target_base);
string fraction_to_another_base(unsigned long long numerator, unsigned long long denominator, int target_base);
unsigned long long power(int base, int exponent);

char valid_chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
int ceil_log_2[16] = {0, 0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4};

// NOTES: unsigned long long = 2^64
// therefore, maximum character to represent chars of radix 16
// log_2 16 = 4, meaning for every character of base 16 turns into 4 bits
// meaning the maximum space for 16 would be 64 / 4 = 16 characters
// but that gets multiplied in the fraction_to_another_base function
// so you theoretically have 15 characters to spare for base 16???
// and since log_2 x for x < 16 is less than 4, i CAN make the limits for bases < 16
// greater based upon 64 / log_2 x
// nah screw it, ill just make the decimal li

int main()
{
    while (true)
    {
        string input_base_x;

        cout << "Enter number to convert, or enter \"Q\" to [Q]uit" << endl;
        cin >> input_base_x;

        if (input_base_x == "Q")
        {
            cout << "Quitting...";
            break;
        } // exit if "Q" is entered

        int init_base;
        cout << "Indicate base of input number:" << endl;
        cin >> init_base;

        if (2 > init_base || init_base > 16)
        {
            cout << "Invalid base input (only from 2 to 16)" << endl;
            continue;
        }

        char validity_result = determine_validity(input_base_x, init_base);
        if (validity_result != '\0')
        {
            cout << "Invalid character detected: " << validity_result << endl;
            cout << "Character is invalid with this base or is an lowercase character" << endl;
            cout << "If character is a \'.\', two radix points are not allowed." << endl;
            continue;
        }

        int target_base;
        cout << "Input target base:" << endl;
        cin >> target_base;

        if (2 > target_base || target_base > 16)
        {
            cout << "Invalid base input (only from 2 to 16)" << endl;
            continue;
        }

        cout << input_base_x << " (base " << init_base << ") in" << endl;
        cout << "base " << target_base << " is " << convert_bases(input_base_x, init_base, target_base) << endl;
    }

    return 0;
}

// apologies for the O(n^2) complexity algorithm
// please inform if there is a faster solution here tho
char determine_validity(string inp, int base)
{

    bool char_is_valid;
    bool radix_point_detected = false;
    for (int i = 0; i < inp.length(); i++)
    {

        // cout << "evaluating character #" << i << ": " << inp[i] << endl;
        char_is_valid = false;
        if (inp[i] == '.')
        {
            if (radix_point_detected)
            {
                return '.';
            }

            radix_point_detected = true;
            continue;
        }

        for (int j = 0; j < base; j++)
        {

            // cout << "checking if character " << inp[i] << " matches " << valid_chars[j] << endl;
            if (inp[i] == valid_chars[j])
            {
                char_is_valid = true;
                break;
            } // valid character detected. exiting and performing a new loop

            // if character not detected: return invalid character
        }
        if (!char_is_valid)
        {
            return inp[i];
        }
    } // is this valid? idk sir
    return '\0';
}

string convert_bases(string init_number, int init_base, int target_base)
{

    int radix_point_loc = init_number.find('.');

    string whole_init_number = init_number.substr(0, radix_point_loc);
    string decimal_init_number;

    if (radix_point_loc != -1)
    {
        int char_limit = 64 - ceil_log_2[target_base];
        char_limit = (char_limit - (char_limit % ceil_log_2[init_base])) / ceil_log_2[init_base];
        decimal_init_number = init_number.substr(radix_point_loc + 1, char_limit);
    }
    else
    {
        decimal_init_number = "0";
    }

    // cout << "whole: " << whole_init_number << " decimal: " << decimal_init_number << endl;
    // cout << "whole len: " << whole_init_number.length() << " decimal len: " << decimal_init_number.length() << endl;
    unsigned long long whole_base_10;
    unsigned long long numerator_base_10;

    if (init_base != 10)
    {
        whole_base_10 = whole_to_base_10(whole_init_number, init_base);
        numerator_base_10 = whole_to_base_10(decimal_init_number, init_base);
    }
    else
    {
        whole_base_10 = stoi(whole_init_number);
        numerator_base_10 = stoi(decimal_init_number);
    }

    // cout << "whole part: " << whole_base_10;
    // cout << " decimal part: " << numerator_base_10 << "/" << power(init_base, decimal_init_number.length());
    // cout << endl;

    string whole_target_base = whole_base_10_to_another(whole_base_10, target_base);
    string decimal_target_base = fraction_to_another_base(numerator_base_10, power(init_base, decimal_init_number.length()), target_base);

    // cout << "whole part in new base:" << whole_target_base << endl;
    // cout << "decimal part in new base: " << decimal_target_base << endl;

    if (radix_point_loc == -1)
    {
        return whole_target_base;
    }
    else
    {
        return whole_target_base + "." + decimal_target_base;
    }
}

unsigned long long whole_to_base_10(string inp, int init_base)
{

    unsigned long long running_total = 0;
    int len = inp.length();
    for (int i = 0; i < len; i++)
    {
        for (int base = 0; base < init_base; base++)
        {
            if (inp[i] == valid_chars[base])
            {
                running_total += base * power(init_base, len - i - 1);
            }
        }
    }

    return running_total;
}

string whole_base_10_to_another(unsigned long long inp, int target_base)
{

    string output = "";
    int remainder;
    while (inp > target_base)
    {
        remainder = inp % target_base;
        output = valid_chars[remainder] + output;
        inp = (inp - remainder) / target_base;
    }

    return valid_chars[inp] + output;
}

string fraction_to_another_base(unsigned long long numerator, unsigned long long denominator, int target_base)
{

    string output = "";
    int whole_num;
    while (output.length() != 10 && numerator != 0)
    {
        numerator *= target_base;
        whole_num = (numerator - (numerator % denominator)) / denominator;
        output += valid_chars[whole_num];
        numerator = numerator % denominator;
    }

    return output;
}

unsigned long long power(int base, int exponent)
{
    unsigned long long result = 1;
    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }
    return result;
}
