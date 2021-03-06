#include <doctest/doctest.h>
#include "Beam/Collections/EnumIterator.hpp"
#include "Beam/Parsers/EnumeratorParser.hpp"
#include "Beam/Parsers/ReaderParserStream.hpp"

using namespace Beam;
using namespace Beam::Parsers;

namespace {
  BEAM_ENUM(Fruit,
    APPLE,
    PEAR,
    BANANA);

  std::string ToString(Fruit fruit) {
    if(fruit == Fruit::APPLE) {
      return "APPLE";
    } else if(fruit == Fruit::PEAR) {
      return "PEAR";
    } else if(fruit == Fruit::BANANA) {
      return "BANANA";
    }
    return "NONE";
  }
}

namespace Beam {
  template<>
  struct EnumeratorCount<Fruit> : std::integral_constant<int, 3> {};
}

TEST_SUITE("EnumeratorParser") {
  TEST_CASE("read_enumerator") {
    auto parser = EnumeratorParser<Fruit>(begin(MakeRange<Fruit>()),
      end(MakeRange<Fruit>()), static_cast<std::string (*)(Fruit)>(ToString));
    auto source = ParserStreamFromString("APPLE");
    auto value = Fruit();
    REQUIRE(parser.Read(source, value));
    REQUIRE(value == Fruit::APPLE);
    source = ParserStreamFromString("CAT");
    REQUIRE(!parser.Read(source, value));
  }
}
