#pragma once

#include <string>
#include <exception>

namespace simo
{
namespace shapes
{

/// @todo (pavel) improve these types

class exception : public std::exception
{
  public:
    const char* what() const noexcept override
    {
        return "shapes error";
    }
};

class parse_error : public exception
{
  public:
    const char* what() const noexcept override
    {
        return "parse error";
    }
};

}  // namespace shapes
}  // namespace simo
