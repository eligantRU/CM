#include "stdafx.h"

namespace po = boost::program_options;

int main(int argc, char * argv[])
{
	srand(unsigned(time(nullptr)));

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("n", po::value<size_t>(), "")
	;
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}

	if (vm.count("n"))
	{
		std::random_device rd;
		std::mt19937 g(rd());

		std::vector<size_t> permutation;
		for (size_t i = 0; i < vm["n"].as<size_t>(); ++i)
		{
			permutation.push_back(i);
		}
		std::shuffle(permutation.begin(), permutation.end(), g);

		for (const auto & el : permutation)
		{
			std::cout << el << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Use --help for reference" << std::endl;
	}
}
