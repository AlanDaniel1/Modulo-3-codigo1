#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

class ipAddress
{
private:
    std::string address;

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

    ipAddress(const std::string& addr) : address(addr)
    {
        if (!check(addr)) { throw std::runtime_error("Exception - invalid IP number."); }
    }

    void printRange(int number)
    {
        if (!(number > 0 && (number & (number - 1)) == 0)) {
            throw std::runtime_error("Exception - invalid range.");
        }

        int a, b, c, d;
        char dot;
        std::istringstream ss(address);
        ss >> a >> dot >> b >> dot >> c >> dot >> d;

        for (int i = 1; i <= number; i++) {
            // Nota: Esto no maneja correctamente el desbordamiento (ej. 192.168.1.255 + 2)
            // pero sigue la lógica del laboratorio.
            std::cout << a << "." << b << "." << c << "." << (d + i) << "\n";
        }
        std::cout << "\n";
    }

};

int main()
{
    std::string ip;
    int subnet;

    std::cin >> ip >> subnet;

    try
    {
        ipAddress ipAddr(ip);
        ipAddr.printRange(subnet);
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << "\n";
    }

    return 0;
}