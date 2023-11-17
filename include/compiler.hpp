#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <fstream>
#include<algorithm>

#ifndef CE
#define CE
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

        void addSuccessor(BasicBlock& successor, const std::string& tag) {
            successors.emplace_back(&successor, tag);
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

        void setEntryBlockName(const std::string& entryName) {
            entryBlockName = entryName;
        }

        bool isValid() const {
            // Check if there is exactly one entry point
            int entryCount = 0;
            for (const auto& basicBlock : basicBlocks) {
                if (basicBlock != nullptr && basicBlock->getName() == entryBlockName) {
                    ++entryCount;
                }
            }

            if (entryCount != 1) {
                std::cerr << "Error: Function " << name << " must have exactly one entry point." << std::endl;
                return false;
            }

            // Check reachability from the entry point
            std::unordered_map<std::string, bool> visited;
            if (!isReachable(entryBlockName, visited)) {
                std::cerr << "Error: Not all basic blocks are reachable from the entry point in function " << name << "." << std::endl;
                return false;
            }

            // Check each basic block has at most one successor per tag
            for (const auto& basicBlock : basicBlocks) {
                if (basicBlock != nullptr) {
                    const auto& successors = basicBlock->getSuccessors();
                    std::unordered_map<std::string, bool> tagMap;
                    for (const auto& successorEntry : successors) {
                        const auto& tag = successorEntry.second;
                        if (!tagMap.emplace(tag, true).second) {
                            std::cerr << "Error: Basic block " << basicBlock->getName() << " has multiple successors with the same tag." << std::endl;
                            return false;
                        }
                    }
                }
            }

            return true;
        }

        const std::vector<std::unique_ptr<BasicBlock>>& getBasicBlocks() const {
            return basicBlocks;
        }

    private:
        std::string name;
        std::vector<std::unique_ptr<BasicBlock>> basicBlocks;
        std::string entryBlockName;  // Added member variable for the entry block name

        bool isReachable(const std::string& currentBlockName, std::unordered_map<std::string, bool>& visited) const {
            if (visited[currentBlockName]) {
                return true; // Already visited
            }

            visited[currentBlockName] = true;

            const auto& currentBlock = std::find_if(basicBlocks.begin(), basicBlocks.end(),
                                                    [currentBlockName](const auto& bb) { return bb->getName() == currentBlockName; });

            if (currentBlock == basicBlocks.end()) {
                return false; // Basic block not found
            }

            const auto& successors = (*currentBlock)->getSuccessors();
            for (const auto& successorEntry : successors) {
                const auto& nextBlockName = successorEntry.first->getName();
                if (!isReachable(nextBlockName, visited)) {
                    return false; // Not all successors are reachable
                }
            }

            return true;
        }
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
// } // namespace ce
#endif // CE
