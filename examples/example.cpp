#include <compiler.hpp>

// namespace ce::example {

    int main() {
        // Example usage
        std::unique_ptr<Module> myModule = std::make_unique<Module>("MyModule");

        // Adding functions to the module
        std::unique_ptr<Function> func1 = std::make_unique<Function>("Function1");
        func1->setEntryBlockName("BB1"); // Set entry point before adding basic blocks
        // Add basic blocks to func1
        func1->addBasicBlock(std::make_unique<BasicBlock>("BB1"));
        func1->addBasicBlock(std::make_unique<BasicBlock>("BB2"));
        func1->addBasicBlock(std::make_unique<BasicBlock>("BB3"));

        // Access the basic blocks
        BasicBlock& bb1 = *func1->getBasicBlocks().at(0);
        BasicBlock& bb2 = *func1->getBasicBlocks().at(1);
        BasicBlock& bb3 = *func1->getBasicBlocks().at(2);

        bb1.addSuccessor(bb2, "true");
        bb1.addSuccessor(bb3, "false");

        myModule->addFunction(std::move(func1));

        if (func1->isValid()) {
            // Serialize to GraphViz
            std::ofstream outputFile("control_flow_graph_example.dot");
            if (outputFile.is_open()) {
                serializeToGraphViz(outputFile, *myModule);
                outputFile.close();
                std::cout << "GraphViz file 'control_flow_graph_example.dot' generated successfully." << std::endl;
            }
            else {
                std::cerr << "Error: Unable to open file for writing." << std::endl;
            }
        } else {
            std::cerr << "Error: The function is not valid." << std::endl;
        }

        return 0;
    }
// } // namespace ce::example 