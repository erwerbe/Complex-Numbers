/*
	класс для комплексного числа
*/

/*
	TEMPLATE:
	[число] + [число] * [i]
*/

#pragma once
#include<iostream>
#include<string>
using namespace std;

class Complex {
private:
	double real; // действительная часть
	double imaginaryMultiplier; // множитель мнимой части
	bool imaginaryUnit; // флаг на наличие числа i (мнимая единица)

public:
	Complex() {
		this->real = 0;
		this->imaginaryMultiplier = 0;
		this->imaginaryUnit = false;
	}

	Complex(double real, double imagMul, bool imaginaryUnit = true) {
		this->setReal(real);
		this->setImaginaryMultiplier(imagMul);
		this->setImaginaryUnit(imaginaryUnit);
	}

	Complex copy(const Complex& obj) {
		Complex ret = Complex(obj.real, obj.imaginaryMultiplier, obj.imaginaryUnit);

		/*this->setReal(obj.real);
		this->setImaginaryMultiplier(obj.imaginaryMultiplier);
		this->setImaginaryUnit(obj.imaginaryUnit);*/

		return ret;
	}

	/* GETTERS/SETTERS */

	double getReal() {
		return this->real;
	}

	void setReal(double number) {
		this->real = number;
	}

	double getImaginaryMultiplier() {
		return this->imaginaryMultiplier;
	}

	void setImaginaryMultiplier(double number) {
		this->imaginaryMultiplier = number;
		// если множетель мнимой части раен 0, то число i можно убрать
		if (!number) {
			this->imaginaryUnit = false;
		}
	}

	bool getImaginaryUnit() {
		return this->imaginaryUnit;
	}

	void setImaginaryUnit(bool flag) {
		if (this->imaginaryMultiplier == 0) {
			return;
		}
		this->imaginaryUnit = flag;
		// если i отсутствует, то его множитель мнимой части не имеет смысла
		if (!flag) {
			this->imaginaryMultiplier = 0;
		}
	}

	/* GETTERS/SETTERS END */

	void print(bool needNewLine = true) {
		cout << this->getReal() << " ";
		// если множитель мнимой части равен 0 ИЛИ выражение не содержит число i, то мнимую часть можно не писать
		if (this->imaginaryMultiplier != 0 && this->imaginaryUnit) {
			if (this->imaginaryMultiplier > 0) {
				cout << "+ ";
			}
			cout << this->getImaginary();
		}
		if (needNewLine) {
			cout << endl;
		}
	}

	// возвращает действительную часть
	string string_getReal() {
		return to_string(this->real);
	}

	// возвращает мнимую часть
	string getImaginary() {
		if (this->imaginaryMultiplier == 0 || !this->imaginaryUnit) {
			return "";
		}
		return to_string(this->imaginaryMultiplier) + (this->imaginaryUnit ? " * i" : "");
	}

	// возвращает модуль комплексного числа
	double getModulus() {
		return sqrt(this->real * this->real + this->imaginaryMultiplier * this->imaginaryMultiplier);
	}

	/* OPERATORS */

	// Complex + Complex
	Complex operator+(Complex op) {
		Complex ret = Complex(
			this->real + op.real,
			(this->imaginaryUnit ? this->imaginaryMultiplier : 0) + (op.imaginaryUnit ? op.imaginaryMultiplier : 0),
			this->imaginaryUnit || op.imaginaryUnit
		);

		return ret;
	}

	// Complex + double 
	Complex operator+(double op) {
		return Complex(this->real + op, this->imaginaryMultiplier, this->imaginaryUnit);
	}

	// Complex - Complex 
	Complex operator-(Complex op) {
		Complex ret = Complex(
			this->real - op.real,
			(this->imaginaryUnit ? this->imaginaryMultiplier : 0) - (op.imaginaryUnit ? op.imaginaryMultiplier : 0),
			this->imaginaryUnit || op.imaginaryUnit
		);

		return ret;
	}

	// Complex - double
	Complex operator-(double number) {
		return Complex(
			this->real - number,
			this->imaginaryMultiplier,
			this->imaginaryUnit
		);
	}

	// Complex * Complex
	Complex operator*(Complex op) {
		// (a+bi)*(a'+b'i) = (aa'-bb') + (ab'+ba')i
		/*
			HOW IT SHOULD WORK:

			ret.real = (aa'- bb')
			ret.imaginaryMultiplier = (ab'+ba')
			ret.imaginaryUnit = this->imaginaryUnit || op.imaginaryUnit

		*/

		return Complex(
			this->real * op.real - this->imaginaryMultiplier * op.imaginaryMultiplier,
			this->real * op.imaginaryMultiplier + this->imaginaryMultiplier * op.real,
			this->imaginaryUnit || op.imaginaryUnit
		);
	}

	// Complex * double
	Complex operator*(double op) {
		return Complex(
			this->real * op,
			this->imaginaryMultiplier * op,
			this->imaginaryUnit
		);
	}

	// Complex / Complex
	Complex operator/(Complex op) {
		// (a+bi)/(a'+b'i) = (aa'+bb')/(a'^2+b'^2) + (a'b-b'a)/(a'^2+b'^2) * i
		/*
			HOW:

			ret.real = (aa'+bb')/(a'^2+b'^2)
			ret.imaginaryMultiplier = (a'b-b'a)/(a'^2+b'^2)
			ret.imaginaryUnit = this->imaginaryUnit || op.imaginaryUnit
		*/

		return Complex(
			(this->real * op.real + this->imaginaryMultiplier * op.imaginaryMultiplier) / (op.real * op.real + op.imaginaryMultiplier * op.imaginaryMultiplier),
			(op.real * this->imaginaryMultiplier - op.imaginaryMultiplier * this->real) / (op.real * op.real + op.imaginaryMultiplier * op.imaginaryMultiplier),
			true
		);
	}

	// Complex / double
	Complex operator/(double op) {
		return Complex(
			this->real / op,
			this->imaginaryMultiplier / op,
			this->imaginaryMultiplier
		);
	}

	/* OPERATORS END */
};

