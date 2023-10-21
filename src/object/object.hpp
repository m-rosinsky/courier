/*!
 * @file src/object/object.hpp
 *
 * @brief This file contains the object abstract base class that
 *          all objects inherit from.
 */

#ifndef _COURIER_SRC_OBJECT_OBJECT_HPP
#define _COURIER_SRC_OBJECT_OBJECT_HPP

#include <string>           // std::string

/*!
 * @brief This enum enumerates the object types.
 */
enum OBJECT_TYPE
{
    OBJECT_TYPE_SIGNED_INT = 0,
    OBJECT_TYPE_UNSIGNED_INT,
};

/*!
 * @brief This class is the abstract base class for objects.
 */
class Object
{
public:
    // Virtual destructor.
    virtual ~Object() {}

    // Accessors.
    virtual OBJECT_TYPE get_type(void) const = 0;
    virtual std::string get_type_string(void) const = 0;
    virtual std::string to_string(void) const = 0;
};

#endif // _COURIER_SRC_OBJECT_OBJECT_HPP

/***   end of file   ***/
