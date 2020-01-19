#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include"Complex.h"
#include"utils.h"
using namespace std;

#define DO_CLEAR_SCREEN system("cls")
#define DO_WAIT_BUTTON_DOWN system("pause>nul")

void menuStart(const string& h);
void menuMain(vector<Complex>& v, const string& h);
void menuShow(vector<Complex>& v, const string& h);
void menuAdd(vector<Complex>& v, const string& h);
void menuDelete(vector<Complex>& v, const string& h);
void menuSort(vector<Complex>& v, const string& h);
void menuOperation(vector<Complex>& v, const string& h);

// double + Complex
Complex operator+(double fir, Complex sec) {
	return Complex(fir + sec.getReal(), sec.getImaginaryMultiplier(), sec.getImaginaryUnit());
}

// double - Complex
Complex operator-(double fir, Complex sec) {
	return Complex(fir - sec.getReal(), -sec.getImaginaryMultiplier(), sec.getImaginaryUnit());
}

// double * Complex
Complex operator*(double fir, Complex sec) {
	return Complex(fir * sec.getReal(), fir * sec.getImaginaryMultiplier(), sec.getImaginaryUnit());
}

const string ARROW_TEXT = " -> ";
string in; // хранит пользовательский ввод
Random r = Random();

int main() {
	setlocale(LC_ALL, "ru");
	cout << "=== Complex numbers ===" << endl;
	menuStart("START");
}

void menuStart(const string& h) {
	vector<Complex> v = vector<Complex>(); // массив комплексных чисел

	while (true) {
		cout << h << "\n\n";
		cout << "Начать/Выйти (g/e)? ";
		in = getWord();
		switch (sci(in.c_str())) {
			case sci("g"):
				DO_CLEAR_SCREEN;
				menuMain(v, h + ARROW_TEXT + "MAIN");
				DO_CLEAR_SCREEN;
				v.clear();
				break;

			case sci("e"):
				DO_CLEAR_SCREEN;
				sayLog("Went out");
				return;

			default:
				sayErr("Неправильный ввод.");
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				continue;
		}
	}
}

void menuMain(vector<Complex>& v, const string& h) {
	while (true) {
		cout << h << "\n\n";
		cout << "Выбирете действие." << "\n\n";
		cout << "Показать массив - show" << endl
			<< "Добавить элемент(-ы) - add" << endl
			<< "Удалить элемент(-ы) - del" << endl
			<< "Сортировать - sort" << endl
			<< "Произвести операцию (+, -, *, /) - op" << endl
			<< "Назад - b" << endl;

		cout << ">> ";
		in = getWord();
		switch (sci(in.c_str())) {
			case sci("show"):
				DO_CLEAR_SCREEN;
				menuShow(v, h + ARROW_TEXT + "SHOW");
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				break;

			case sci("add"):
				DO_CLEAR_SCREEN;
				menuAdd(v, h + ARROW_TEXT + "ADD");
				//DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				break;

			case sci("del"):
				DO_CLEAR_SCREEN;
				menuDelete(v, h + ARROW_TEXT + "DELETE");
				DO_CLEAR_SCREEN;
				break;

			case sci("sort"):
				DO_CLEAR_SCREEN;
				menuSort(v, h + ARROW_TEXT + "DELETE");
				DO_CLEAR_SCREEN;
				break;

			case sci("op"):
				DO_CLEAR_SCREEN;
				menuOperation(v, h + ARROW_TEXT + "OPERATION");
				DO_CLEAR_SCREEN;
				break;

			case sci("b"):
				DO_CLEAR_SCREEN;
				return;

			default:
				sayErr("Неправильный ввод.");
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				continue;
		}
	}
}

void menuShow(vector<Complex>& v, const string& h) {
	cout << h << "\n\n";

	if (v.empty()) {
		cout << "Массив пуст." << endl;
		return;
	}

	for (int i = 0; i < v.size(); i++) {
		cout << "#" << i + 1 << ": ";
		v[i].print();
	}
}

