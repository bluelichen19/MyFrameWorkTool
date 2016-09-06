/* Copyright (C)
 * 2016 - BLUE
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _BLUE_DEBUG_TRACE_H_
#define _BLUE_DEBUG_TRACE_H_
#include <stdio.h>
#include <string>

#ifndef _DEBUG
#define _DEBUG
#endif

/* ----------------------------------------------------------------------------*/
/**
 * @Synopsis  do{printf }
 *
 * @Param "debug_info"
 *
 * @Returns
 */
/* ----------------------------------------------------------------------------*/
#ifdef _DEBUG
////#define DEBUGMSG(msg,date) printf(msg);printf(“%d%d%s”,date,_LINE_,_FILE_)
#define DEBUGMSG                                                     \
  do {                                                               \
    printf("debug_info==>");                                         \
    printf("%s line:%d %s <%s>\n", __FUNCTION__, __LINE__, __FILE__, \
           __DATE__);                                                \
  } while (0)
//
#else
#define DEBUGMSG
#endif

/* ----------------------------------------------------------------------------*/
/**
 * @Synopsis  PrintBuffer
 *
 * @Param pBuff
 * @Param nLen
 */
/* ----------------------------------------------------------------------------*/
void PrintBuffer(void* pBuff, unsigned int nLen) {
  unsigned int i = 0;

  const int nBytePerLine = 16;
  unsigned char* p = (unsigned char*)pBuff;
  // char szHex[3*nBytePerLine+1] = {0};
  char szHex[3 * nBytePerLine + 1];
  memset(szHex, 0, 3 * nBytePerLine + 1);
  if (NULL == pBuff || 0 == nLen) {
    printf("input ptr is NULL\n");
    return;
  }
  printf("-----------------begin-------------------\n");
  for (i = 0; i < nLen; ++i) {
    int idx = 3 * (i % nBytePerLine);
    if (0 == idx) {
      memset(szHex, 0, sizeof(szHex));
    }
#ifdef WIN32
    sprintf_s(&szHex[idx], 4, "%02x ", p[i]);  // buff长度要多传入1个字节
#else
    snprintf(&szHex[idx], 4, "%02x ", p[i]);  // buff长度要多传入1个字节
#endif

    // 以16个字节为一行，进行打印
    if (0 == ((i + 1) % nBytePerLine)) {
      printf("%s\n", szHex);
    }
  }

  // 打印最后一行未满16个字节的内容
  if (0 != (nLen % nBytePerLine)) {
    printf("%s\n", szHex);
  }

  printf("------------------end-------------------\n");
}

/* ----------------------------------------------------------------------------*/
/**
 * @Synopsis  PrintfByte
 *
 * @Param p[]
 * @Param len
 *
 * @Returns
 */
/* ----------------------------------------------------------------------------*/
int PrintfByte(char p[], int len) {
  int m = 0;
  for (m = 0; m < len; m++)
    printf("-%c-", p[m]);
  printf("\n");
  printf("printf complete");
  return 0;
}

class BLUEDebugTrace {
 public:
  BLUEDebugTrace(const char* function_name);
  ~BLUEDebugTrace();

 private:
  const char* mFunctionName;
};

#endif
