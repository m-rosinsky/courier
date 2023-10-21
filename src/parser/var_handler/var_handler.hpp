/*!
 * @file src/parser/var_handler/var_handler.hpp
 *
 * @brief This file contains the variable handler class, which is
 *          a member of a parser context.
 */

#ifndef _COURIER_SRC_PARSER_VAR_HANDLER_VAR_HANDLER_HPP
#define _COURIER_SRC_PARSER_VAR_HANDLER_VAR_HANDLER_HPP

#include <cstddef>          // uint*_t
#include <memory>           // std::shared_ptr
#include <string>           // std::string
#include <vector>           // std::vector

#include "../../error/error.hpp"
#include "../../object/object.hpp"

typedef std::shared_ptr<Object> sp_obj_t;

/*!
 * @brief This struct defines a variable entry for a table.
 *
 * @param _name The name of the variable.
 * @param _scope The scope level of the variable.
 */
typedef struct _var
{
    std::string _name;
    uint32_t _scope;
    sp_obj_t _sp_obj;
} var_t;

/*!
 * @brief This class defines the variable handler context.
 *
 * @param _table The variable table.
 */
class var_table_t
{
private:
    std::vector<var_t> _table;

public:
    // Ctor and dtor.
    var_table_t() = default;
    ~var_table_t() = default;

    // Accessors.
    size_t size(void) const noexcept;

    // Modifiers.
    sp_obj_t find(const std::string& __name) noexcept;
    void clear(void) noexcept;
    err_type_e add(const std::string& __name,
                   uint32_t __scope,
                   sp_obj_t __sp_obj) noexcept;
    err_type_e drop_above_scope(uint32_t __scope) noexcept;
};

#endif // _COURIER_SRC_PARSER_VAR_HANDLER_VAR_HANDLER_HPP

/***   end of file   ***/
