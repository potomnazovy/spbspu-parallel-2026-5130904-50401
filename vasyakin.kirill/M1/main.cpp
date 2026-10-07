#include "utils.cpp"

#include <iostream>
#include <iomanip>
#include <limits>


int main(int argc, char** argv)
{
  if (argc < 3 || argc > 4)
  {
    std::cerr << "Too much" << '\n';
    return 1;
  }

  int threads = 0, tries = 0, seed = 0;

  try
  {
    size_t pos = 0;

    threads = vasyakin::parseArgument(argv[1], "threads");
    tries = vasyakin::parseArgument(argv[2], "tries");

    if (argc == 4)
    {
      seed = vasyakin::parseArgument(argv[3], "seed");
    }
  }
  catch (std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(std::out_of_range& e)
  {
    std::cerr << "Number is out of range: " << e.what() << '\n';
    return 1;
  }

  if (threads < 0 || tries <= 0 || seed < 0)
  {
    std::cerr << "threads, tries and seed must be positive" << '\n';
    return 1;
  }
}
