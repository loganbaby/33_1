#include <iostream>
#include <exception>
#include <string>
#include <memory>
#include <map>

inline void setDataBase(std::map<std::string, int>& dataBase) {
  std::string name = "";
  std::cout << "Enter 'ext' to exit setting data base!" << std::endl;
  std::cout << "-----------------------------------------" << std::endl;
  while (name != "ext") {
    std::cout << "Enter the name of product: ";
    std::cin >> name;

    if (name == "ext") break;

    std::cout << "Enter the count of product: ";
    int count = 0;
    std::cin >> count;

    try {
      if (count < 0) throw std::invalid_argument("Invalid count of product\n");
      dataBase.insert(std::make_pair(name, count));
      std::cout << "Added!" << std::endl;
    } catch (const std::invalid_argument& x) {
      std::cerr << x.what();
    }
  }
}

class Bin {
 private:
  std::map<std::string, int> bin;

  std::string nameOfProduct = "";
  int countOfProduct = 0;

 public:
  inline void add(std::map<std::string, int>& dataBase) {
    std::cout << "Enter the name of product: ";
    std::cin >> nameOfProduct;

    std::cout << "Enter the count of product: ";
    std::cin >> countOfProduct;

    dataBase[nameOfProduct] -= countOfProduct;

    try {
      if (countOfProduct <= 0 || dataBase[nameOfProduct] < 0)
        throw std::invalid_argument("Invalid count\n");
        bin.insert(std::make_pair(nameOfProduct, countOfProduct));
        std::cout << "Added!" << std::endl;
      } catch (const std::invalid_argument& x) {
      std::cerr << x.what();
    }
  }

  inline void remove(std::map<std::string, int>& dataBase) {
    std::cout << "Enter the name of product: ";
    std::cin >> nameOfProduct;

    std::cout << "Enter the count of products to delete: ";
    std::cin >> countOfProduct;

    try {
      if (countOfProduct <= 0 || bin[nameOfProduct] - countOfProduct < 0)
        throw std::invalid_argument("Invalid count\n");
      bin[nameOfProduct] -= countOfProduct;
      std::cout << "Removed!" << std::endl;
    } catch (const std::invalid_argument& x) {
      std::cerr << x.what();
    }
  }
};

enum class CommandType { ADD = 1, REMOVE, EXIT };

inline void commandKeyboard(std::map<std::string, int>& dataBase, std::shared_ptr<Bin> bin) {
  setDataBase(dataBase);

  int command = 0;
  while (command != static_cast<int>(CommandType::EXIT)) {
    std::cout << static_cast<int>(CommandType::ADD) << "# Add" << std::endl;
    std::cout << static_cast<int>(CommandType::REMOVE) << "# Remove"
              << std::endl;
    std::cout << static_cast<int>(CommandType::EXIT) << "# Exit" << std::endl;
    std::cin >> command;
    CommandType input_command = static_cast<CommandType>(command);

    switch (input_command) {
      case CommandType::ADD:
        bin->add(dataBase);
        break;
      case CommandType::REMOVE:
        bin->remove(dataBase);
        break;
      case CommandType::EXIT:
        std::cout << "Program finished!" << std::endl;
        break;
      default:
        std::cout << "Wrong input! Try again!" << std::endl;
        break;
    }
    system("pause");
    system("cls");
  }
}

int main() {
  std::map<std::string, int> dataBase;
  std::shared_ptr<Bin> bin = std::make_shared<Bin>();
  commandKeyboard(dataBase, bin);
}