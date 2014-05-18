#ifndef _BUSYBIN_ITERATOR_H_
#define _BUSYBIN_ITERATOR_H_

namespace busybin
{
  // Circular.
  template <class T>
  class Iterable;

  /**
   * Interface for iterable objects.
   * T is the type of object that the Iterable iterates over.
   */
  template <class T>
  class Iterator
  {
  protected:
    Iterable<T>* const pContainer;
    unsigned  current;

  public:
    /**
     * Initialize the iterator with a reference to the container,
     * and the current index into the container (used for at()).
     * @param cont The Iterable container.
     * @param current The index into the container.
     */
    Iterator(Iterable<T>& cont, unsigned current) : pContainer(&cont)
    {
      this->current = current;
    }

    /**
     * Increment current.
     */
    virtual Iterator& operator++()
    {
      ++this->current;
      return *this;
    }

    /**
     * Dereference - return the item at current.
     */
    virtual T& operator*() const
    {
      return this->pContainer->at(this->current);
    }

    /**
     * Comparison.
     * @param rhs The rhs iterator
     */
    virtual bool operator==(const Iterator& rhs) const
    {
      return this->pContainer == rhs.pContainer && this->current == rhs.current;
    }

    /**
     * Comparison.
     * @param rhs The rhs iterator
     */
    virtual bool operator!=(const Iterator& rhs) const
    {
      return this->pContainer != rhs.pContainer || this->current != rhs.current;
    }
  };

  /**
   * Interface for iterable objects - constant version.
   * T is the type of object that the Iterable iterates over.
   */
  template <class T>
  class ConstIterator
  {
  protected:
    const Iterable<T>* const pContainer;
    unsigned  current;

  public:
    /**
     * Initialize the iterator with a reference to the container,
     * and the current index into the container (used for at()).
     * @param cont The Iterable container.
     * @param current The index into the container.
     */
    ConstIterator(const Iterable<T>& cont, unsigned current) : pContainer(&cont)
    {
      this->current = current;
    }

    /**
     * Increment current.
     */
    virtual ConstIterator& operator++()
    {
      ++this->current;
      return *this;
    }

    /**
     * Dereference - return the item at current.
     */
    virtual const T& operator*() const
    {
      return this->pContainer->at(this->current);
    }

    /**
     * Comparison.
     * @param rhs The rhs iterator
     */
    virtual bool operator==(const ConstIterator& rhs) const
    {
      return this->pContainer == rhs.pContainer && this->current == rhs.current;
    }

    /**
     * Comparison.
     * @param rhs The rhs iterator
     */
    virtual bool operator!=(const ConstIterator& rhs) const
    {
      return this->pContainer != rhs.pContainer || this->current != rhs.current;
    }
  };
}

#endif

