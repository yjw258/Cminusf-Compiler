#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "IRBuilder.h"
#include "Module.h"
#include "Type.h"

#include <iostream>
#include <memory>

#ifdef DEBUG  // 用于调试信息,大家可以在编译过程中通过" -DDEBUG"来开启这一选项
#define DEBUG_OUTPUT std::cout << __LINE__ << std::endl;  // 输出行号的简单示例
#else
#define DEBUG_OUTPUT
#endif

#define CONST_INT(num) \
    ConstantInt::get(num, module)

#define CONST_FP(num) \
    ConstantFP::get(num, module) // 得到常数值的表示,方便后面多次用到

int main() {
  auto module = new Module("Cminus code");  // module name是什么无关紧要
  auto builder = new IRBuilder(nullptr, module);
  Type *Int32Type = Type::get_int32_type(module);

  // main函数
  auto mainFun = Function::create(FunctionType::get(Int32Type, {}), "main", module);
  auto bb = BasicBlock::create(module, "entry", mainFun);
  // BasicBlock的名字在生成中无所谓,但是可以方便阅读
  builder->set_insert_point(bb);

  auto retAlloca = builder->create_alloca(Int32Type);
  builder->create_store(CONST_INT(0), retAlloca);           // 默认 ret 0

  auto aAlloca = builder->create_alloca(Int32Type);         // a的存放
  auto iAlloca = builder->create_alloca(Int32Type);         // a的存放
  builder->create_store(CONST_INT(10), aAlloca);            // a = 10
  builder->create_store(CONST_INT(0), iAlloca);             // i = 0

  auto brBB = BasicBlock::create(module, "br", mainFun);     // branch basic block
  auto loopBB = BasicBlock::create(module, "loop", mainFun); // loop basic block
  auto exitBB = BasicBlock::create(module, "exit", mainFun); // exit loop

  builder->create_br(brBB);
  builder->set_insert_point(brBB);
  auto iLoad = builder->create_load(iAlloca);                // load i
  auto icmp = builder->create_icmp_lt(iLoad, CONST_INT(10));
  builder->create_cond_br(icmp, loopBB, exitBB);

  //loop
  builder->set_insert_point(loopBB);
  auto iPlus = builder->create_iadd(iLoad, CONST_INT(1));    // i = i + 1
  builder->create_store(iPlus, iAlloca);                     // store i
  auto aLoad = builder->create_load(aAlloca);                // load a
  iLoad = builder->create_load(iAlloca);                     // load i
  auto aPlus = builder->create_iadd(aLoad, iLoad);           // a = a + i
  builder->create_store(aPlus, aAlloca);                     // store a 
  builder->create_br(brBB);

  //exit
  builder->set_insert_point(exitBB);
  aLoad = builder->create_load(aAlloca);                    // load a
  builder->create_store(aLoad, retAlloca);
  auto ret = builder->create_load(retAlloca);
  builder->create_ret(ret);

  std::cout << module->print();
  delete module;
  return 0;
} 
