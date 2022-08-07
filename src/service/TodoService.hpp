#ifndef TodoService_hpp
#define TodoService_hpp

#include "db/TodoDb.hpp"
#include "dto/TodoDto.hpp"
#include "dto/StatusDto.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class TodoService
{
private:
    OATPP_COMPONENT(std::shared_ptr<TodoDb>, m_database);
    typedef oatpp::web::protocol::http::Status Status;

public:
    oatpp::Object<TodoDto> createTodo(const oatpp::Object<CreateTodoDto> &todo, const oatpp::Int32 &timestamp);
    oatpp::Object<TodoDto> getTodoById(const oatpp::Int32 &id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection> &connection = nullptr);
    oatpp::Vector<oatpp::Object<TodoDto>> getAllTodo();
    oatpp::Object<TodoDto> updateTodo(const oatpp::Object<UpdateTodoDto> &todo, const oatpp::Int32 &id);
    oatpp::Object<StatusDto> deleteTodo(const oatpp::Int32 &id);
};

#endif