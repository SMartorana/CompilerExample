#include <compiler.hpp>

int main() {
    // Example usage
    std::unique_ptr<Module> myModule = std::make_unique<Module>("MyModule");

    // Adding functions to the module
    std::unique_ptr<Function> func1 = std::make_unique<Function>("Function1");
    func1->addBasicBlock(std::make_unique<BasicBlock>("BB1"));
    func1->addBasicBlock(std::make_unique<BasicBlock>("BB2"));
    myModule->addFunction(std::move(func1));

    std::unique_ptr<Function> func2 = std::make_unique<Function>("Function2");
    func2->addBasicBlock(std::make_unique<BasicBlock>("BB3"));
    myModule->addFunction(std::move(func2));

    // Removing a function from the module (if needed)
    myModule->removeFunction("Function2");

    return 0;
}