#include "TodoService.hpp"

oatpp::Object<TodoDto> TodoService::createTodo(const oatpp::Object<CreateTodoDto> &todo, const oatpp::Int32 &timestamp)
{
    const auto dbResult = m_database->createTodo(todo, timestamp);

    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<TodoDto>>>();
    OATPP_ASSERT_HTTP(result->size() >= 1, Status::CODE_500, "Result is less than 1");

    return result[0];
}
oatpp::Object<TodoDto> TodoService::getTodoById(const oatpp::Int32 &id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection> &connection)
{
    auto dbResult = m_database->getTodoById(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<TodoDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}
oatpp::Vector<oatpp::Object<TodoDto>> TodoService::getAllTodo()
{
    auto dbResult = m_database->getAllTodo();
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<TodoDto>>>();

    return items;
}
oatpp::Object<TodoDto> TodoService::updateTodo(const oatpp::Object<UpdateTodoDto> &todo, const oatpp::Int32 &id)
{
    auto dbResult = m_database->updateTodo(todo, id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getTodoById(id);
}
oatpp::Object<StatusDto> TodoService::deleteTodo(const oatpp::Int32 &id)
{
    auto dbResult = m_database->deleteTodo(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "User was successfully deleted";
    return status;
}