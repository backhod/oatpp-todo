#ifndef StatusControllerTest_hpp
#define StatusControllerTest_hpp

#include "oatpp-test/UnitTest.hpp"

class StatusControllerTest : public oatpp::test::UnitTest {
public:

  StatusControllerTest() : UnitTest("TEST[StatusControllerTest]"){}
  void onRun() override;

};

#endif // StatusControllerTest_hpp
