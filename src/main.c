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

/*
 * Case 1.2: Try to rewrite square value as an atomic event
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>


// single global variable
// shared, accessible, modified by all threads
int accum = 0;

void* square(void* x) {
  // cast void pointer `x` into int
  int xi = (int)(intptr_t)x;

  // assign temp to accum
  int temp = accum;
  // increement temporary value by accum
  temp += xi * xi;
  // assignment here is an atomic operation
  accum = temp;

  // nothing to return, prevent warning
  return NULL;
}

int main ()
{
  pthread_t threads[20];
  for (int i = 0; i < 20; i++) {
    pthread_create (&threads[i], NULL, square, (void*)(intptr_t)i+1);
  }

  for (int i = 0; i < 20; i++) {
    void *res;
    pthread_join(threads[i], &res);
  }

  printf("ACCUM = %d\n", accum);
  return 0;
}
