#include "ishumi_impl_decoder.h"

using namespace ishumi::impl;

AbstractDecoder::DecodeError::DecodeError( const std::string &msg )
    : std::runtime_error::runtime_error(msg)
{}
