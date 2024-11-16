// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите размеры матриц\n";
	int size;
	cin >> size;
	cout << "Введите матрицу A\n";
	TDynamicMatrix<int> a(size);
	cin >> a;
	cout << '\n';
	cout << "Введите матрицу B\n";
	TDynamicMatrix<int> b(size);
	cin >> b;
	cout << '\n';
	string s = "0";
	do {
		cout << "e - выйти, m - перемножить A и B, p - сложить A и B, d - вычесть из A B, ta - умножить A на скаляр, tb - умножить B на скаляр va - умножить A на вектор, vb - умножить B на вектор\n";
		cin >> s;
		if (s == "m")
			cout << a * b << '\n';
		else if (s == "p")
			cout << a + b << '\n';
		else if (s == "d")
			cout << a - b << '\n';
		else if (s == "ta") {
			int t;
			cout << "значение скаляра: \n";
			cin >> t;
			cout << a * t << '\n';
		}
		else if (s == "tb") {
			int t;
			cout << "значение скаляра: \n";
			cin >> t;
			cout << b * t << '\n';
		}
		else if (s == "va") {
			cout << "Введите элементы вектора:\n";
			TDynamicVector<int> v(size);
			cin >> v;
			cout << a * v << '\n';
		}
		else if (s == "vb") {
			cout << "Введите элементы вектора:\n";
			TDynamicVector<int> v(size);
			cin >> v;
			cout << b * v << '\n';
		}
		else if (s != "e")
			cout << "Некоректный ввод\n";
	} while (s != "e");
}

//---------------------------------------------------------------------------
