
#include <iostream>
#include <exception>

class DivideByZeroException
{
public:
    const char* what() const throw()
    {
        return "Your input is not valid, you can't divide by zero.";
    }
};

int main(void)
{
    int numerator, denominator;
    std::cout << "Enter numerator: ";
    std::cin >> numerator;
    std::cout << "Enter denominator: ";
    std::cin >> denominator;

    try {
        if (denominator == 0) {
            throw DivideByZeroException();
        }

        int result = numerator / denominator;
        std::cout << "Result: " << result << "\n";

        return 0;
    }
    catch (DivideByZeroException& e)
    {
        std::cout << e.what() << std::endl;
    }

}
