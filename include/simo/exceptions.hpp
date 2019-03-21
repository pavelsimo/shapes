#pragma once

#include <ciso646>
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
 *
 * @since 0.0.1
 */
class ShapesException : public std::exception
{
  public:
    /*!
     * @brief creates a shapes exception
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    explicit ShapesException(const char* reason)
        : m_reason(reason) {}

    /*!
     * @brief returns the exception reason
     * @return a string with the exception reason
     *
     * @since 0.0.1
     */
    const char* what() const noexcept override
    {
        return m_reason.c_str();
    }

  protected:
    /*!
     * @brief set the exception reason
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    void set_reason(const std::string& reason)
    {
        m_reason.append(": ");
        m_reason.append(reason);
    }

  private:
    std::string m_reason{};
};

/*!
 * @brief exception thrown when an error has been found while parsing
 *
 * @since 0.0.1
 */
class ParseError : public ShapesException
{
  public:
    /*!
     * @brief creates a parse error with the given reason
     * @param reason the reason message
     *
     * @since 0.0.1
     */
    explicit ParseError(const std::string& reason)
        : ShapesException("parse error")
    {
        set_reason(reason);
    }
};

/*!
 * @brief exception thrown when method or routine is not implemented
 *
 * @since 0.0.1
 */
class NotImplementedError : public ShapesException
{
  public:

    /*!
     * @brief creates a not implemented error exception
     *
     * @since 0.0.1
     */
    NotImplementedError()
        : ShapesException("not implemented error")
    {
    }

    /*!
     * @brief creates a not implemented error exception
     *
     * @param reason the reason message
     *
     * @since 0.0.1
     */
    explicit NotImplementedError(const std::string& reason)
        : ShapesException("not implemented error")
    {
        set_reason(reason);
    }
};

/*!
 * @brief exception thrown when a value error is found
 *
 * @since 0.0.1
 */
class ValueError : public ShapesException
{
  public:

    /*!
     * @brief creates a value error exception
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    explicit ValueError(const std::string& reason)
        : ShapesException("value error")
    {
        set_reason(reason);
    }
};

}  // namespace exceptions
}  // namespace shapes
}  // namespace simo
