/*!
 * @file src/object/object_signed_int.cpp
 *
 * @brief This file contains the signed integer object class.
 */

#include "object_signed_int.hpp"

/******************************************************************************/
/*                          Accessor functions                                */
/******************************************************************************/

/*!
 * @brief This function returns the enumerated type of the object.
 */
OBJECT_TYPE ObjectSignedInt::get_type(void) const
{
    return OBJECT_TYPE_SIGNED_INT;
}

/******************************************************************************/

/*!
 * @brief This function returns the string representation of the object's type.
 */
std::string ObjectSignedInt::get_type_string(void) const
{
    return "int";
}

/******************************************************************************/

/*!
 * @brief This function returns the string representation of the object's data.
 */
std::string ObjectSignedInt::to_string(void) const
{
    return std::to_string(_data);
}

/***   end of file   ***/
