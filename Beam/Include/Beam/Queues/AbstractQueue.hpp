#ifndef BEAM_ABSTRACTQUEUE_HPP
#define BEAM_ABSTRACTQUEUE_HPP
#include "Beam/Queues/QueueReader.hpp"
#include "Beam/Queues/QueueWriter.hpp"
#include "Beam/Queues/Queues.hpp"

namespace Beam {

  /*! \class AbstractQueue
      \brief Base class for both the read and write side of a Queue.
      \tparam T The data to store in the Queue.
   */
  template<typename T>
  class AbstractQueue : public virtual QueueReader<T>,
      public virtual QueueWriter<T> {
    public:

      //! The Reader side of the Queue.
      using Reader = QueueReader<T>;

      //! The Writer side of the Queue.
      using Writer = QueueWriter<T>;

      //! The type being read from the Queue.
      using Target = typename Reader::Target;

      //! The type being pushed onto the Queue.
      using Source = typename Writer::Source;

      virtual ~AbstractQueue() = default;
  };
}

#endif
