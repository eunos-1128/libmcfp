/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2022-2025 Maarten L. hekkelman
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

/**
 * @file error.hpp
 *
 * Header file containing the error codes used by libmcfp
 *
 */

#include <string>
#include <system_error>
#include <type_traits>

namespace mcfp
{

// we use the new system_error stuff.

/**
 * @enum config_error error.hpp mcfp/error.hpp
 *
 * @brief A stronly typed class containing the error codes reported by @ref mcfp::config
 */
enum class config_error
{
	unknown_option = 1,              /**< The option requested does not exist, was not part of @ref mcfp::config::init. This error is returned by @ref mcfp::config::get */
	option_does_not_accept_argument, /**< When parsing the command line arguments a value (argument) was specified for an option that should not have one */
	missing_argument_for_option,     /**< A option without a required argument was found while parsing the command line arguments */
	option_not_specified,            /**< There was not option found on the command line and no default argument was specified for the option passed in @ref mcfp::config::get */
	invalid_config_file,             /**< The config file is not of the expected format */
	wrong_type_cast,                 /**< An attempt was made to ask for an option in another type than used when registering this option in @ref mcfp::config::init */
	wrong_type_cast_flag,            /**< The value assigned in a config file to a flag option was not 'true', 'false' or an integral numerical value */
	config_file_not_found            /**< The specified config file was not found */
};
/**
 * @brief Return the implementation for the config_category
 *
 * @return std::error_category&
 */
std::error_category &config_category();

/**
 * @brief Create an std::error_code for our config_error enum
 *
 * @param e A config_error enum
 * @return std::error_code
 */
inline std::error_code make_error_code(config_error e)
{
	return { static_cast<int>(e), config_category() };
}

/**
 * @brief Create an std::error_condition for our config_error enum
 *
 * @param e A config_error enum
 * @return std::error_condition
 */
inline std::error_condition make_error_condition(config_error e)
{
	return { static_cast<int>(e), config_category() };
}

} // namespace mcfp

// Make our error_codes implicitly convertible

namespace std
{

template <> // NOLINT(bugprone-std-namespace-modification,cert-dcl58-cpp)
struct is_error_code_enum<mcfp::config_error>
	: public true_type
{
};

} // namespace std
