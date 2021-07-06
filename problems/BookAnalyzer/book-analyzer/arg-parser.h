#ifndef INPUT_PARSER
#define INPUT_PARSER

#include <boost/program_options.hpp>
#include <math.h>
#include <iostream>
#include <exception>

struct ArgParser
{
    /* Validates program input - checks for target-size existence and correctness  */
    bool isInputValid(int argc, char **argv)
    {
        try
        {
            namespace po = boost::program_options;
            po::options_description inputDescription("Allowed options");
            inputDescription.add_options()
                ("help", "produce help message")
                ("target-size", po::value<int>(), "the total number of shares.");

            po::variables_map valuesMap;
            po::store(po::parse_command_line(argc, argv, inputDescription), valuesMap);
            po::notify(valuesMap);
 
            if (valuesMap.count("help"))
            {
                std::cout << inputDescription << "\n";
                return false;
            }

            if (valuesMap.count("target-size"))
            {
                targetSize = valuesMap["target-size"].as<int>();
                if (targetSize < 0)
                {
                    std::cout << "target-size cannot be negative number.\nType --help for more information.\n";
                    return false;
                }
                return true;
            }
            else
            {
                std::cout << "target-size was not set.\nType --help for more information.\n";
            }
        }
        catch (std::exception &e)
        {
            std::cerr <<"error: " << e.what() << ".\nType --help for more information.\n";
        }
        catch (...)
        {
            std::cerr << "Exception of unknown type!.\nType --help for more information.\n";
        }

        return false;
    };

    void setTargetSize(const int& inputValue) noexcept { targetSize = inputValue; };
    int getTargetSize() const noexcept  { return targetSize; };
    
private:
    int targetSize = 0;

};

#endif //INPUT_PARSER