void menuAdd(vector<Complex>& v, const string& h) {
	bool isGoingOn;
	string str_real, str_imaginaryMultiplier;
	int index;
	int count;
	int originalSize = v.size();

	while (true) {
		isGoingOn = true;

		cout << h << "\n\n"
			<< "Выбирете способ ввода: " << "\n\n"
			<< "самостоятельно - 's'" << endl
			<< "рандом - 'r'" << endl
			<< "назад - 'b'" << "\n\n";
		cout << ">> ";


		switch (sci(getWord().c_str())) {
			case sci("s"):
				cout << "Для остановки введите 'stop'" << "\n\n";

				index = v.size() + 1;
				while (true) {
					cout << "#" << index << ":\n";
					cout << "real: ";
					str_real = getWord();
					if (str_real == "stop") return;
					else if (str_imaginaryMultiplier == "stop") return;
					cout << "imaginary multiplier: ";
					str_imaginaryMultiplier = getWord();
					if (isNumber(str_real) && isNumber(str_imaginaryMultiplier)) {
						v.push_back(Complex(stod(str_real), stod(str_imaginaryMultiplier)));
						index++;
					}
					else {
						sayErr("Неправильный ввод.");
						continue;
					}
				}
				break;

			case sci("r"):
				while (true) {
					cout << "Введите количество: ";
					in = getWord();
					if (isNumber(in) && stoi(in) >= 0) {
						count = stoi(in);
						for (int i = 0; i < count; i++) {
							v.push_back(Complex(random(-10, 10), random(-10, 10)));
							cout << "#" << originalSize + i + 1 << ": ";
							v[i + originalSize].print();
						}
						DO_WAIT_BUTTON_DOWN;
						return;
					}
					else {
						sayErr("Неправильный ввод.");
						continue;
					}
				}
				break;

			case sci("b"):
				return;

			default:
				sayErr("Неправильный ввод.");
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				continue;
		}
	}
}

void menuDelete(vector<Complex>& v, const string& h) {
	int indexToDelete;

	cout << h << "\n\n";
	if (v.empty()) {
		cout << "Нечего удалать." << endl;
		DO_WAIT_BUTTON_DOWN;
		return;
	}
	while (true) {
		DO_CLEAR_SCREEN;
		cout << h << "\n\n";
		cout << "Введите номер элемента или 'stop': ";
		in = getWord();
		if (isNumber(in) && stoi(in) - 1 >= 0 and stoi(in) - 1 < v.size()) {
			indexToDelete = stoi(in) - 1;
			cout << "Элемент под номером " << indexToDelete + 1 << " (";
			v[indexToDelete].print(false);
			cout << ") удален" << endl;
			v.erase(v.begin() + indexToDelete);
			DO_WAIT_BUTTON_DOWN;
			DO_CLEAR_SCREEN;
			continue;
		}
		else if (isNumber(in)) {
			cout << "Нету элемента под таким номером" << endl;
			DO_WAIT_BUTTON_DOWN;
			DO_CLEAR_SCREEN;
			continue;
		}
		else switch (sci(in.c_str())) {
			case sci("stop"):
				return;
			default:
				sayErr("Неправильный ввод.");
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				continue;
		}
	}
}

// меню сортировки
void menuSort(vector<Complex>& v, const string& h) {
	string crit;
	while (true) {
		cout << h << "\n\n";
		cout << "Выбирете критерий для сотрировки." << "\n\n";
		cout << "модуль к. ч. - 'm'" << endl
			<< "действительная часть - 'r'" << endl
			<< "комплексная часть - 'c'" << endl
			<< "назад - 'b'" << endl;
		cout << ">> ";

		crit = getWord();
		if (crit == "b") {
			return;
		}
		if (crit != "m" && crit != "r" && crit != "c") {
			sayErr("Неправильный ввод.");
			DO_WAIT_BUTTON_DOWN;
			DO_CLEAR_SCREEN;
			continue;
		}
		else {
			cout << "По убыванию? (y/n): ";
			in = getWord();
			switch (sci(in.c_str())) {
				// UP
				case sci("y"):
					if (crit == "m") {
						sort(v.begin(), v.end(),
							 [](Complex& a, Complex& b) {
							return a.getModulus() > b.getModulus();
						});
					}
					else if (crit == "r") {
						sort(v.begin(), v.end(),
							 [](Complex& a, Complex& b) {
							return a.getReal() > b.getReal();
						});
					}
					else if (crit == "c") {
						sort(v.begin(), v.end(),
							 [](Complex& a, Complex& b) {
							return a.getImaginaryMultiplier() > b.getImaginaryMultiplier();
						});
					}
					if (v.empty()) {
						cout << "Массив пуст." << endl;
						return;
					}

					// print array
					for (int i = 0; i < v.size(); i++) {
						cout << "#" << i + 1 << ": ";
						v[i].print();
					}

					DO_WAIT_BUTTON_DOWN;
					DO_CLEAR_SCREEN;
					return;

				// DOWN
				case sci("n"):
					if (crit == "m") {
						sort(v.begin(), v.end(),
							 [](Complex& a, Complex& b) {
							return a.getModulus() < b.getModulus();
						});
					}
					else if (crit == "r") {
						sort(v.begin(), v.end(),
							 [](Complex& a, Complex& b) {
							return a.getReal() < b.getReal();
						});
					}
					else if (crit == "c") {
						sort(v.begin(), v.end(),
							 [](Complex& a, Complex& b) {
							return a.getImaginaryMultiplier() < b.getImaginaryMultiplier();
						});
					}
					if (v.empty()) {
						cout << "Массив пуст." << endl;
						return;
					}

					// print array
					for (int i = 0; i < v.size(); i++) {
						cout << "#" << i + 1 << ": ";
						v[i].print();
					}
					DO_WAIT_BUTTON_DOWN;
					DO_CLEAR_SCREEN;
					return;

				default:
					sayErr("Неправильный ввод.");
					DO_WAIT_BUTTON_DOWN;
					DO_CLEAR_SCREEN;
					continue;
			}
		}
	}
}

