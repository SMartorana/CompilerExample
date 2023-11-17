#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <fstream>
// namespace ce{

    // Forward declarations
    class BasicBlock;
    class Function;
    class Module;

    // Basic block data structureclass BasicBlock {
    class BasicBlock {

    public:
        BasicBlock(const std::string& name) : name(name) {}

        const std::string& getName() const {
            return name;
        }

        void addSuccessor(std::unique_ptr<BasicBlock> successor, const std::string& tag) {
            successors.emplace_back(std::move(successor), tag);
        }

        void removeSuccessor(const std::string& successor) {
            for (auto it = successors.begin(); it != successors.end(); ++it) {
                if ((*it).first->getName() == successor) {
                    it = successors.erase(it);
                    --it; // Adjust the iterator to stay at the current position after erase
                }
            }
        }

        const std::vector<std::pair<std::unique_ptr<BasicBlock>, std::string>>& getSuccessors() const {
            return successors;
        }

    private:
        std::string name;
        std::vector<std::pair<std::unique_ptr<BasicBlock>, std::string>> successors;
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

        const std::vector<std::unique_ptr<BasicBlock>>& getBasicBlocks() const {
            return basicBlocks;
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
            functions.erase(functionName);
        }

        const std::unordered_map<std::string, std::unique_ptr<Function>>& getFunctions() const {
            return functions;
        }

    private:
        std::string name;
        std::unordered_map<std::string, std::unique_ptr<Function>> functions;
    };

    // Serialization routine for GraphViz
    void serializeToGraphViz(std::ostream& os, const Module& module) {
        os << "digraph " << module.getName() << " {" << std::endl;

        // Traverse functions
        for (const auto& functionEntry : module.getFunctions()) {
            const auto& function = functionEntry.second;

            // Traverse basic blocks in the function
            for (const auto& basicBlock : function->getBasicBlocks()) {
                if (basicBlock != nullptr) {
                    os << "  \"" << function->getName() << "_" << basicBlock->getName() << "\" [label=\"" << basicBlock->getName() << "\"];" << std::endl;

                    // Traverse successors of the basic block
                    for (const auto& successorEntry : basicBlock->getSuccessors()) {
                        const auto& successor = successorEntry.first;
                        const auto& tag = successorEntry.second;

                        os << "  \"" << function->getName() << "_" << basicBlock->getName() << "\" -> \""
                        << function->getName() << "_" << successor->getName() << "\" [label=\"" << tag << "\"];" << std::endl;
                    }
                }
            }
        }

        os << "}" << std::endl;
    }
// }