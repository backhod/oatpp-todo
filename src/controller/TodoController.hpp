#ifndef TodoController_hpp
#define TodoController_hpp

#include "service/TodoService.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<- Begin Codegen

/**
 * Todo REST controller.
 */
class TodoController : public oatpp::web::server::api::ApiController {
 public:
  TodoController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

 private:
  TodoService m_todoService;  // Create todo service.
 public:
  static std::shared_ptr<TodoController> createShared(OATPP_COMPONENT(
      std::shared_ptr<ObjectMapper>,
      objectMapper)  // Inject objectMapper component here as default parameter
  ) {
    return std::make_shared<TodoController>(objectMapper);
  }

  ENDPOINT_INFO(createTodo) {
    info->summary = "Create new Todo";

    info->addTag("Todo");
    info->addConsumes<Object<CreateTodoDto>>("application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST",
           "todos",
           createTodo,
           BODY_DTO(Object<CreateTodoDto>, todoDto)) {
    const auto p1 = std::chrono::system_clock::now();
    auto timestamp =
        std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch())
            .count();
    return createDtoResponse(Status::CODE_200,
                             m_todoService.createTodo(todoDto, timestamp));
  }

  ENDPOINT_INFO(putTodo) {
    info->summary = "Update Todo by todoId";

    info->addTag("Todo");
    info->addConsumes<Object<UpdateTodoDto>>("application/json");
    info->addResponse<Object<TodoDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["todoId"].description = "Todo Identifier";
  }
  ENDPOINT("PUT",
           "todos/{todoId}",
           putTodo,
           PATH(Int32, todoId),
           BODY_DTO(Object<UpdateTodoDto>, todoDto)) {
    return createDtoResponse(Status::CODE_200,
                             m_todoService.updateTodo(todoDto, todoId));
  }

  ENDPOINT_INFO(getTodoById) {
    info->summary = "Get one Todo by todoId";

    info->addTag("Todo");
    info->addResponse<Object<TodoDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["todoId"].description = "Todo Identifier";
  }
  ENDPOINT("GET", "todos/{todoId}", getTodoById, PATH(Int32, todoId)) {
    return createDtoResponse(Status::CODE_200,
                             m_todoService.getTodoById(todoId));
  }

  ENDPOINT_INFO(getTodos) {
    info->summary = "Get Todos";

    info->addTag("Todo");
    info->addResponse<oatpp::Vector<oatpp::Object<TodoDto>>>(
        Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "todos", getTodos) {
    return createDtoResponse(Status::CODE_200, m_todoService.getAllTodo());
  }

  ENDPOINT_INFO(deleteTodo) {
    info->summary = "Delete Todo by todoId";

    info->addTag("Todo");
    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["todoId"].description = "Todo Identifier";
  }
  ENDPOINT("DELETE", "todos/{todoId}", deleteTodo, PATH(Int32, todoId)) {
    return createDtoResponse(Status::CODE_200,
                             m_todoService.deleteTodo(todoId));
  }
};

#include OATPP_CODEGEN_END(ApiController)  //<- End Codegen

#endif /* TodoController_hpp */
