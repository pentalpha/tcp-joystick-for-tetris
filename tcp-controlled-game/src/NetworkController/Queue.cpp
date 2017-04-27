//
// Copyright (c) 2013 Juan Palacios juan.palacios.puyana@gmail.com
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//https://github.com/juanchopanza/cppblog/blob/master/Concurrency/Queue/Queue.h

#include "Queue.h"

int* Queue::pop()
{
  std::unique_lock<std::mutex> mlock(mutex_);
  if (queue_.empty())
  {
    return NULL;
  }
  int *val = queue_.front();
  queue_.pop();
  return val;
}

void Queue::push(int* item)
{
  std::unique_lock<std::mutex> mlock(mutex_);
  queue_.push(item);
  mlock.unlock();
  cond_.notify_one();
}
