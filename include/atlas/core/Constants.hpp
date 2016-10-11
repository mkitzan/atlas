/**
 * \file Constants.hpp
 * \brief Defines some useful constants used throughout graphics applications.
 * These are fully templated and default to float.
 */

#ifndef ATLAS_INCLUDE_ATLAS_CORE_CONSTANTS_HPP
#define ATLAS_INCLUDE_ATLAS_CORE_CONSTANTS_HPP

#pragma once

#include <limits>

namespace atlas
{
    namespace core
    {
        /**
         * Returns the defined epsilon value for that data type.
         * @tparam The numerical data type.
         */
        template <typename GenType = float>
        constexpr GenType epsilon()
        {
            return std::numeric_limits<GenType>::epsilon();
        }

        /**
         * Returns the "infinity" (maximum value) that the specified data type
         * can represent.
         * @tparam The numerical data type.
         */
        template <typename GenType = float>
        constexpr typename std::enable_if<
            std::numeric_limits<GenType>::has_infinity, GenType>::type
        infinity()
        {
            return std::numeric_limits<GenType>::infinity();
        }

        template <typename GenType = float>
        constexpr typename std::enable_if<
            std::numeric_limits<GenType>::has_infinity, GenType>::type
            negInfinity()
        {
            return GenType(-1) * infinity<GenType>();
        }
    }
}

#endif