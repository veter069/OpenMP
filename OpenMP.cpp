#include"stdafx.h"
#include<stdio.h>
#include<math.h>
#include<omp.h>
#include<iostream>


int main()
{
	const int N = 1e8;
	const double h = 0.5;

	double pi;
	double t_1, t_2; //временныеинтервалы

	double sum = 0.0;
	int a;
	std::cout << "Enter number of process: ";
	std::cin >> a;

	t_1 = omp_get_wtime(); //начальный замер времени
	int k8 = 0;
#pragma omp parallel for reduction(+: sum) num_threads(a) // онструкци€ дл€ создани€ потоков, число потоков - а
	for (int k = 0; k < N; ++k) // ÷икл будет выполн€тс€ с использованием большого числа нитей, результаты получит главна€ нить дл€ суммировани€
	{
		sum += 1.0 / pow(16.0, k)*(
			8.0 / (k8 + 2.0) + 
			4.0 / (k8 + 3.0) +
			4.0 / (k8 + 4.0) - 
			1.0 / (k8 + 7.0));
	}
	pi = sum * h;
	t_2 = omp_get_wtime(); //замер€ем врем€ после завершени€ работы всех нитей


	printf("Max process: %d\n", omp_get_max_threads()); // ¬озвращает число потоков, доступных дл€ распаралеливани€
	printf("time: %f\n", t_2 - t_1); // ¬рем€ выполнени€ 
	printf("pi ~ %.10f\n", pi);

	system("pause");
	return 0;
}
