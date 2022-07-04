#ifndef TodoDto_hpp
#define TodoDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class TodoDto : public oatpp::DTO
{

    DTO_INIT(TodoDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, task);
    DTO_FIELD(Int32, timestamp);
    DTO_FIELD(Boolean, status);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* TodoDto_hpp */
