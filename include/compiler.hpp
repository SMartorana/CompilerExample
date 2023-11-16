#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

// Forward declarations
class BasicBlock;
class Function;
class Module;

// Basic block data structure
class BasicBlock {
public:
    BasicBlock(const std::string& name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

private:
    std::string name;
};

// Function data structure
class Function {
public:
    Function(const std::string& name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    void addBasicBlock(std::unique_ptr<BasicBlock> basicBlock) {
        basicBlocks.push_back(std::move(basicBlock));
    }

    void removeBasicBlock(const std::string& basicBlockName) {
        // This is just a placeholder, actual implementation depends on your requirements
        for (auto it = basicBlocks.begin(); it != basicBlocks.end(); ++it) {
            if ((*it)->getName() == basicBlockName) {
                it = basicBlocks.erase(it);
                --it; // Adjust the iterator to stay at the current position after erase
            }
        }
    }

private:
    std::string name;
    std::vector<std::unique_ptr<BasicBlock>> basicBlocks;
};

// Module data structure
class Module {
public:
    Module(const std::string& name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    void addFunction(std::unique_ptr<Function> function) {
        functions.emplace(function->getName(), std::move(function));
    }

    void removeFunction(const std::string& functionName) {
        auto it = functions.find(functionName);
        if (it != functions.end()) {
            functions.erase(it);
        }
    }

private:
    std::string name;
    std::unordered_map<std::string, std::unique_ptr<Function>> functions;
};

// int main() {
//     // Example usage
//     std::unique_ptr<Module> myModule = std::make_unique<Module>("MyModule");

//     // Adding functions to the module
//     std::unique_ptr<Function> func1 = std::make_unique<Function>("Function1");
//     func1->addBasicBlock(std::make_unique<BasicBlock>("BB1"));
//     func1->addBasicBlock(std::make_unique<BasicBlock>("BB2"));
//     myModule->addFunction(std::move(func1));

//     std::unique_ptr<Function> func2 = std::make_unique<Function>("Function2");
//     func2->addBasicBlock(std::make_unique<BasicBlock>("BB3"));
//     myModule->addFunction(std::move(func2));

//     // Removing a function from the module (if needed)
//     myModule->removeFunction("Function2");

//     return 0;
// }
