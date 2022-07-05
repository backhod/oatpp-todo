#ifndef TodoDb_hpp
#define TodoDb_hpp

#include "dto/TodoDto.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class TodoDb : public oatpp::orm::DbClient
{
public:
    TodoDb(const std::shared_ptr<oatpp::orm::Executor> &executor) : oatpp::orm::DbClient(executor)
    {
        oatpp::orm::SchemaMigration migration(executor);
        migration.addFile(1, DATABASE_MIGRATIONS "/001_init.sql");
        migration.migrate(); // <-- run migrations. This guy will throw on error.

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("TodoDb", "Migration - OK. Version=%lld.", version);
    }

    QUERY(createTodo,
          "INSERT INTO Todo"
          "(task, timestamp) VALUES "
          "(:todo.task, :timestamp);",
          PARAM(oatpp::Object<CreateTodoDto>, todo),
          PARAM(oatpp::Int32, timestamp))

    QUERY(getAllTodo, "SELECT * FROM Todo;")

    QUERY(getTodoById, "SELECT * FROM Todo WHERE id=:id", PARAM(oatpp::Int32, id))

    QUERY(updateTodo,
          "UPDATE Todo "
          "SET"
          " task=:todo.task "
          " status=:todo.status "
          "WHERE"
          " id=:id;",
          PARAM(oatpp::Object<UpdateTodoDto>, todo),
          PARAM(oatpp::Int32, id))

    QUERY(deleteTodo, "DELETE FROM Todo WHERE id=:id", PARAM(oatpp::Int32, id))
};

#include OATPP_CODEGEN_END(DbClient)

#endif