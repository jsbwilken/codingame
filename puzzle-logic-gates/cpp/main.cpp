//
// Created by wilke on 20.07.2023.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

bool to_boolean(char c)
{
    return c == '-';
}

int main()
{
    int n;
    std::cin >> n; std::cin.ignore();
    int m;
    std::cin >> m; std::cin.ignore();

    std::map<std::string, std::string> signals;
    for (int i = 0; i < n; i++) {
        std::string input_name;
        std::string input_signal;
        std::cin >> input_name >> input_signal; std::cin.ignore();

        signals.insert({input_name, input_signal});
    }
    for (int i = 0; i < m; i++) {
        std::string output_name;
        std::string type;
        std::string input_name_1;
        std::string input_name_2;
        std::cin >> output_name >> type >> input_name_1 >> input_name_2; std::cin.ignore();

        auto input1 = signals.at(input_name_1);
        auto input2 = signals.at(input_name_2);

        std::vector<bool> boolean_signal_1(input1.length());
        std::vector<bool> boolean_signal_2(input2.length());

        std::transform(input1.begin(), input1.end(), boolean_signal_1.begin(), to_boolean);
        std::transform(input2.begin(), input2.end(), boolean_signal_2.begin(), to_boolean);

        if(type == std::string("AND"))
        {
            std::transform(boolean_signal_1.begin(), boolean_signal_1.end(), boolean_signal_2.begin(), boolean_signal_1.begin(), std::logical_and<>());
        }
        else if(type == std::string("OR"))
        {
            std::transform(boolean_signal_1.begin(), boolean_signal_1.end(), boolean_signal_2.begin(), boolean_signal_1.begin(), std::logical_or<>());
        }
        else if(type == std::string("XOR"))
        {
            std::transform(boolean_signal_1.begin(), boolean_signal_1.end(), boolean_signal_2.begin(), boolean_signal_1.begin(), std::not_equal_to<>());
        }
        else if(type == std::string("NAND"))
        {
            std::transform(boolean_signal_1.begin(), boolean_signal_1.end(), boolean_signal_2.begin(), boolean_signal_1.begin(), std::logical_and<>());
            std::transform(boolean_signal_1.begin(), boolean_signal_1.end(), boolean_signal_1.begin(), std::logical_not<>());
        }
        else if(type == std::string("NOR"))
        {
            std::transform(boolean_signal_1.begin(), boolean_signal_1.end(), boolean_signal_2.begin(), boolean_signal_1.begin(), std::logical_or<>());
            std::transform(boolean_signal_1.begin(), boolean_signal_1.end(), boolean_signal_1.begin(), std::logical_not<>());
        }
        else if(type == std::string("NXOR"))
        {
            std::transform(boolean_signal_1.begin(), boolean_signal_1.end(), boolean_signal_2.begin(), boolean_signal_1.begin(), std::equal_to<>());
        }

        std::string output;
        std::for_each(boolean_signal_1.begin(), boolean_signal_1.end(), [&output](bool b) -> void
        {
            if(b)
            {
                output.push_back('-');
            }
            else
            {
                output.push_back('_');
            }
        });

        std::cout << output_name << " " << output << std::endl;
    }

}