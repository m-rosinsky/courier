/*!
 * @file src/object/object_unsigned_int.cpp
 *
 * @brief This file contains the unsigned integer object class.
 */

#include "object_unsigned_int.hpp"

/******************************************************************************/
/*                          Accessor functions                                */
/******************************************************************************/

/*!
 * @brief This function returns the enumerated type of the object.
 */
OBJECT_TYPE ObjectUnsignedInt::get_type(void) const
{
    return OBJECT_TYPE_UNSIGNED_INT;
}

/******************************************************************************/

/*!
 * @brief This function returns the string representation of the object's type.
 */
std::string ObjectUnsignedInt::get_type_string(void) const
{
    return "uint";
}

/******************************************************************************/

/*!
 * @brief This function returns the string representation of the object's data.
 */
std::string ObjectUnsignedInt::to_string(void) const
{
    return std::to_string(_data);
}

/***   end of file   ***/
