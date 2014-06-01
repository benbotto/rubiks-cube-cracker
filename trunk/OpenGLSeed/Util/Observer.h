#ifndef _BUSYBIN_OBSERVER_H_
#define _BUSYBIN_OBSERVER_H_

namespace busybin
{
  /**
   * A basic type-safe Ovserver interface.
   */
  template <class ObservableType>
  class Observer
  {
  public:
    /**
     * Process the notification.
     */
    virtual void notify(ObservableType* o) = 0;
  };
}

#endif
