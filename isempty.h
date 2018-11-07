/*
Copyright 2018 Styopa Semenukha
This file is part of isempty, see COPYING
*/

#ifndef _ISEMPTY_H
#define _ISEMPTY_H

#define RESULT_EMPTY 0
#define RESULT_NOT_EMPTY 1
#define RESULT_BAD_OPTIONS 2
#define RESULT_IO_ERROR 3

#define div_ceil(x, y) (x / y + (x % y ? 1 : 0))

#endif // _ISEMPTY_H
