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

// Fills the rows with digits
std::vector<int> get_word_codes(int no_of_words, int digits_per_word)
{
  std::vector<int> temp(no_of_words, 0);

  std::random_device rd;
  std::mt19937 mt{rd()};
  std::uniform_int_distribution<int> dist(1, 5);
  for (int i = 0; i < no_of_words; ++i) {
    for (int j = digits_per_word-1; j >= 0; --j)
      temp[i] += dist(mt) * pow(10, j);
  }

  return std::move(temp);
}

int main(int argc, char* argv[])
try
{
  std::unordered_map<int, std::string> dice_map;
  read_dict("diceware_dict.txt", dice_map);
    
  // Creates a matrix of
  // words in pass x digits_per_word
  const     int no_of_words = argc > 2 ? std::stoi(argv[1]) : 5;
  constexpr int digits_per_word = 5;
  const std::vector<int> word_codes = get_word_codes(no_of_words, digits_per_word);

  std::cout << "Here is your diceware word list\n";
  std::cout << "-------------------------------\n";
  for (int code : word_codes)
    std::cout << dice_map[code] << " ";
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
