/* main.c
 *
 * Copyright 2022 Goutham Krishna K V
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name(s) of the above copyright
 * holders shall not be used in advertising or otherwise to promote the sale,
 * use or other dealings in this Software without prior written
 * authorization.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>


void* func(void* x) {
  // cast from void pointer to integer
  int xi = (int)(intptr_t)x;

  // print passed in value
  printf("INSIDE THREAD: %d", xi);

  // return the value after converting back to void pointer
  return (void*)(intptr_t)(xi + 123);
}

int main ()
{
  // create a POSIX thread to run
  pthread_t thread;
  pthread_create (&thread, NULL, func, (void*)100);

  // set up the pointer to which the value is returned to
  void* ret_from_thread;
  // declare the integer whhere the returning void pointer is casted to
  int ri;
  // wait for the thread to join and get the return value
  pthread_join(thread, &ret_from_thread);
  // cast it from void pointer to int
  ri = (int)(intptr_t)ret_from_thread;

  // print the newly created value
  printf("OUTSIDE THE THREAD: %d", ri);

  return 0;
}
