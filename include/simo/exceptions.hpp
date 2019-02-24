#pragma once

#include <string>
#include <exception>

namespace simo
{
namespace shapes
{
namespace exceptions
{

/*!
 * @brief base shapes exception
 */
class shapes_exception : public std::exception
{
  public:
    explicit shapes_exception(const char* what)
        : m_what(what) {}

    const char* what() const noexcept override
    {
        return m_what.c_str();
    }

  protected:
    void set_reason(const std::string& reason)
    {
        m_what.append(": ");
        m_what.append(reason);
    }

  private:
    std::string m_what{};
};

class parse_error : public shapes_exception
{
  public:
    explicit parse_error(const std::string& reason)
        : shapes_exception("parse error")
    {
        set_reason(reason);
    }
};

class not_implemented_error : public shapes_exception
{
  public:
    not_implemented_error()
        : shapes_exception("not implemented error")
    {
    }

    explicit not_implemented_error(const std::string& reason)
        : shapes_exception("not implemented error")
    {
        set_reason(reason);
    }
};

class value_error : public shapes_exception
{
  public:
    explicit value_error(const std::string& reason)
        : shapes_exception("value error")
    {
        set_reason(reason);
    }
};

}  // namespace exceptions
}  // namespace shapes
}  // namespace simo
