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
		std::vector<size_t> bla;
		for (size_t i = 0; i < vm["n"].as<size_t>(); ++i)
		{
			bla.push_back(i);
		}

		std::vector<size_t> permutation;
		for (size_t i = 0; i < vm["n"].as<size_t>(); ++i)
		{
			size_t randNum = rand() % bla.size();
			permutation.push_back(bla[randNum]);
			auto it = std::find(bla.begin(), bla.end(), bla[randNum]);
			bla.erase(it);
		}
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
