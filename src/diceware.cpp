#include "../include/diceware.hpp"

// Functor used to cache random number generator rather than
// instantiating it over again in a function call
int GetDicewareWordCode::operator()()
{
  int word_code = 0;
  for (int i = digits_per_word-1; i >= 0; --i)
    word_code += dist(mt) * pow(10, i);

  return word_code;
}

void GetDicewareWord::read_dict(const std::string& filename)
{
  int key;
  std::string word;

  std::fstream fs{filename, std::fstream::in};
  if (fs.fail())
    throw FileNotFound{filename + " is not in the current directory"};

  while (!fs.eof()) {
    fs >> key;
    std::getline(fs, word);
    word.erase(0, word.find_first_not_of("\t "));
    dice_map[key] = word;
  }
}
