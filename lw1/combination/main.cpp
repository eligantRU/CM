#include "stdafx.h"

namespace po = boost::program_options;

template <class T>
auto MeasureTime(T && fn)
{
	const auto begin = std::chrono::high_resolution_clock::now();
	fn();
	const auto end = std::chrono::high_resolution_clock::now();
	return (end - begin);
}

void GenerateCombination(const size_t n, const size_t k, const bool isNeedToPrint)
{
	std::vector<size_t> comb(k, 1);
	comb.resize(n, 0);

	do {
		for (size_t i = 0; i < n; ++i)
		{
			if (isNeedToPrint && comb[i])
			{
				std::cout << " " << i;
			}
		}
		if (isNeedToPrint)
		{
			std::cout << std::endl;
		}
	} while (std::prev_permutation(comb.begin(), comb.end()));
}

int main(int argc, char * argv[])
{
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("n", po::value<size_t>(), "")
		("k", po::value<size_t>(), "")
		("time", "measure time")
		("print", "print all combinations")
	;
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}

	const bool isNeedToMeasure = vm.count("time");
	const bool isNeedToPrint = vm.count("print");
	if (vm.count("n") && vm.count("k"))
	{
		std::cout << "C(" << vm["n"].as<size_t>() << ", "
		          << vm["k"].as<size_t>() << ")" << std::endl;
		const auto t = MeasureTime([&]() {
			GenerateCombination(vm["n"].as<size_t>(), vm["k"].as<size_t>(), isNeedToPrint);
		});
		if (isNeedToMeasure)
		{
			std::cerr << "runtime = "
			          << std::chrono::duration_cast<std::chrono::milliseconds>(t).count()
			          << " ms" << std::endl;
		}
	}
	else
	{
		std::cout << "Use --help for reference" << std::endl;
	}
}
