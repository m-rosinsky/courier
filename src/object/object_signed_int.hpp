/*!
 * @file src/object/object_signed_int.hpp
 *
 * @brief This file contains the signed integer object class.
 */

#ifndef _COURIER_SRC_OBJECT_OBJECT_SIGNED_INT_HPP
#define _COURIER_SRC_OBJECT_OBJECT_SIGNED_INT_HPP

#include "object.hpp"

#include <cstddef>          // uint*_t

/*!
 * @brief This class is the signed integer object class.
 */
class ObjectSignedInt : public Object
{

private:
    int32_t _data;
    uint8_t _width;

public:
    // Constructors.
    ObjectSignedInt()
        : _data(0), _width(32) {}
    ObjectSignedInt(int32_t __data, uint8_t __width)
        : _data(__data), _width(__width) {}

    ~ObjectSignedInt() override {}

    // Accessors.
    OBJECT_TYPE get_type(void) const override;
    std::string get_type_string(void) const override;
    std::string to_string(void) const override;
};

#endif // _COURIER_SRC_OBJECT_OBJECT_SIGNED_INT_HPP

/***   end of file   ***/
