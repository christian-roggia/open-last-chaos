/******************************************************************************************
  Copyright 2013 Andrea Ragusa

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************************************/

#ifndef __COMMON
#define __COMMON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>

#include "defs.h"
#include "stuff.hpp"


/*
typedef long	__suseconds_t;

#ifndef __suseconds_t_defined
typedef __suseconds_t suseconds_t;
# define __suseconds_t_defined
#endif
*/


#define ntohll(x) (((int64_t)(ntohl((int)((x << 32) >> 32))) << 32) | (unsigned int)ntohl(((int)(x >> 32))))

#define htonll(x) ntohll(x)
/*
void __pure_virtual() {};
void *__builtin_new(int size) {return (void*)malloc(size);}
void __builtin_delete(void *ptr) {free(ptr);}
void *builtin_new(int size) {return (void*)malloc(size);}
void builtin_delete(void *ptr) {free(ptr);}
void *builtin_vec_new(int size) {return builtin_new(size);}
void builtin_vec_delete(void *ptr) {builtin_delete(ptr);}
void *__builtin_vec_new(int size) {return (void*)malloc(size);}
void __builtin_vec_delete(void *ptr) {free(ptr);}
*/
#endif
