#ifndef _BUSYBIN_THREAD_POOL_H_
#define _BUSYBIN_THREAD_POOL_H_

#include <thread>
using std::thread;
#include <mutex>
using std::mutex;
using std::unique_lock;
#include <condition_variable>
using std::condition_variable;
#include <vector>
using std::vector;
#include <queue>
using std::queue;
#include <functional>
using std::bind;
using std::function;
using std::ref;
#include <atomic>
using std::atomic_bool;

namespace busybin
{
  class ThreadPool
  {
    condition_variable workCond;
    mutex              workMutex;
    vector<thread>     threads;
    atomic_bool        halt;
    queue<function<void()> > jobs;

    void waitForWork();

  public:
    ThreadPool(unsigned numThreads);
    ~ThreadPool();
    void addJob(function<void()> job);
  };
}

#endif

