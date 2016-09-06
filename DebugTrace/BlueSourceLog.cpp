#include "BlueSourceLog.h"
inline int BLUESourceLog::SourceLogPrintf() {
  printf("====>BlueSourceLog function:%s==>line:%d==>path:%s\n", mFunctionName,
         mLineNumber, mFilePath);
  return 0;
}
