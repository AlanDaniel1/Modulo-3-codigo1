#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>

class MatricesSizeException :public std::runtime_error
{
public:
	MatricesSizeException(const char* message) : std::runtime_error(message) {}
};

class Matrix
{
private:
	int rows, columns;
	std::vector<std::vector<float>> Vmatrix;

public:

	Matrix(int r, int c) : rows(r), columns(c), Vmatrix(r, std::vector<float>(c, 0)) {}

	void addValue(int value)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				Vmatrix[i][j] += value;
			}
		}
	}

	void addMatrix(Matrix& Omatrix)
	{
		if (Omatrix.rows != rows || Omatrix.columns != columns) {
			throw MatricesSizeException("Matrices sizes do not match for addition.");
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				Vmatrix[i][j] += Omatrix.Vmatrix[i][j];
			}
		}
	}

	void print()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				std::cout << Vmatrix[i][j] << " ";
			}

			std::cout << "\n";
		}
	}
};

void tryA(Matrix& m1, Matrix& m2)
{
	try
	{
		m1.addMatrix(m2);
		m1.print();
	}
	catch (MatricesSizeException& ex)
	{
		std::cout << ex.what() << "\n";
	}
}


int main()
{
	int m1r, m1c, m2r, m2c, m3r, m3c;

	std::cin >> m1r >> m1c;
	std::cin >> m2r >> m2c;
	std::cin >> m3r >> m3c;

	Matrix m1(m1r, m1c);
	Matrix m2(m2r, m2c);
	Matrix m3(m3r, m3c);

	tryA(m1, m2);
	tryA(m1, m3);
	tryA(m2, m3);

	return 0;
}