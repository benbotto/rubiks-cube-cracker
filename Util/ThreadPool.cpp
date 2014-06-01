#include "ThreadPool.h"

namespace busybin
{
  /**
   * Initialize and start all threads.
   */
  ThreadPool::ThreadPool(unsigned numThreads)
  {
    this->halt = false;

    for (unsigned i = 0; i < numThreads; ++i)
      this->threads.push_back(thread(&ThreadPool::waitForWork, ref(*this)));
  }

  /**
   * Join all the threads.
   */
  ThreadPool::~ThreadPool()
  {
    // Flag halt.
    unique_lock<mutex> lock(workMutex);
    halt = true;
    lock.unlock();
    workCond.notify_all();

    // Join all threads.
    for (thread& t : this->threads)
      t.join();
  }

  /**
   * Wait for some work (or halt).
   * @param i The thread number.
   */
  void ThreadPool::waitForWork()
  {
    while (1)
    {
      function<void()> job;
      unique_lock<mutex> wLock(this->workMutex);

      // Wake up if halt is flagged or there is work in the queue.
      this->workCond.wait(wLock, [this]
      {
        return this->halt || this->jobs.size() != 0;
      });

      // If halt is flagged and there's no more work, exit.
      if (this->halt && this->jobs.size() == 0)
        return;

      // Get the next job and release the lock.
      job = this->jobs.front();
      this->jobs.pop();
      wLock.unlock();

      // Run the job.
      job();
    }
  }

  /**
   * Add a job.
   * @param job The function to run.
   */
  void ThreadPool::addJob(function<void()> job)
  {
    unique_lock<mutex> wLock(this->workMutex);

    // Add the job.
    this->jobs.push(job);
    wLock.unlock();

    // Wake up a waiting thread.
    this->workCond.notify_one();
  }
}

