
#ifndef StatusApiTestClient_hpp
#define StatusApiTestClient_hpp

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class StatusApiTestClient : public oatpp::web::client::ApiClient {

  API_CLIENT_INIT(StatusApiTestClient)

  API_CALL("GET", "/", getRoot)

  // TODO - add more client API calls here

};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif // StatusApiTestClient_hpp
