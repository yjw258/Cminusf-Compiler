#ifndef CONSTPROPAGATION_HPP
#define CONSTPROPAGATION_HPP
#include "PassManager.hpp"
#include "Constant.h"
#include "Instruction.h"
#include "Module.h"

#include "Value.h"
#include "IRBuilder.h"
#include <vector>
#include <stack>
#include <unordered_map>

// tips: 用来判断value是否为ConstantFP/ConstantInt
<<<<<<< HEAD
ConstantFP* cast_constantfp(Value *value);
ConstantInt* cast_constantint(Value *value);

=======
ConstantFP *cast_constantfp(Value *value);
ConstantInt *cast_constantint(Value *value);
>>>>>>> c7f1069 (commit all)

// tips: ConstFloder类

class ConstFolder
{
public:
    ConstFolder(Module *m) : module_(m) {}
    ConstantInt *compute(
        Instruction::OpID op,
        ConstantInt *value1,
        ConstantInt *value2);
<<<<<<< HEAD
=======
    ConstantFP *computeFP(
        Instruction::OpID op,
        ConstantFP *value1,
        ConstantFP *value2);
    Constant *computeConvert(
        Instruction::OpID op,
        Constant *value);
    Constant *computeIcmp(
        CmpInst::CmpOp op,
        ConstantInt *value1,
        ConstantInt *value2);
    Constant *computeFcmp(
        FCmpInst::CmpOp op,
        ConstantFP *value1,
        ConstantFP *value2);
>>>>>>> c7f1069 (commit all)
    // ...
private:
    Module *module_;
};

class ConstPropagation : public Pass
{
public:
    ConstPropagation(Module *m) : Pass(m) {}
<<<<<<< HEAD
    void run();
=======
    void CPpass(BasicBlock *bb);
    void run();
    std::vector<BasicBlock *> visited_bb;           //basic block which has been handled
    std::map<std::string, Constant *> constant_map; //record const var and its value
>>>>>>> c7f1069 (commit all)
};

#endif
