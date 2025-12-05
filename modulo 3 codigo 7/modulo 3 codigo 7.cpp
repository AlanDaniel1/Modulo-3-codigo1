#include <iostream>
#include <stdexcept>

class Exeption : public std::runtime_error
{
public:
	Exeption(const char* message) : runtime_error(message) {}
};

float square_area(float side)
{
	if (side < 0)
	{
		throw Exeption("Your input is not valid. The area can't be negative.");
	}
	return side * side;
}

float rectangle_area(float side1, float side2)
{
	if (side1 < 0 || side2 < 0)
	{
		throw Exeption("Your input is not valid.The area can't be negative.");
	}
	return side1 * side2;
}


int main()
{
	float a, b, r;
	std::cin >> a;
	std::cin >> b;
	try
	{
		float rsquare = square_area(a);
		float rrectangle = rectangle_area(a, b);
		std::cout << rsquare << "\n" << rrectangle << "\n";
	}
	catch (Exeption msg)
	{
		std::cout << msg.what() << "\n";
	}
	return 0;
}