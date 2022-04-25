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
 * Case 2: In this following example, the fn `reporter` must run only after
 * `assigner` is run, but when you run it, but again runs unexpectedly here.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>


pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int value = 100;
bool notified = false;

void* reporter(void* unused) {
  /* pthread_mutex_lock (&m); */
  /* while (!notified) { */
  /*   pthread_cond_wait (&cond_var, &m); */
  /* } */

  printf("The value is %d\n", value);

  /* pthread_mutex_unlock (&m); */

  return NULL;
}


void *assigner(void *unused) {
  value = 20;

  /* pthread_mutex_lock (&m); */
  /* notified = true; */
  /* pthread_cond_signal (&cond_var); */
  /* pthread_mutex_unlock (&m); */

  return NULL;
}

int main ()
{
  // create 2 therad objects
  pthread_t rep, asgn;

  // create the new threads from them, and assign functions
  pthread_create (&rep, NULL, reporter, NULL);
  pthread_create (&asgn, NULL, assigner, NULL);

  // the unused pointer
  void *unused;

  // wait till the 2 therads have been finished executing
  pthread_join (rep, unused);
  pthread_join (asgn, unused);

  return 0;
}
