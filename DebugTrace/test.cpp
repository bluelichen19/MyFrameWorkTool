#include <string.h>
#include <stdio.h>
#include "BlueSourceLog.h"

// const_cast，字面上理解就是去const属性。
// static_cast，命名上理解是静态类型转换。如int转换成char。
// dynamic_cast，命名上理解是动态类型转换。如子类和父类之间的多态类型转换。
// reinterpret_cast，仅仅重新解释类型，但没有进行二进制的转换。

// 一、new创建类对象与不new区别

// 下面是自己总结的一些关于new创建类对象特点：

// new创建类对象需要指针接收，一处初始化，多处使用
// new创建类对象使用完需delete销毁
// new创建对象直接使用堆空间，而局部不用new定义类对象则使用栈空间
// new对象指针用途广泛，比如作为函数返回值、函数参数等
// 频繁调用场合并不适合new，就像new申请和释放内存一样
// 二、new创建类对象实例

// 1、new创建类对象例子：

// CTest* pTest = new CTest();

// delete pTest;

// pTest用来接收类对象指针。

// 不用new，直接使用类定义申明：

// CTest mTest;

// 此种创建方式，使用完后不需要手动释放，该类析构函数会自动执行。而new申请的对象，则只有调用到delete时再会执行析构函数，如果程序退出而没有执行delete则会造成内存泄漏。

// 2、只定义类指针

// 这跟不用new申明对象有很大区别，类指针可以先行定义，但类指针只是个通用指针，在new之前并为该类对象分配任何内存空间。比如：

// CTest* pTest = NULL;

// 但使用普通方式创建的类对象，在创建之初就已经分配了内存空间。而类指针，如果未经过对象初始化，则不需要delete释放。

// 3、new对象指针作为函数参数和返回值

// 下面是天缘随手写一个例子，不太严谨。主要示意一下类指针对象作为返回值和参数使用。

// class CTest {
// public:
// int a;
// };

// class CBest {
// public:
// int b;
// };

// CTest* fun(CBest* pBest) {
// CTest* pTest = new CTest();
// pTest->a = pBest->b;
// return pTest;
// }

// 1.在类的声明尚未完成的情况下，可以声明指向该类的指针，但是不可声明该类的对象...
// 2.父类的指针可以指向子类的对象..

// 定义对象实例时，分配了内存。指针变量则未分配类对象所需内存

// 指针变量是间接访问，但可实现多态（通过父类指针可调用子类对象），并且没有调用构造函数。
// 直接声明可直接访问，但不能实现多态，声明即调用了构造函数（已分配了内存）。
// 至于那个效率高要看程序调用过程而定。

// C++的精髓之一就是多态性，只有指针或者引用可以达到多态。对象不行

// 用指针：
// 第一实现多态。
// 第二，在函数调用，传指针参数。不管你的对象或结构参数多么庞大，你用指针，传过去的就是4个字节。如果用对象，参数传递占用的资源就太大了

// int main() {
// CBest* pBest = new CBest();
// CTest* pRes= fun(pBest);

// if(pBest!=NULL)
// delete pBest;
// if(pRes!=NULL)
// delete pRes ;
// return -1;
// }
int main(int argc, char* argv[]) {
  //    BLUESourceLog* ptrBLUESourceLog = new
  //    BLUESourceLog((char*)__FUNCTION__,(char*)__FILE__,__LINE__);
  // BLUESourceLog* ptrBLUESourceLog = new
  // BLUESourceLog(const_cast<char*>(__FUNCTION__),const_cast<char*>(__FILE__),__LINE__);
  BLUESourceLog mBlueSourceLog(const_cast<char*>(__FUNCTION__),
                               const_cast<char*>(__FILE__), __LINE__);
  int a;
  int b;
  char p[] = "this is a test";
  BLUESourceLog mBlueSourceLog1(const_cast<char*>(__FUNCTION__),
                                const_cast<char*>(__FILE__), __LINE__);
  // ptrBLUESourceLog->SourceLogPrintf();
  a = 2;
  // ptrBLUESourceLog->SourceLogPrintf();
  BLUESourceLog mBlueSourceLog2(const_cast<char*>(__FUNCTION__),
                                const_cast<char*>(__FILE__), __LINE__);
  b = 3;
  // ptrBLUESourceLog->SourceLogPrintf();
  BLUESourceLog mBlueSourceLog3(const_cast<char*>(__FUNCTION__),
                                const_cast<char*>(__FILE__), __LINE__);
  BLUESourceLog* ptr =
      NULL;  // 注意这里！局部成员指针不会申请内存空间，局部成员对象才会申请内存空间，所以局部成员指针也不会调用构造函数，及时强行按照构造函数传递参数，编译器也会报错，因为，局部成员指针根本不会申请内存空间
  // delete ptrBLUESourceLog;
    
  return 0;
}
