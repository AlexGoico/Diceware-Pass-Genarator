#include "../include/diceware.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
try
{
  std::cout.sync_with_stdio(false); // faster io

  const int no_of_words = argc >= 2 ? std::atoi(argv[1]) : 5;
  if (no_of_words <= 0) {
    std::cout << "Must provide a number greater than or equal to 0\n";
    return -3;
  }

  GetDicewareWord get_word{"diceware_dict.txt"};
  std::string word[no_of_words];
  std::cout << " ---------------------------------\n";
  std::cout << "| Here is your diceware word list |\n";
  std::cout << " ---------------------------------\n";
  std::cout << "With    spaces: ";
  for (int i = 0; i < no_of_words; ++i) {
    word[i] = get_word();
    std::cout << word[i] << " ";
  }
  std::cout << "\n";

  std::cout << "Without spaces: ";
  for (int i = 0; i < no_of_words; ++i)
    std::cout << word[i];
  std::cout << "\n";
}
catch (const FileNotFound& e) {
  std::cout << e.what() << std::endl;
  return -4;
}
catch (...)
{
  std::cout << "Something strange happened..." << std::endl;
  return -77;
}
