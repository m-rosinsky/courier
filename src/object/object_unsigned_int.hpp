/*!
 * @file src/object/object_unsigned_int.hpp
 *
 * @brief This file contains the unsigned integer object class.
 */

#ifndef _COURIER_SRC_OBJECT_OBJECT_UNSIGNED_INT_HPP
#define _COURIER_SRC_OBJECT_OBJECT_UNSIGNED_INT_HPP

#include "object.hpp"

#include <cstddef>          // uint*_t

/*!
 * @brief This class is the unsigned integer object class.
 */
class ObjectUnsignedInt : public Object
{

private:
    uint32_t _data;
    uint8_t _width;

public:
    // Constructors.
    ObjectUnsignedInt()
        : _data(0), _width(32) {}
    ObjectUnsignedInt(int32_t __data, uint8_t __width)
        : _data(__data), _width(__width) {}

    ~ObjectUnsignedInt() override {}

    // Accessors.
    OBJECT_TYPE get_type(void) const override;
    std::string get_type_string(void) const override;
    std::string to_string(void) const override;
};

#endif // _COURIER_SRC_OBJECT_OBJECT_UNSIGNED_INT_HPP

/***   end of file   ***/
