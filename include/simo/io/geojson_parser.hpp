#pragma once

#include <ciso646>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <sstream>

namespace simo
{
namespace shapes
{
namespace io
{

// Exception for GeoJSON parsing errors
class geojson_parse_error : public std::runtime_error
{
  public:
    explicit geojson_parse_error(const std::string& msg)
        : std::runtime_error(msg) {}
};

// Forward declaration
class geojson_value;

// Lightweight JSON value representation optimized for GeoJSON
class geojson_value
{
  public:
    enum class type_t
    {
        NULL_TYPE,
        STRING,
        NUMBER,
        ARRAY,
        OBJECT
    };

  private:
    type_t type_;

    // Use pointer-based storage to avoid large union
    std::unique_ptr<std::string> string_val_;
    double number_val_;
    std::unique_ptr<std::vector<geojson_value>> array_val_;
    std::unique_ptr<std::unordered_map<std::string, geojson_value>> object_val_;

  public:
    // Constructors
    geojson_value()
        : type_(type_t::NULL_TYPE), number_val_(0.0) {}

    explicit geojson_value(const std::string& s)
        : type_(type_t::STRING), string_val_(new std::string(s)), number_val_(0.0) {}

    explicit geojson_value(double n)
        : type_(type_t::NUMBER), number_val_(n) {}

    explicit geojson_value(std::vector<geojson_value>&& arr)
        : type_(type_t::ARRAY), number_val_(0.0), array_val_(new std::vector<geojson_value>(std::move(arr))) {}

    explicit geojson_value(std::unordered_map<std::string, geojson_value>&& obj)
        : type_(type_t::OBJECT), number_val_(0.0), object_val_(new std::unordered_map<std::string, geojson_value>(std::move(obj))) {}

    // Move constructor and assignment
    geojson_value(geojson_value&& other) noexcept
        : type_(other.type_),
          string_val_(std::move(other.string_val_)),
          number_val_(other.number_val_),
          array_val_(std::move(other.array_val_)),
          object_val_(std::move(other.object_val_))
    {
        other.type_ = type_t::NULL_TYPE;
    }

    geojson_value& operator=(geojson_value&& other) noexcept
    {
        if (this != &other)
        {
            type_ = other.type_;
            string_val_ = std::move(other.string_val_);
            number_val_ = other.number_val_;
            array_val_ = std::move(other.array_val_);
            object_val_ = std::move(other.object_val_);
            other.type_ = type_t::NULL_TYPE;
        }
        return *this;
    }

    // Delete copy constructor and assignment (move-only for efficiency)
    geojson_value(const geojson_value&) = delete;
    geojson_value& operator=(const geojson_value&) = delete;

    // Type queries
    type_t type() const noexcept { return type_; }
    bool is_null() const noexcept { return type_ == type_t::NULL_TYPE; }
    bool is_string() const noexcept { return type_ == type_t::STRING; }
    bool is_number() const noexcept { return type_ == type_t::NUMBER; }
    bool is_array() const noexcept { return type_ == type_t::ARRAY; }
    bool is_object() const noexcept { return type_ == type_t::OBJECT; }

    // Access methods with bounds checking
    const geojson_value& at(const std::string& key) const
    {
        if (type_ != type_t::OBJECT)
        {
            throw geojson_parse_error("not an object");
        }
        auto it = object_val_->find(key);
        if (it == object_val_->end())
        {
            throw std::out_of_range("key not found: " + key);
        }
        return it->second;
    }

    const geojson_value& operator[](size_t index) const
    {
        if (type_ != type_t::ARRAY)
        {
            throw geojson_parse_error("not an array");
        }
        if (index >= array_val_->size())
        {
            throw std::out_of_range("array index out of range");
        }
        return (*array_val_)[index];
    }

    bool has_key(const std::string& key) const
    {
        if (type_ != type_t::OBJECT)
        {
            return false;
        }
        return object_val_->find(key) != object_val_->end();
    }

    size_t size() const
    {
        if (type_ == type_t::ARRAY)
        {
            return array_val_->size();
        }
        if (type_ == type_t::OBJECT)
        {
            return object_val_->size();
        }
        return 0;
    }

