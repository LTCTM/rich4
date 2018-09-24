/*
 * Copyright (C)  2018 Iru Cai <mytbk920423@gmail.com>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <windows.h>
#include "rich4_time.h"

void get_local_time(rich4_time *t)
{
  SYSTEMTIME st;
  GetLocalTime(&st);
  t->day = st.wDay;
  t->month = st.wMonth;
  t->year = st.wYear;
  t->dayofweek = st.wDayOfWeek;
}
