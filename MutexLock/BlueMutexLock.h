#ifndef _BLUE_MUTEX_LOCK_H_
#define _BLUE_MUTEX_LOCK_H_
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "../DebugTrace/BlueSourceLog.h"
class MUTEX_LOCK_BASE {
 public:
  MUTEX_LOCK_BASE(){};
  virtual ~MUTEX_LOCK_BASE(){};
};
class BLUEMutexLock : public MUTEX_LOCK_BASE {
 public:
  inline BLUEMutexLock(pthread_mutex_t& mutex, BLUESourceLog& blue_source_log)
      : mMutexKey(mutex), mBLUESourceLog(blue_source_log){};
  ~BLUEMutexLock(){};

 private:
  pthread_mutex_t& mMutexKey;
  BLUESourceLog& mBLUESourceLog;
};
#endif
