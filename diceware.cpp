#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <unordered_map>
#include <vector>
#include <stdexcept>

struct FileNotFound : public std::runtime_error
{
  explicit FileNotFound(const char* message)
    : std::runtime_error{message} { };
  explicit FileNotFound(const std::string& message)
    : std::runtime_error{message.c_str()} { };
};

void read_dict(const std::string& filename,
               std::unordered_map<int, std::string>& map)
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
    map[key] = word;
  }
}

// Functor used to cache random number generator rather than
// instantiating it over again in a function call
class GetWordCode
{
  int digits_per_word;
  std::random_device rd;
  std::mt19937 mt{};
  std::uniform_int_distribution<int> dist;
public:
  explicit GetWordCode(int dpw)
    : digits_per_word{dpw}, rd{}, mt{rd()}, dist{1, 5} { };

  int operator()()
  {
    int word_code = 0;
    for (int i = digits_per_word-1; i >= 0; --i)
      word_code += dist(mt) * pow(10, i);

    return word_code;
  }
};

int main(int argc, char* argv[])
try
{
  std::unordered_map<int, std::string> dice_map;
  read_dict("diceware_dict.txt", dice_map);
  
  const     int no_of_words = argc > 2 ? std::stoi(argv[1]) : 5;
  constexpr int digits_per_word = 5;

  GetWordCode get_word_code{digits_per_word};
  std::vector<int> word_codes(no_of_words, 0);
  for (int& word_code : word_codes)
    word_code = get_word_code();

  std::cout << " ---------------------------------\n";
  std::cout << "| Here is your diceware word list |\n";
  std::cout << " ---------------------------------\n";
  std::cout << "With    spaces: ";
  for (int code : word_codes)
    std::cout << dice_map[code] << " ";
  std::cout << "\n";

  std::cout << "Without spaces: ";
  for (int code : word_codes)
    std::cout << dice_map[code];
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
