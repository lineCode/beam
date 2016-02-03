#ifndef BEAM_HTTPREQUESTPARSER_HPP
#define BEAM_HTTPREQUESTPARSER_HPP
#include <deque>
#include <boost/noncopyable.hpp>
#include <boost/optional/optional.hpp>
#include "Beam/WebServices/HttpServerRequest.hpp"
#include "Beam/WebServices/WebServices.hpp"

namespace Beam {
namespace WebServices {

  /*! \class HttpRequestParser
      \brief Parses an HTTP request.
   */
  class HttpRequestParser : private boost::noncopyable {
    public:

      //! Constructs an HttpRequestParser.
      HttpRequestParser() = default;

      //! Feeds the parser additional characters to parse.
      /*!
        \param buffer The buffer containing the characters to parse.
        \return <code>true</code> iff there is a complete HttpServerRequest
                available.
      */
      template<typename Buffer>
      bool Feed(const Buffer& buffer);

      //! Returns the next HttpServerRequest.
      boost::optional<HttpServerRequest> GetNextRequest();

    private:
      std::deque<HttpServerRequest> m_requests;
  };

  template<typename Buffer>
  bool HttpRequestParser::Feed(const Buffer& buffer) {

    // TODO
    return false;
  }

  inline boost::optional<HttpServerRequest> HttpRequestParser::
      GetNextRequest() {
    if(m_requests.empty()) {
      return boost::none;
    }
    auto request = std::move(m_requests.front());
    m_requests.pop_front();
    return std::move(request);
  }
}
}

#endif
