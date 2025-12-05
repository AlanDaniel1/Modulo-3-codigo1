#include <iostream>
#include <exception>
#include <stdexcept>

class LimitExceededException : public std::runtime_error
{
public:
	LimitExceededException(const char* message) : std::runtime_error(message) {}
};

class Value
{
private:
	int value, min, max;

public:

	Value(int v, int mi, int ma) : value(v), min(mi), max(ma) {}

	void addValue(int v)
	{
		if (value + v > max) {
			throw LimitExceededException("Value could exceed limit.");
		}
		value += v;
	}

	void subtractValue(int v)
	{
		if (value - v < min)
		{
			throw LimitExceededException("Value could exceed limit.");
		}
		value -= v;
	}

	void print()
	{
		std::cout << value << "\n";
	}

};

void tryVA(Value& n1)
{
	int value;
	std::cin >> value;

	try
	{
		n1.addValue(value);
	}
	catch (LimitExceededException& e)
	{
		std::cout << e.what() << "\n";
	}

}
void tryVS(Value& n1)
{
	int value;
	std::cin >> value;

	try
	{
		n1.subtractValue(value);
	}
	catch (LimitExceededException& e)
	{
		std::cout << e.what() << "\n";
	}

}

int main()
{
	int v1, v2, min1, max1, min2, max2;

	std::cin >> v1 >> min1 >> max1;
	std::cin >> v2 >> min2 >> max2;

	Value number1(v1, min1, max1);
	Value number2(v2, min2, max2);

	tryVA(number1);
	tryVA(number2);
	tryVS(number1);

	number1.print();
	number2.print();


	return 0;

}