    bool empty() const
    {
        return size() == 0;
    }

    // Type conversions
    std::string as_string() const
    {
        if (type_ != type_t::STRING)
        {
            throw geojson_parse_error("value is not a string");
        }
        return *string_val_;
    }

    double as_number() const
    {
        if (type_ != type_t::NUMBER)
        {
            throw geojson_parse_error("value is not a number");
        }
        return number_val_;
    }

    // Optimized conversion for coordinate arrays (common case in GeoJSON)
    std::vector<double> as_double_array() const
    {
        if (type_ != type_t::ARRAY)
        {
            throw geojson_parse_error("value is not an array");
        }

        std::vector<double> result;
        result.reserve(array_val_->size());

        for (const auto& val : *array_val_)
        {
            if (!val.is_number())
            {
                throw geojson_parse_error("array element is not a number");
            }
            result.push_back(val.as_number());
        }

        return result;
    }

    // Array access for iteration
    const std::vector<geojson_value>& as_array() const
    {
        if (type_ != type_t::ARRAY)
        {
            throw geojson_parse_error("value is not an array");
        }
        return *array_val_;
    }
};

// Lightweight JSON parser optimized for GeoJSON
class geojson_parser
{
  private:
    const char* pos_;
    const char* end_;

    // Skip whitespace
    void skip_whitespace()
    {
        while (pos_ < end_ && std::isspace(static_cast<unsigned char>(*pos_)))
        {
            ++pos_;
        }
    }

    // Parse a string
    std::string parse_string()
    {
        if (pos_ >= end_ || *pos_ != '"')
        {
            throw geojson_parse_error("expected '\"'");
        }
        ++pos_; // skip opening quote

        std::string result;
        while (pos_ < end_)
        {
            char c = *pos_++;

            if (c == '"')
            {
                return result;
            }
            else if (c == '\\')
            {
                if (pos_ >= end_)
                {
                    throw geojson_parse_error("unexpected end in string escape");
                }
                char escaped = *pos_++;
                switch (escaped)
                {
                    case '"':
                    case '\\':
                    case '/':
                        result += escaped;
                        break;
                    case 'b':
                        result += '\b';
                        break;
                    case 'f':
                        result += '\f';
                        break;
                    case 'n':
                        result += '\n';
                        break;
                    case 'r':
                        result += '\r';
                        break;
                    case 't':
                        result += '\t';
                        break;
                    default:
                        throw geojson_parse_error("invalid escape sequence");
                }
            }
            else
            {
                result += c;
            }
        }

        throw geojson_parse_error("unterminated string");
    }

    // Parse a number
    double parse_number()
    {
        const char* start = pos_;

        // Optional minus
        if (pos_ < end_ && *pos_ == '-')
        {
            ++pos_;
        }

        // Integer part
        if (pos_ >= end_ || !std::isdigit(static_cast<unsigned char>(*pos_)))
        {
            throw geojson_parse_error("invalid number");
        }

        while (pos_ < end_ && std::isdigit(static_cast<unsigned char>(*pos_)))
        {
            ++pos_;
        }

        // Fractional part
        if (pos_ < end_ && *pos_ == '.')
        {
            ++pos_;
            if (pos_ >= end_ || !std::isdigit(static_cast<unsigned char>(*pos_)))
            {
                throw geojson_parse_error("invalid number: expected digit after '.'");
            }
            while (pos_ < end_ && std::isdigit(static_cast<unsigned char>(*pos_)))
            {
                ++pos_;
            }
        }

        // Exponent part
        if (pos_ < end_ && (*pos_ == 'e' || *pos_ == 'E'))
        {
            ++pos_;
            if (pos_ < end_ && (*pos_ == '+' || *pos_ == '-'))
            {
                ++pos_;
            }
            if (pos_ >= end_ || !std::isdigit(static_cast<unsigned char>(*pos_)))
            {
                throw geojson_parse_error("invalid number: expected digit in exponent");
            }
            while (pos_ < end_ && std::isdigit(static_cast<unsigned char>(*pos_)))
            {
                ++pos_;
            }
        }

        // Convert to double
        std::string num_str(start, pos_);
        return std::stod(num_str);
    }

