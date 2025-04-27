#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
class Branch 
{
public:
    Branch* parent;
    std::vector<Branch*> children;
    std::vector<std::string> elves;
    Branch(Branch* parent = nullptr) : parent(parent) 
    {
    }
    void addChild(Branch* child) 
    {
        children.push_back(child);
    }
    void addElf(const std::string& name) 
    {
        elves.push_back(name);
    }
    Branch* getTopBranch() 
    {
        if (parent == nullptr) return nullptr;
        if (parent->parent == nullptr) return parent;
        return parent->getTopBranch();
    }
    int countNeighbors(const std::string& elfName) 
    {
        int count = 0;
        for (const auto& elf : elves) 
        {
            if (elf != elfName) 
            {
                count++;
            }
        }
        return count;
    }
    Branch* findElf(const std::string& elfName) 
    {
        for (const auto& elf : elves) 
        {
            if (elf == elfName) 
            {
                return this;
            }
        }
        for (auto& child : children) 
        {
            Branch* result = child->findElf(elfName);
            if (result != nullptr) 
            {
                return result;
            }
        }
        return nullptr;
    }
};
void generateForest(std::vector<Branch*>& forest) 
{
    for (int i = 0; i < 5; ++i) 
    {
        Branch* tree = new Branch();
        int numBranches = rand() % 3 + 3; // 3 to 5 branches
        for (int j = 0; j < numBranches; ++j) 
        {
            Branch* bigBranch = new Branch(tree);
            int numMediumBranches = rand() % 2 + 2; // 2 to 3 medium branches
            for (int k = 0; k < numMediumBranches; ++k) 
            {
                Branch* mediumBranch = new Branch(bigBranch);
                bigBranch->addChild(mediumBranch);
            }
            tree->addChild(bigBranch);
        }
        forest.push_back(tree);
    }
}
int main() 
{
    srand(static_cast<unsigned int>(time(0)));
    std::vector<Branch*> forest;
    generateForest(forest);
    // Ввод имен эльфов
    for (auto& tree : forest) 
    {
        for (auto& bigBranch : tree->children) 
        {
            for (auto& mediumBranch : bigBranch->children) 
            {
                std::string elfName;
                std::cout << "Enter the name of elf for the house on the branch: ";
                std::cin >> elfName;
                if (elfName != "None") 
                {
                    mediumBranch->addElf(elfName);
                }
            }
        }
    }
    // Поиск эльфа
    std::string searchElfName;
    std::cout << "Enter the name of an elf for the search: ";
    std::cin >> searchElfName;
    for (auto& tree : forest) 
    {
        Branch* foundBranch = tree->findElf(searchElfName);
        if (foundBranch != nullptr) 
        {
            int neighbors = foundBranch->getTopBranch()->countNeighbors(searchElfName);
            std::cout << "The number of neighbors an " << searchElfName << " has: " << neighbors << std::endl;
            break;
        }
    }
    // Освобождение памяти
    for (auto& tree : forest) 
    {
        delete tree; // удаление
    }
    return 0;
}


