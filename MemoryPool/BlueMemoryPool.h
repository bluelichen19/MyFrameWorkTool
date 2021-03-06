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

#ifndef _BLUE_SINGLE_THREAD_MEMORY_POOL_H_
#define _BLUE_SINGLE_THREAD_MEMORY_POOL_H_
#include "../BaseTool/BlueBaseTools.h"
class Rational {
 public:
  Rational(int32_t a = 0, int32_t b = 1) : n(a), d(b){};

 private:
  int32_t n;
  int32_t d;
};
#endif /* ifndef SYMBOL */
