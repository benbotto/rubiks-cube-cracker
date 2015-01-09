#ifndef _BUSYBIN_INVERTER_H_
#define _BUSYBIN_INVERTER_H_

namespace busybin
{
  /**
   * Class to toggle/invert between two Ts.  Useful for transformations.
   */
  template <class T>
  class Inverter
  {
    T val;
    T inverse;
  public:
    /**
     * Initialize the Inverter.
     * @param val The first value.
     * @param inverse The inverse of val.
     */
    Inverter(T val, T inverse)
    {
      this->val     = val;
      this->inverse = inverse;
    }

    /**
     * Called on each iteration.
     * @param ele The value to invert.
     */
    T operator()(const T& ele)
    {
      return (ele == val) ? inverse : val;
    }
  };
}

#endif

