#include <iostream>
#include <stdexcept>

const bool DivideByZero = true;

float internaldiv(float arg1, float arg2)
{
	if (0 == arg2)
		throw DivideByZero;
	return arg1 / arg2;
}


int main()
{
	float r, a, b;
	while (std::cin >> a) {
		std::cin >> b;
		try
		{
			r = internaldiv(a, b);
			std::cout << r << "\n";
			return 0;

		}
		catch (bool exe)
		{
			std::cout << "Are you kidding me?" << "\n";
			std::cout << "Your input is not valid, you can't divide by zero.";

			return 0;
		}


	}

}