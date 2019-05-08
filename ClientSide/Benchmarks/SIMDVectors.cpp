/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>

 #include "omp.h"
 #include "GenerateRandomArray.hpp"
 #include "Vectors/Vector4.hpp"
 
void SIMDVectorsAdditionBenchmark()
{
	const std::size_t ARR_SIZE = 100000;
	const std::size_t TIMES = 100000;
	std::unique_ptr<Math::Vector4f>	arr1(new Math::Vector4f[ARR_SIZE]),
		arr2(new Math::Vector4f[ARR_SIZE]),
		arr3(new Math::Vector4f[ARR_SIZE]);
	double total_gen_time = 0;
	const double start = omp_get_wtime();
	for (std::size_t i = 0; i < TIMES; i++)
	{
		if (i % 100 == 0)
		{
			const double gen_start = omp_get_wtime();
			fillArray<Math::Vector4f>(arr1.get(), ARR_SIZE);
			fillArray<Math::Vector4f>(arr2.get(), ARR_SIZE);
			const double gen_finish = omp_get_wtime();
			total_gen_time += gen_finish - gen_start;
		}
		for (std::size_t j = 0; j < ARR_SIZE; j++)
			arr3.get()[j] = std::move(arr1.get()[j] + arr2.get()[j]);
	}
	const double finish = omp_get_wtime();
	std::cout << "Vector4f addition time is " << finish - start - total_gen_time << "\n";
}

void SIMDVectorsSubtractionBenchmark()
{
	const std::size_t ARR_SIZE = 100000;
	const std::size_t TIMES = 100000;
	std::unique_ptr<Math::Vector4f>	arr1(new Math::Vector4f[ARR_SIZE]),
									arr2(new Math::Vector4f[ARR_SIZE]),
									arr3(new Math::Vector4f[ARR_SIZE]);
	double total_gen_time = 0;
	const double start = omp_get_wtime();
	for (std::size_t i = 0; i < TIMES; i++)
	{
		if (i % 100 == 0)
		{
			const double gen_start = omp_get_wtime();
			fillArray<Math::Vector4f>(arr1.get(), ARR_SIZE);
			fillArray<Math::Vector4f>(arr2.get(), ARR_SIZE);
			const double gen_finish = omp_get_wtime();
			total_gen_time += gen_finish - gen_start;
		}
		for (std::size_t j = 0; j < ARR_SIZE; j++)
			arr3.get()[j] = std::move(arr2.get()[j] - arr1.get()[j]);
	}
	const double finish = omp_get_wtime();
	std::cout << "Vector4f subtraction time is " << finish - start - total_gen_time << "\n";
}

void SIMDVectorsScalarMultiplicationBenchmark()
{
	const std::size_t ARR_SIZE = 100000;
	const std::size_t TIMES = 100000;
	std::unique_ptr<Math::Vector4f>	arr1(new Math::Vector4f[ARR_SIZE]), 
									arr2(new Math::Vector4f[ARR_SIZE]);
	double total_gen_time = 0;
	const double start = omp_get_wtime();
	for (std::size_t i = 0; i < TIMES; i++)
	{
		if (i % 100 == 0)
		{
			const double gen_start = omp_get_wtime();
			fillArray<Math::Vector4f>(arr1.get(), ARR_SIZE);
			const double gen_finish = omp_get_wtime();
			total_gen_time += gen_finish - gen_start;
		}
		for (std::size_t j = 0; j < ARR_SIZE; j++)
		{
			float scalar = arr1.get()[j].getX() + arr1.get()[j].getY() + arr1.get()[j].getZ();
			arr2.get()[j] = std::move(arr1.get()[j] * scalar);
		}
	}
	const double finish = omp_get_wtime();
	std::cout << "Vector4f scalar multiplication time is " << finish - start - total_gen_time << "\n";
}

int main()
{
	SIMDVectorsAdditionBenchmark();
	SIMDVectorsSubtractionBenchmark();
	SIMDVectorsScalarMultiplicationBenchmark();
	return EXIT_SUCCESS;
}