// меню с операциями (+,-,*,/)
void menuOperation(vector<Complex>& v, const string& h) {
	string firNum, // первый операнд
		secNum; // второй операнд 
	while (true) {
		cout << h << "\n\n"
			<< "Выбирете шаблон выражения: " << "\n\n"
			<< "Complex + Complex - 1" << endl
			<< "Complex + double - 2" << endl
			<< "double + Complex - 3" << endl
			<< "Complex - Complex - 4" << endl
			<< "Complex - double - 5" << endl
			<< "double - Complex - 6" << endl
			<< "Complex * Complex - 7" << endl
			<< "Complex * double - 8" << endl
			<< "double * Complex - 9" << endl
			<< "Complex / Complex - 10" << endl
			<< "Complex / double - 11" << endl
			<< "назад - b" << "\n\n"
			<< ">> ";

		in = getWord();

		switch (sci(in.c_str())) {
			// c+c
			case sci("1"):
				if (v.size() < 2) {
					cout << "массив должен содержать как минимум 2 элемента!";
					continue;
				}
				cout << "c+c" << endl
					<< "номер 1-го числа: ";
				firNum = getWord();
				cout << "номер 2-го числа: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(firNum) > 0 && stoi(firNum) <= v.size()
					&& stoi(secNum) > 0 && stoi(secNum) <= v.size()) {
					cout << endl;
					v[stoi(firNum) - 1].print();
					cout << "+" << endl;
					v[stoi(secNum) - 1].print();
					cout << "=" << endl;
					(v[stoi(firNum) - 1] + v[stoi(secNum) - 1]).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// c+d
			case sci("2"):
				if (v.size() < 1) {
					cout << "массив должен содержать как минимум 1 элемент!";
					continue;
				}
				cout << "c+d" << endl
					<< "номер 1-го числа: ";
				firNum = getWord();
				cout << "2-е число: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(firNum) > 0 && stoi(firNum) <= v.size()) {
					cout << endl;
					v[stoi(firNum) - 1].print();
					cout << "+" << endl
						<< stod(secNum) << endl
						<< "=" << endl;
					(v[stoi(firNum) - 1] + stod(secNum)).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// d+c
			case sci("3"):
				if (v.size() < 1) {
					cout << "массив должен содержать как минимум 1 элемент!";
					continue;
				}
				cout << "d+C" << endl
					<< "1-е число: ";
				firNum = getWord();
				cout << "номер 2-го числа: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(secNum) > 0 && stoi(secNum) <= v.size()) {
					cout << endl
						<< stod(firNum) << endl
						<< "+" << endl;
					v[stoi(secNum) - 1].print();
					cout << "=" << endl;
					(stod(firNum) + v[stoi(secNum) - 1]).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// c-c
			case sci("4"):
				if (v.size() < 2) {
					cout << "Массив должен содержать как минимум 2 элемента!";
					continue;
				}
				cout << "c-c" << endl
					<< "Номер 1-го числа: ";
				firNum = getWord();
				cout << "Номер 2-го числа: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(firNum) > 0 && stoi(firNum) <= v.size()
					&& stoi(secNum) > 0 && stoi(secNum) <= v.size()) {
					cout << endl;
					v[stoi(firNum) - 1].print();
					cout << "-" << endl;
					v[stoi(secNum) - 1].print();
					cout << "=" << endl;
					(v[stoi(firNum) - 1] - v[stoi(secNum) - 1]).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// c-d
			case sci("5"):
				if (v.size() < 1) {
					cout << "Массив должен содержать как минимум 1 элемент!";
					continue;
				}
				cout << "c-d" << endl
					<< "Номер 1-го числа: ";
				firNum = getWord();
				cout << "2-е число: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(firNum) > 0 && stoi(firNum) <= v.size()) {
					cout << endl;
					v[stoi(firNum) - 1].print();
					cout << "-" << endl
						<< stod(secNum) << endl
						<< "=" << endl;
					(v[stoi(firNum) - 1] - stod(secNum)).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// d-c
			case sci("6"):
				if (v.size() < 1) {
					cout << "Массив должен содержать как минимум 1 элемент!";
					continue;
				}
				cout << "d-C" << endl;
				cout << "1-е число: ";
				firNum = getWord();
				cout << "Номер 2-го числа: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(secNum) > 0 && stoi(secNum) <= v.size()) {
					cout << endl
					<< stod(firNum) << endl
					<< "-" << endl;
					v[stoi(secNum) - 1].print();
					cout << "=" << endl;
					(stod(firNum) - v[stoi(secNum) - 1]).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// c*c
			case sci("7"):
				if (v.size() < 2) {
					cout << "Массив должен содержать как минимум 2 элемента!";
					continue;
				}
				cout << "c*c" << endl;
				cout << "номер 1-го числа: ";
				firNum = getWord();
				cout << "номер 2-го числа: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(firNum) > 0 && stoi(firNum) <= v.size()
					&& stoi(secNum) > 0 && stoi(secNum) <= v.size()) {
					cout << endl;
					v[stoi(firNum) - 1].print();
					cout << "*" << endl;
					v[stoi(secNum) - 1].print();
					cout << "=" << endl;
					(v[stoi(firNum) - 1] * v[stoi(secNum) - 1]).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// c*d
			case sci("8"):
				if (v.size() < 1) {
					cout << "Массив должен содержать как минимум 1 элемент!";
					continue;
				}
				cout << "c*d" << endl;
				cout << "номер 1-го числа: ";
				firNum = getWord();
				cout << "2-е число: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(firNum) > 0 && stoi(firNum) <= v.size()) {
					cout << endl;
					v[stoi(firNum) - 1].print();
					cout << "*" << endl;
					cout << stod(secNum) << endl;
					cout << "=" << endl;
					(v[stoi(firNum) - 1] * stod(secNum)).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// d*c
			case sci("9"):
				if (v.size() < 1) {
					cout << "Массив должен содержать как минимум 1 элемент!";
					continue;
				}
				cout << "d*C" << endl;
				cout << "1-е число: ";
				firNum = getWord();
				cout << "номер 2-го числа: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(secNum) > 0 && stoi(secNum) <= v.size()) {
					cout << endl;
					cout << stod(firNum) << endl;
					cout << "*" << endl;
					v[stoi(secNum) - 1].print();
					cout << "=" << endl;
					(stod(firNum) * v[stoi(secNum) - 1]).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// c/c
			case sci("10"):
				if (v.size() < 2) {
					cout << "Массив должен содержать как минимум 2 элемента!";
					continue;
				}
				cout << "c/c" << endl;
				cout << "номер 1-го числа: ";
				firNum = getWord();
				cout << "номер 2-го числа: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(firNum) > 0 && stoi(firNum) <= v.size()
					&& stoi(secNum) > 0 && stoi(secNum) <= v.size()) {
					cout << endl;
					v[stoi(firNum) - 1].print();
					cout << "/" << endl;
					v[stoi(secNum) - 1].print();
					cout << "=" << endl;
					(v[stoi(firNum) - 1] / v[stoi(secNum) - 1]).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			// c/d
			case sci("11"):
				if (v.size() < 1) {
					cout << "Массив должен содержать как минимум 1 элемент!";
					continue;
				}
				cout << "c/d" << endl;
				cout << "номер 1-го числа: ";
				firNum = getWord();
				cout << "2-е число: ";
				secNum = getWord();
				if (isNumber(firNum) && isNumber(secNum)
					&& stoi(firNum) > 0 && stoi(firNum) <= v.size()) {
					cout << endl;
					v[stoi(firNum) - 1].print();
					cout << "/" << endl
						<< stod(secNum) << endl
						<< "=" << endl;
					(v[stoi(firNum) - 1] / stod(secNum)).print();
					cout << endl;
				}
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				return;

			case sci("b"):
				return;
		}
	}



}