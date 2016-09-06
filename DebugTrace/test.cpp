#include <string.h>
#include <stdio.h>
#include "BlueSourceLog.h"

// const_cast，字面上理解就是去const属性。
// static_cast，命名上理解是静态类型转换。如int转换成char。
// dynamic_cast，命名上理解是动态类型转换。如子类和父类之间的多态类型转换。
// reinterpret_cast，仅仅重新解释类型，但没有进行二进制的转换。


int main(int argc, char* argv[]) {
//    BLUESourceLog* ptrBLUESourceLog = new BLUESourceLog((char*)__FUNCTION__,(char*)__FILE__,__LINE__);
    //BLUESourceLog* ptrBLUESourceLog = new BLUESourceLog(const_cast<char*>(__FUNCTION__),const_cast<char*>(__FILE__),__LINE__);
    BLUESourceLog mBlueSourceLog(const_cast<char*>(__FUNCTION__),const_cast<char*>(__FILE__),__LINE__);
    int a;
    int b;
    char p[]="this is a test"; 
    BLUESourceLog mBlueSourceLog1(const_cast<char*>(__FUNCTION__),const_cast<char*>(__FILE__),__LINE__);
    //ptrBLUESourceLog->SourceLogPrintf();
    a = 2;
    //ptrBLUESourceLog->SourceLogPrintf();
    BLUESourceLog mBlueSourceLog2(const_cast<char*>(__FUNCTION__),const_cast<char*>(__FILE__),__LINE__);
    b =3;
    //ptrBLUESourceLog->SourceLogPrintf();
    BLUESourceLog mBlueSourceLog3(const_cast<char*>(__FUNCTION__),const_cast<char*>(__FILE__),__LINE__);
    //delete ptrBLUESourceLog;
    
  return 0;
}
