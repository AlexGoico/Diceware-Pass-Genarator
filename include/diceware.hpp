#include <fstream>
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

// Functor used to cache random number generator rather than
// instantiating it over again in a function call
class GetDicewareWordCode
{
  int digits_per_word;
  std::random_device rd;
  std::mt19937 mt{};
  std::uniform_int_distribution<int> dist;
public:
  explicit GetDicewareWordCode()
    : digits_per_word{5}, rd{}, mt{rd()}, dist{1, 5} { };

  int operator()();
};

// Functor taking a functor in order to provide a flexible
// diceware word generation function.
class GetDicewareWord
{
  GetDicewareWordCode get_word_code;
  std::unordered_map<int, std::string> dice_map;

public:
  explicit GetDicewareWord(const std::string& filename)
    : get_word_code{} { read_dict(filename); };
  void read_dict(const std::string& filename);

  std::string operator()()
  {
    return dice_map[get_word_code()];
  }
};
