// ClassWork_ZNK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/// <summary>
/// Функция main. В нём будут выполняться основные задачи.
/// На 31.10.2024:
/// 1) Фибоначчи
/// 2) НОД(x,y)
/// 3) Простое число
/// 4) K-е простое число
/// 5) e (вычисление)
/// </summary>
/// <returns></returns>

constexpr int fibonacci(int n) {
    return n <= 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

constexpr int nod(int x, int y) {
    return x == 0 ? y : x > y ? nod(x%y, y) : nod(y%x, x);
}


constexpr bool isPrime(int x, int y = 2) {
    return x == 1 ? false : x / y < 2 ? true : x % y == 0 ? false : isPrime(x, ++y);
}

constexpr int kPrime(int k, int x = 2) {
    return k == 1 ? x : isPrime(++x) ? kPrime(--k, x) : kPrime(k, x);
}

/// <summary>
/// constexpr функция для приближённого вычисления e.
/// Идея: если iter_num <= 0 - 0, так как число итераций меньше 0,
/// иначе если iter_num == 1, то e_appr + 1, где e_appr рекуррентно вычисляется,
/// иначе если iter_num == 2, то e_appr + 2, это связано с тем, что в разложении Тейлора для e в
/// точке 1 первые два слагаемых - 1, иначе вычисляем факториал fac*=fac + 1 и e_appr += 1./fac.
/// Отсюда также следует, что суммирование начинается с 1/(2!), вплоть до 1/(iter_num!), а затем добавляются 2 единицы 
/// </summary>
/// <param name="iter_num">Число итераций</param>
/// <param name="fac">Факториал</param>
/// <param name="e_appr">Приближённое значение e</param>
/// <returns>Приближённое значение e</returns>
constexpr double eIter(int iter_num, int fac = 1, double e_appr = 0) {
    return iter_num <= 0 ? 0 : iter_num == 1 ? e_appr + 1 : iter_num == 2 ? eIter(--iter_num, fac, e_appr + 1) : eIter(--iter_num, fac *= fac + 1, e_appr + 1. / fac);
}

int main()
{
    int test1 = fibonacci(10);
    std::cout << "Fibonacci: " << test1 << std::endl;

    int x = 12;
    int y = 4;
    std::cout << "NOD: " << nod(x, y) << std::endl;
    std::cout << nod(1, 10) << " " << nod(5, 15) << " " << nod(6, 36) << " " << nod(18, 30) << std::endl;

    std::cout << isPrime(1) << " " << isPrime(3) << " " << isPrime(4) << " " << isPrime(5) << " " << isPrime(10) << " " << isPrime(11) << " " << isPrime(17) << " " << isPrime(24) << " " << isPrime(91) << " " << isPrime(101) << std::endl;

    for (int i = 1; i < 10; ++i) {
        std::cout << kPrime(i) << " ";
    }
    std::cout << std::endl;
    std::cout.precision(12);
    for (int i = 1; i < 10; ++i) {
        std::cout << eIter(i) << " ";
    }
    std::cout << std::endl;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
