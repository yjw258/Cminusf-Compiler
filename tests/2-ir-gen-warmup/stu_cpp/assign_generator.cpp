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
#define DEBUG_OUTPUT //std::cout << __LINE__ << std::endl;
#endif

#define CONST_INT(num) \
    ConstantInt::get(num, module)

#define CONST_FP(num) \
    ConstantFP::get(num, module) // 得到常数值的表示,方便后面多次用到

int main() {
  auto module = new Module("Cminus code");  // module name是什么无关紧要
  auto builder = new IRBuilder(nullptr, module);
  Type *Int32Type = Type::get_int32_type(module);
  Type *ArrayType = Type::get_array_type(Int32Type, 10);    // array a's type

  DEBUG_OUTPUT

  // main函数
  auto mainFun = Function::create(FunctionType::get(Int32Type, {}),
                                  "main", module);
  auto bb = BasicBlock::create(module, "entry", mainFun);
  // BasicBlock的名字在生成中无所谓,但是可以方便阅读
  builder->set_insert_point(bb);

  auto retAlloca = builder->create_alloca(Int32Type);
  builder->create_store(CONST_INT(0), retAlloca);             // 默认 ret 0
  
  auto apAlloca = builder->create_alloca(ArrayType);
  DEBUG_OUTPUT
  auto a0GEP = builder->create_gep(apAlloca, {CONST_INT(0), CONST_INT(0)});    // get a[0]'s address
  DEBUG_OUTPUT
  builder->create_store(CONST_INT(10), a0GEP);  // a[0] = 10
  DEBUG_OUTPUT


  auto a0temp = builder->create_load(a0GEP); // load a[0]'s val in a0temp
  auto a1GEP = builder->create_gep(apAlloca, {CONST_INT(0), CONST_INT(1)});    // get a[1]'s address
  auto tempAlloca = builder->create_imul(a0temp, CONST_INT(2)); // temp = a[0] * 2
  builder->create_store(tempAlloca, a1GEP); // store temp's val in a[1]
  auto a1Load = builder->create_load(a1GEP); // load a[1]
  builder->create_store(a1Load, retAlloca); // return a[1]

  auto retLoad = builder->create_load(retAlloca);
  builder->create_ret(retLoad);
  std::cout << module->print();
  delete module;
  return 0;
}