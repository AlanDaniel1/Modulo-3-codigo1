#include <iostream>
#include <exception>
#include <stdexcept>

class ipAddress
{
private:
    std::string address1, address2;

    bool check(const std::string& addr) {

        int number = 0;
        int counter = 0;
        bool hasDigit = false;

        for (char n : addr)
        {
            if (n != '.') {

                if (n < '0' || n > '9') {
                    return false;
                }

                int digit = n - '0';

                number = (number * 10 + digit);

                if (number > 255)
                {
                    return false;
                }
                hasDigit = true;
            }
            else
            {
                if (!hasDigit) {
                    return false;
                }

                counter++;
                number = 0;
                hasDigit = false;

            }
        }
        return hasDigit && number <= 255 && counter == 3;

    }

public:

    ipAddress(const std::string& addr1, const std::string& addr2) : address1(addr1), address2(addr2)
    {
        if (!check(addr1)) { throw std::runtime_error("Invalid IP Header - Source IP Address is invalid."); }
        if (!check(addr2)) { throw std::runtime_error("Invalid IP Header - Source IP Address is invalid."); }
        std::cout << "Valid IP Header.\n";
    }



};

int main()
{
    std::string ip1, ip2;

    std::cin >> ip1 >> ip2;

    try {
        ipAddress ipAddr(ip1, ip2);
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << "\n";
    }
    return 0;
}