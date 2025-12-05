
#include <iostream>

const bool divZero = true;

int main()
{
	int a = 8, b = 0, c = 0;
	std::cout << "Enter a divisor: \n";
	std::cin >> b;

	try {

		if (b == 0) {
			throw divZero;
		}
		c = a / b;
	}
	catch (bool isZero)
	{
		std::cout << "Your input is not valid, you can't divide by zero. \n";

	}

	std::cout << c << "\n";

	return 0;
}