    // Parse an array
    geojson_value parse_array()
    {
        if (pos_ >= end_ || *pos_ != '[')
        {
            throw geojson_parse_error("expected '['");
        }
        ++pos_; // skip '['

        skip_whitespace();

        std::vector<geojson_value> arr;

        // Empty array
        if (pos_ < end_ && *pos_ == ']')
        {
            ++pos_;
            return geojson_value(std::move(arr));
        }

        while (true)
        {
            arr.push_back(parse_value());

            skip_whitespace();

            if (pos_ >= end_)
            {
                throw geojson_parse_error("unexpected end in array");
            }

            if (*pos_ == ']')
            {
                ++pos_;
                break;
            }

            if (*pos_ != ',')
            {
                throw geojson_parse_error("expected ',' or ']' in array");
            }
            ++pos_; // skip ','

            skip_whitespace();
        }

        return geojson_value(std::move(arr));
    }

    // Parse an object
    geojson_value parse_object()
    {
        if (pos_ >= end_ || *pos_ != '{')
        {
            throw geojson_parse_error("expected '{'");
        }
        ++pos_; // skip '{'

        skip_whitespace();

        std::unordered_map<std::string, geojson_value> obj;

        // Empty object
        if (pos_ < end_ && *pos_ == '}')
        {
            ++pos_;
            return geojson_value(std::move(obj));
        }

        while (true)
        {
            // Parse key
            skip_whitespace();

            if (pos_ >= end_ || *pos_ != '"')
            {
                throw geojson_parse_error("expected string key in object");
            }

            std::string key = parse_string();

            // Parse colon
            skip_whitespace();

            if (pos_ >= end_ || *pos_ != ':')
            {
                throw geojson_parse_error("expected ':' after object key");
            }
            ++pos_; // skip ':'

            // Parse value
            skip_whitespace();
            obj.emplace(std::move(key), parse_value());

            // Check for continuation
            skip_whitespace();

            if (pos_ >= end_)
            {
                throw geojson_parse_error("unexpected end in object");
            }

            if (*pos_ == '}')
            {
                ++pos_;
                break;
            }

            if (*pos_ != ',')
            {
                throw geojson_parse_error("expected ',' or '}' in object");
            }
            ++pos_; // skip ','
        }

        return geojson_value(std::move(obj));
    }

    // Parse a value (recursive)
    geojson_value parse_value()
    {
        skip_whitespace();

        if (pos_ >= end_)
        {
            throw geojson_parse_error("unexpected end of input");
        }

        char c = *pos_;

        if (c == '{')
        {
            return parse_object();
        }
        else if (c == '[')
        {
            return parse_array();
        }
        else if (c == '"')
        {
            return geojson_value(parse_string());
        }
        else if (c == '-' || std::isdigit(static_cast<unsigned char>(c)))
        {
            return geojson_value(parse_number());
        }
        else if (pos_ + 4 <= end_ && std::strncmp(pos_, "null", 4) == 0)
        {
            pos_ += 4;
            return geojson_value();
        }
        else if (pos_ + 4 <= end_ && std::strncmp(pos_, "true", 4) == 0)
        {
            pos_ += 4;
            return geojson_value(1.0); // Use 1.0 for true (GeoJSON doesn't use booleans in coordinates)
        }
        else if (pos_ + 5 <= end_ && std::strncmp(pos_, "false", 5) == 0)
        {
            pos_ += 5;
            return geojson_value(0.0); // Use 0.0 for false
        }
        else
        {
            throw geojson_parse_error(std::string("unexpected character: ") + c);
        }
    }

  public:
    static geojson_value parse(const std::string& json)
    {
        if (json.empty())
        {
            throw geojson_parse_error("empty JSON string");
        }

        geojson_parser parser;
        parser.pos_ = json.data();
        parser.end_ = json.data() + json.size();

        geojson_value result = parser.parse_value();

        parser.skip_whitespace();

        if (parser.pos_ != parser.end_)
        {
            throw geojson_parse_error("unexpected characters after JSON value");
        }

        return result;
    }
};

}  // namespace io
}  // namespace shapes
}  // namespace simo
