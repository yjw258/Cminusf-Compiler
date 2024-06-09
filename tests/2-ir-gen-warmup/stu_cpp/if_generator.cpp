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
  Type *FloatType = Type::get_float_type(module);

   // main函数
  auto mainFun = Function::create(FunctionType::get(Int32Type, {}),"main", module);
  auto bb = BasicBlock::create(module, "entry", mainFun);
  
  builder->set_insert_point(bb);                        // 一个BB的开始,将当前插入指令点的位置设在bb
    
  auto retAlloca = builder->create_alloca(Int32Type);   // 在内存中分配返回值的位置
  auto aAlloca = builder->create_alloca(FloatType);     // 在内存中分配参数a的位置
  builder->create_store(CONST_FP(5.555), aAlloca);      // a = 5.555
  auto aLoad = builder->create_load(aAlloca);           // load a

  auto fcmp = builder->create_fcmp_gt(aLoad, CONST_FP(1));       // a > 1
  auto trueBB = BasicBlock::create(module, "trueBB", mainFun);
  auto falseBB = BasicBlock::create(module, "falseBB",  mainFun);
  builder->create_cond_br(fcmp, trueBB, falseBB);

  // a > 1
  builder->set_insert_point(trueBB);                    
  builder->create_store(CONST_INT(233), retAlloca);     // store 233 in retAlloca
  auto ret = builder->create_load(retAlloca);           // load retAlloca
  builder->create_ret(ret);
  builder->create_br(falseBB);  // 注意在下一个BB之前要Br一下

  // a <= 1
  builder->set_insert_point(falseBB); 
  builder->create_store(CONST_INT(0), retAlloca);     // store 233 in retAlloca
  ret = builder->create_load(retAlloca);           // load retAlloca
  builder->create_ret(ret);

  std::cout << module->print();
  delete module;
  return 0;
} 