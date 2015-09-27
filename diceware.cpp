#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <random>
#include <unordered_map>
#include <vector>
#include <stdexcept>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using boost::numeric::ublas::matrix;

void read_dict(std::unordered_map<int, std::string>& map, std::string filename)
{
    int key;
    std::string word;
    std::fstream fs{filename, std::fstream::in};

    while (!fs.eof()) {
        fs >> key;
        std::getline(fs, word);
        word.erase(word.begin(), std::find_if(word.begin(), word.end(),
                                              std::not1(std::ptr_fun<int, int>(std::isspace))));
        map[key] = word;
    }
}

int p_matrix_idx(matrix<int>& mat, int i, int j)
{
    return mat(i, j);
}

void roll_dice_sets(matrix<int>& mat)
{
    std::random_device rd;  // non-deterministic entropy.
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist(1, 5);
    for (int i = 0; i < mat.size1(); ++i)
        for (int j = 0; j < mat.size2(); ++j)
            mat(i, j) = dist(mt);
}

std::vector<int> bit_matrix_to_nums(matrix<int>& mat)
{
    std::vector<int> temp(5, 0);
    for (int i = 0; i < mat.size1(); ++i)
        for (int j = 0; j < mat.size2(); ++j)
            temp[i] += mat(i, j) * pow(10, j); // not all that portable, but I can trust ints to have 5 bits.

    return temp;
}

int main(int argc, char* argv[])
try
{
    if (argc != 3)
        throw std::invalid_argument{"Usage: "
                "./diceware diceware_dict.txt <no_of_words>"};

    std::unordered_map<int, std::string> dice_map;
    read_dict(dice_map, argv[1]);
    
    const     int no_of_words = std::stoi(argv[2]);
    constexpr int digits_per_word = 5;  // compile time #define, way better than #define
    matrix<int> m{no_of_words, digits_per_word};
    roll_dice_sets(m);

    std::vector<int> word_codes = bit_matrix_to_nums(m);

    std::cout << "Here is your diceware word list\n";
    for (int code : word_codes)
        std::cout << dice_map[code] << " ";
    std::cout << "\n";
}
catch (std::invalid_argument e)
{
    e.what();
    return -3;
}
catch (...)
{
    std::cout << "Something strange happened...";
    return -10;
}
