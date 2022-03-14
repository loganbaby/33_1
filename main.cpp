#include <iostream>
#include <exception>
#include <string>
#include <memory>
#include <map>

inline void setDataBase(std::map<std::string, int>* dataBase) {
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

    if (count < 0) throw std::invalid_argument("Invalid count of product");

    try {
      dataBase->insert(std::make_pair(name, count));
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

  inline int countEqualProducts(std::map<std::string, int>* dataBase) const {
    int counter = 0;
    for (auto it = dataBase->begin(); it != dataBase->end(); it++) {
      if (it->first == nameOfProduct) counter++;
    }

    return counter;
  }

 public:
  inline void add(std::map<std::string, int>* dataBase) {
    std::cout << "Enter the name of product: ";
    std::cin >> nameOfProduct;

    int counter = countEqualProducts(dataBase);
    if (counter <= 0 || counter > 1) throw std::invalid_argument("Invalid count");

    try {
      std::cout << "Enter the count of product: ";
      std::cin >> countOfProduct;

      dataBase->find(nameOfProduct)->second -= countOfProduct;
      if (countOfProduct <= 0 ||
          countOfProduct < dataBase->find(nameOfProduct)->second)
        throw std::invalid_argument("Invalid count");

      try {
        if (bin.empty()) {
          bin.insert(std::make_pair(nameOfProduct, countOfProduct));
        } else {
          int countInBase = dataBase->find(nameOfProduct)->second;
          int countInBin = bin.find(nameOfProduct)->second;

          if (countInBase < countOfProduct + countInBin)
            throw std::invalid_argument("Too many products");

          try {
            bin.insert(std::make_pair(nameOfProduct, countOfProduct));
          } catch (const std::invalid_argument& x) {
            std::cerr << x.what();
          }
        }

        std::cout << "Added!" << std::endl;
      } catch (const std::invalid_argument& x) {
        std::cerr << x.what();
      }
    } catch (const std::invalid_argument& x) {
      std::cerr << x.what();
    }
  }

  inline void remove(std::map<std::string, int>* dataBase) {
    std::cout << "Enter the name of product: ";
    std::cin >> nameOfProduct;

    int counter = countEqualProducts(dataBase);
    if (counter <= 0 || counter > 1)
      throw std::invalid_argument("Invalid count");

    try {
      std::cout << "Enter the count of products to delete: ";
      std::cin >> countOfProduct;

      bin.find(nameOfProduct)->second -= countOfProduct;
      if (countOfProduct <= 0 || bin.find(nameOfProduct)->second < 0)
        throw std::invalid_argument("Invalid count");

      try {
        bin.erase(nameOfProduct);
        std::cout << "Removed!" << std::endl;
      } catch (const std::invalid_argument& x) {
        std::cerr << x.what();
      }

    } catch (const std::invalid_argument& x) {
      std::cerr << x.what();
    }
  }
};

enum class CommandType { ADD = 1, REMOVE, EXIT };

inline void commandKeyboard(std::map<std::string, int>* dataBase, std::shared_ptr<Bin> bin) {
  setDataBase(dataBase);

  int command = 0;
  while (command != static_cast<int>(CommandType::EXIT)) {
    std::cout << static_cast<int>(CommandType::ADD) << "# Add" << std::endl;
    std::cout << static_cast<int>(CommandType::REMOVE) << "# Remove"
              << std::endl;
    std::cout << static_cast<int>(CommandType::EXIT) << "# Exit" << std::endl;
    std::cin >> command;

    switch (command) {
      case static_cast<int>(CommandType::ADD):
        bin->add(dataBase);
        break;
      case static_cast<int>(CommandType::REMOVE):
        bin->remove(dataBase);
        break;
      case static_cast<int>(CommandType::EXIT):
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
  commandKeyboard(&dataBase, bin);
}