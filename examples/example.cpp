#include <compiler.hpp>

int main() {
    // Example usage
    std::unique_ptr<Module> myModule = std::make_unique<Module>("MyModule");

    // Adding functions to the module
    std::unique_ptr<Function> func1 = std::make_unique<Function>("Function1");
    std::unique_ptr<BasicBlock> bb1 = std::make_unique<BasicBlock>("BB1");
    std::unique_ptr<BasicBlock> bb2 = std::make_unique<BasicBlock>("BB2");
    std::unique_ptr<BasicBlock> bb3 = std::make_unique<BasicBlock>("BB3");

    bb1->addSuccessor(std::move(bb2), "true");
    bb1->addSuccessor(std::move(bb3), "false");

    func1->addBasicBlock(std::move(bb1));
    func1->addBasicBlock(std::move(bb2));
    func1->addBasicBlock(std::move(bb3));
    myModule->addFunction(std::move(func1));

    // Serialize to GraphViz
    std::ofstream outputFile("control_flow_graph.dot");
    if (outputFile.is_open()) {
        serializeToGraphViz(outputFile, *myModule);
        outputFile.close();
        std::cout << "GraphViz file 'control_flow_graph.dot' generated successfully." << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }

    return 0;
}
