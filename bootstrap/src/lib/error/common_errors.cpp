// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "error/common_errors.hpp"

using namespace gallop::Error;

InvalidArgumentError::InvalidArgumentError(const std::string &message_)
    : message(message_) {};

IOError::IOError(const std::string &message_) : message(message_) {};
