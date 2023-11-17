#include <compiler.hpp>

// namespace ce::complec_example {

    int main() {
        // Create a module
        std::unique_ptr<Module> myModule = std::make_unique<Module>("MyModule");

        // Function 1
        std::unique_ptr<Function> func1 = std::make_unique<Function>("Function1");
        func1->setEntryBlockName("BB1");

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

        // Function 2
        std::unique_ptr<Function> func2 = std::make_unique<Function>("Function2");
        func2->setEntryBlockName("BB4");

        // Add basic blocks to func2
        func2->addBasicBlock(std::make_unique<BasicBlock>("BB4"));
        func2->addBasicBlock(std::make_unique<BasicBlock>("BB5"));
        func2->addBasicBlock(std::make_unique<BasicBlock>("BB6"));

        // Access the basic blocks
        BasicBlock& bb4 = *func2->getBasicBlocks().at(0);
        BasicBlock& bb5 = *func2->getBasicBlocks().at(1);
        BasicBlock& bb6 = *func2->getBasicBlocks().at(2);

        bb4.addSuccessor(bb5, "success");
        bb5.addSuccessor(bb6, "next");

        myModule->addFunction(std::move(func2));

        // Validate and serialize to GraphViz
        for (const auto& functionEntry : myModule->getFunctions()) {
            const auto& function = functionEntry.second;

            if (function->isValid()) {
                std::cout << "Function '" << function->getName() << "' is valid." << std::endl;

                // Serialize to GraphViz
                std::ofstream outputFile(function->getName() + "_control_flow_graph_complex-example.dot");
                if (outputFile.is_open()) {
                    serializeToGraphViz(outputFile, *myModule);
                    outputFile.close();
                    std::cout << "GraphViz file '" << function->getName() << "_control_flow_graph_complex-example.dot' generated successfully." << std::endl;
                } else {
                    std::cerr << "Error: Unable to open file for writing." << std::endl;
                }
            } else {
                std::cerr << "Error: Function '" << function->getName() << "' is not valid." << std::endl;
            }
        }

        return 0;
    }
// } // namespace ce::complec_example