#ifndef BEAM_BASEQUEUE_HPP
#define BEAM_BASEQUEUE_HPP
#include <exception>
#include <boost/noncopyable.hpp>
#include "Beam/Queues/PipeBrokenException.hpp"
#include "Beam/Queues/Queues.hpp"

namespace Beam {

  /*! \class BaseQueue
      \brief Base class for a Queue.
   */
  class BaseQueue : private boost::noncopyable {
    public:
      virtual ~BaseQueue() = default;

      //! Breaks the Queue, indicating no further values will be published.
      virtual void Break();

      //! Breaks the Queue, indicating no further values will be published.
      /*!
        \param e The reason why the Queue was broken.
      */
      virtual void Break(const std::exception_ptr& e) = 0;

      //! Breaks the Queue, indicating no further values will be published.
      /*!
        \param e The reason why the Queue was broken.
      */
      template<typename E>
      void Break(const E& e);
  };

  inline void BaseQueue::Break() {
    Break(PipeBrokenException());
  }

  template<typename E>
  void BaseQueue::Break(const E& e) {
    Break(std::make_exception_ptr(e));
  }
}

#endif
