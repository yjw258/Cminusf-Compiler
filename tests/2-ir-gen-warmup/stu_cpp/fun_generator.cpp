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

  // callee函数
  // 函数参数类型的vector
  std::vector<Type *> Ints(1, Int32Type);

   //通过返回值类型与参数类型列表得到函数类型
  auto calleeFunTy = FunctionType::get(Int32Type, Ints);

  // 由函数类型得到函数
  auto calleeFun = Function::create(calleeFunTy,
                                 "callee", module);

  // BB的名字在生成中无所谓,但是可以方便阅读
  auto bb = BasicBlock::create(module, "entry", calleeFun);

  builder->set_insert_point(bb);                        // 一个BB的开始,将当前插入指令点的位置设在bb
  
  auto retAlloca = builder->create_alloca(Int32Type);   // 在内存中分配返回值的位置
  auto aAlloca = builder->create_alloca(Int32Type);     // 在内存中分配参数a的位置
  
  std::vector<Value *> args;  // 获取gcd函数的形参,通过Function中的iterator
  for (auto arg = calleeFun->arg_begin(); arg != calleeFun->arg_end(); arg++) {
    args.push_back(*arg);   // * 号运算符是从迭代器中取出迭代器当前指向的元素
  }

  builder->create_store(args[0], aAlloca);  // 将参数a store下来
  auto aLoad = builder->create_load(aAlloca); // load a
  auto mul = builder->create_imul(CONST_INT(2), aLoad); // mul = 2 * a
  builder->create_store(mul, retAlloca);
  auto retload = builder->create_load(retAlloca);
  builder->create_ret(retload);

  // main函数
  auto mainFun = Function::create(FunctionType::get(Int32Type, {}), "main", module);
  bb = BasicBlock::create(module, "entry", mainFun);
  // BasicBlock的名字在生成中无所谓,但是可以方便阅读
  builder->set_insert_point(bb);

  auto argAlloca = builder->create_alloca(Int32Type);
  builder->create_store(CONST_INT(110), argAlloca);
  auto argLoad = builder->create_load(argAlloca); // load arg
  auto call = builder->create_call(calleeFun, {argLoad}); // callee(110) 
  builder->create_ret(call);

  std::cout << module->print();
  delete module;
  return 0;
}