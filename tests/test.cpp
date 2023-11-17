#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <compiler.hpp>

// Your compiler implementation here (Module, Function, BasicBlock, isValid, etc.)

TEST_CASE("Valid Functions in a Module") {
    // Create a module
    std::unique_ptr<Module> myModule = std::make_unique<Module>("MyModule");

    SECTION("Function with one entry and valid successors") {
        std::unique_ptr<Function> validFunc = std::make_unique<Function>("ValidFunction");

        // Add basic blocks to validFunc
        validFunc->setEntryBlockName("EntryBlock");
        validFunc->addBasicBlock(std::make_unique<BasicBlock>("EntryBlock"));
        validFunc->addBasicBlock(std::make_unique<BasicBlock>("SuccessorBlock1"));
        validFunc->addBasicBlock(std::make_unique<BasicBlock>("SuccessorBlock2"));

        myModule->addFunction(std::move(validFunc));

        REQUIRE(myModule->getFunctions().at("ValidFunction")->isValid() == true);
    }

    SECTION("Function with multiple entry blocks") {
        std::unique_ptr<Function> invalidFunc = std::make_unique<Function>("InvalidFunction");

        // Add basic blocks to invalidFunc
        invalidFunc->setEntryBlockName("EntryBlock1");
        invalidFunc->addBasicBlock(std::make_unique<BasicBlock>("EntryBlock1"));
        invalidFunc->addBasicBlock(std::make_unique<BasicBlock>("EntryBlock2"));
        invalidFunc->addBasicBlock(std::make_unique<BasicBlock>("SuccessorBlock"));

        myModule->addFunction(std::move(invalidFunc));

        REQUIRE(myModule->getFunctions().at("InvalidFunction")->isValid() == false);
    }

    // Add more test cases for different scenarios
}

TEST_CASE("Invalid Functions in a Module") {
    // Create a module
    std::unique_ptr<Module> myModule = std::make_unique<Module>("MyModule");

    SECTION("Function with unreachable basic block") {
        std::unique_ptr<Function> invalidFunc = std::make_unique<Function>("InvalidFunction");

        // Add basic blocks to invalidFunc
        invalidFunc->setEntryBlockName("EntryBlock");
        invalidFunc->addBasicBlock(std::make_unique<BasicBlock>("EntryBlock"));
        invalidFunc->addBasicBlock(std::make_unique<BasicBlock>("UnreachableBlock"));

        myModule->addFunction(std::move(invalidFunc));

        REQUIRE(myModule->getFunctions().at("InvalidFunction")->isValid() == false);
    }

    SECTION("Function with multiple successors with the same tag") {
        std::unique_ptr<Function> invalidFunc = std::make_unique<Function>("InvalidFunction");

        // Add basic blocks to invalidFunc
        invalidFunc->setEntryBlockName("EntryBlock");
        invalidFunc->addBasicBlock(std::make_unique<BasicBlock>("EntryBlock"));
        invalidFunc->addBasicBlock(std::make_unique<BasicBlock>("SuccessorBlock1"));
        invalidFunc->addBasicBlock(std::make_unique<BasicBlock>("SuccessorBlock2"));
        invalidFunc->getBasicBlocks().at(0)->addSuccessor(*invalidFunc->getBasicBlocks().at(1), "tag");
        invalidFunc->getBasicBlocks().at(0)->addSuccessor(*invalidFunc->getBasicBlocks().at(2), "tag"); // Duplicate tag

        myModule->addFunction(std::move(invalidFunc));

        REQUIRE(myModule->getFunctions().at("InvalidFunction")->isValid() == false);
    }

    // Add more test cases for different scenarios
}
