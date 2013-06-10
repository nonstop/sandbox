#ifndef JSON_SPIRIT
#define JSON_SPIRIT

//          Copyright John W. Wilkinson 2007 - 2011
// Distributed under the MIT License, see accompanying file LICENSE.txt
// json spirit version 4.05

#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <boost/io/ios_state.hpp>
#include <stdexcept>
#include <boost/cstdint.hpp> 
#include <boost/variant.hpp> 

//#define JSON_SPIRIT_VALUE_ENABLED
//#define JSON_SPIRIT_WVALUE_ENABLED
#define JSON_SPIRIT_MVALUE_ENABLED
//#define JSON_SPIRIT_WMVALUE_ENABLED

namespace json_spirit
{
enum Value_type{ obj_type, array_type, str_type, bool_type, int_type, real_type, null_type };

struct Null{};

template< class Config >    // Config determines whether the value uses std::string or std::wstring and
                            // whether JSON Objects are represented as vectors or maps
class Value_impl
{
public:

    typedef Config Config_type;
    typedef typename Config::String_type String_type;
    typedef typename Config::Object_type Object;
    typedef typename Config::Array_type Array;
    typedef typename String_type::const_pointer Const_str_ptr;  // eg const char*

    Value_impl();  // creates null value
    Value_impl( Const_str_ptr      value ); 
    Value_impl( const String_type& value );
    Value_impl( const Object&      value );
    Value_impl( const Array&       value );
    Value_impl( bool               value );
    Value_impl( int                value );
    Value_impl( boost::int64_t     value );
    Value_impl( boost::uint64_t    value );
    Value_impl( double             value );

    template< class Iter >
    Value_impl( Iter first, Iter last );    // constructor from containers, e.g. std::vector or std::list

    template< BOOST_VARIANT_ENUM_PARAMS( typename T ) >
    Value_impl( const boost::variant< BOOST_VARIANT_ENUM_PARAMS(T) >& variant ); // constructor for compatible variant types

    Value_impl( const Value_impl& other );

    bool operator==( const Value_impl& lhs ) const;

    Value_impl& operator=( const Value_impl& lhs );

    Value_type type() const;

    bool is_uint64() const;
    bool is_null() const;

    const String_type& get_str()    const;
    const Object&      get_obj()    const;
    const Array&       get_array()  const;
    bool               get_bool()   const;
    int                get_int()    const;
    boost::int64_t     get_int64()  const;
    boost::uint64_t    get_uint64() const;
    double             get_real()   const;

    Object& get_obj();
    Array&  get_array();

    template< typename T > T get_value() const;  // example usage: int    i = value.get_value< int >();
                                                 // or             double d = value.get_value< double >();

    static const Value_impl null;

private:

    void check_type( const Value_type vtype ) const;

    typedef boost::variant< boost::recursive_wrapper< Object >, boost::recursive_wrapper< Array >, 
                            String_type, bool, boost::int64_t, double, Null, boost::uint64_t > Variant;

    Variant v_;

    class Variant_converter_visitor : public boost::static_visitor< Variant > 
    {
    public:
     
          template< typename T, typename A, template< typename, typename > class Cont >
          Variant operator()( const Cont< T, A >& cont ) const 
          {
              return Array( cont.begin(), cont.end() );
          }
         
          Variant operator()( int i ) const 
          {
              return static_cast< boost::int64_t >( i );
          }
       
          template<class T>
          Variant operator()( const T& t ) const 
          {
              return t;
          }
    };
};

// vector objects

template< class Config >
struct Pair_impl
{
    typedef typename Config::String_type String_type;
    typedef typename Config::Value_type Value_type;

    Pair_impl()
    {
    }

    Pair_impl( const String_type& name, const Value_type& value );

    bool operator==( const Pair_impl& lhs ) const;

    String_type name_;
    Value_type value_;
};

#if defined( JSON_SPIRIT_VALUE_ENABLED ) || defined( JSON_SPIRIT_WVALUE_ENABLED )
template< class String >
struct Config_vector
{
    typedef String String_type;
    typedef Value_impl< Config_vector > Value_type;
    typedef Pair_impl < Config_vector > Pair_type;
    typedef std::vector< Value_type > Array_type;
    typedef std::vector< Pair_type > Object_type;

    static Value_type& add( Object_type& obj, const String_type& name, const Value_type& value )
    {
        obj.push_back( Pair_type( name , value ) );

        return obj.back().value_;
    }
            
    static String_type get_name( const Pair_type& pair )
    {
        return pair.name_;
    }
            
    static Value_type get_value( const Pair_type& pair )
    {
        return pair.value_;
    }
};
#endif

// typedefs for ASCII

#ifdef JSON_SPIRIT_VALUE_ENABLED
typedef Config_vector< std::string > Config;

typedef Config::Value_type  Value;
typedef Config::Pair_type   Pair;
typedef Config::Object_type Object;
typedef Config::Array_type  Array;
#endif

// typedefs for Unicode

#if defined( JSON_SPIRIT_WVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
typedef Config_vector< std::wstring > wConfig;

typedef wConfig::Value_type  wValue;
typedef wConfig::Pair_type   wPair;
typedef wConfig::Object_type wObject;
typedef wConfig::Array_type  wArray;
#endif

// map objects

#if defined( JSON_SPIRIT_MVALUE_ENABLED ) || defined( JSON_SPIRIT_WMVALUE_ENABLED )
template< class String >
struct Config_map
{
    typedef String String_type;
    typedef Value_impl< Config_map > Value_type;
    typedef std::vector< Value_type > Array_type;
    typedef std::map< String_type, Value_type > Object_type;
    typedef std::pair< String_type, Value_type > Pair_type;

    static Value_type& add( Object_type& obj, const String_type& name, const Value_type& value )
    {
        return obj[ name ] = value;
    }
            
    static String_type get_name( const Pair_type& pair )
    {
        return pair.first;
    }
            
    static Value_type get_value( const Pair_type& pair )
    {
        return pair.second;
    }
};
#endif

// typedefs for ASCII

#ifdef JSON_SPIRIT_MVALUE_ENABLED
typedef Config_map< std::string > mConfig;

typedef mConfig::Value_type  mValue;
typedef mConfig::Object_type mObject;
typedef mConfig::Array_type  mArray;
#endif

// typedefs for Unicode

#if defined( JSON_SPIRIT_WMVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
typedef Config_map< std::wstring > wmConfig;

typedef wmConfig::Value_type  wmValue;
typedef wmConfig::Object_type wmObject;
typedef wmConfig::Array_type  wmArray;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
//
// implementation

inline bool operator==( const Null&, const Null& )
{
    return true;
}

template< class Config >
const Value_impl< Config > Value_impl< Config >::null;

template< class Config >
Value_impl< Config >::Value_impl()
:   v_( Null() )
{
}

template< class Config >
Value_impl< Config >::Value_impl( const Const_str_ptr value )
:  v_( String_type( value ) )
{
}

template< class Config >
Value_impl< Config >::Value_impl( const String_type& value )
:   v_( value )
{
}

template< class Config >
Value_impl< Config >::Value_impl( const Object& value )
:   v_( value )
{
}

template< class Config >
Value_impl< Config >::Value_impl( const Array& value )
:   v_( value )
{
}

template< class Config >
Value_impl< Config >::Value_impl( bool value )
:   v_( value )
{
}

template< class Config >
Value_impl< Config >::Value_impl( int value )
:   v_( static_cast< boost::int64_t >( value ) )
{
}

template< class Config >
Value_impl< Config >::Value_impl( boost::int64_t value )
:   v_( value )
{
}

template< class Config >
Value_impl< Config >::Value_impl( boost::uint64_t value )
:   v_( value )
{
}

template< class Config >
Value_impl< Config >::Value_impl( double value )
:   v_( value )
{
}

template< class Config >
Value_impl< Config >::Value_impl( const Value_impl< Config >& other )
:   v_( other.v_ )
{
}

template< class Config >
template< class Iter >
Value_impl< Config >::Value_impl( Iter first, Iter last )
:   v_( Array( first, last ) )
{
}

template< class Config >
template< BOOST_VARIANT_ENUM_PARAMS( typename T ) >
Value_impl< Config >::Value_impl( const boost::variant< BOOST_VARIANT_ENUM_PARAMS(T) >& variant )
:   v_( boost::apply_visitor( Variant_converter_visitor(), variant) )
{
}

template< class Config >
Value_impl< Config >& Value_impl< Config >::operator=( const Value_impl& lhs )
{
    Value_impl tmp( lhs );

    std::swap( v_, tmp.v_ );

    return *this;
}

template< class Config >
bool Value_impl< Config >::operator==( const Value_impl& lhs ) const
{
    if( this == &lhs ) return true;

    if( type() != lhs.type() ) return false;

    return v_ == lhs.v_; 
}

template< class Config >
Value_type Value_impl< Config >::type() const
{
    if( is_uint64() )
    {
        return int_type;
    }

    return static_cast< Value_type >( v_.which() );
}

template< class Config >
bool Value_impl< Config >::is_uint64() const
{
    return v_.which() == null_type + 1;
}

template< class Config >
bool Value_impl< Config >::is_null() const
{
    return type() == null_type;
}

template< class Config >
void Value_impl< Config >::check_type( const Value_type vtype ) const
{
    if( type() != vtype ) 
    {
        std::ostringstream os;

        os << "value type is " << type() << " not " << vtype;

        throw std::runtime_error( os.str() );
    }
}

template< class Config >
const typename Config::String_type& Value_impl< Config >::get_str() const
{
    check_type( str_type );

    return *boost::get< String_type >( &v_ );
}

template< class Config >
const typename Value_impl< Config >::Object& Value_impl< Config >::get_obj() const
{
    check_type( obj_type );

    return *boost::get< Object >( &v_ );
}
 
template< class Config >
const typename Value_impl< Config >::Array& Value_impl< Config >::get_array() const
{
    check_type( array_type );

    return *boost::get< Array >( &v_ );
}
 
template< class Config >
bool Value_impl< Config >::get_bool() const
{
    check_type( bool_type );

    return boost::get< bool >( v_ );
}
 
template< class Config >
int Value_impl< Config >::get_int() const
{
    check_type( int_type );

    return static_cast< int >( get_int64() );
}

template< class Config >
boost::int64_t Value_impl< Config >::get_int64() const
{
    check_type( int_type );

    if( is_uint64() )
    {
        return static_cast< boost::int64_t >( get_uint64() );
    }

    return boost::get< boost::int64_t >( v_ );
}

template< class Config >
boost::uint64_t Value_impl< Config >::get_uint64() const
{
    check_type( int_type );

    if( !is_uint64() )
    {
        return static_cast< boost::uint64_t >( get_int64() );
    }

    return boost::get< boost::uint64_t >( v_ );
}

template< class Config >
double Value_impl< Config >::get_real() const
{
    if( type() == int_type )
    {
        return is_uint64() ? static_cast< double >( get_uint64() )
                           : static_cast< double >( get_int64() );
    }

    check_type( real_type );

    return boost::get< double >( v_ );
}

template< class Config >
typename Value_impl< Config >::Object& Value_impl< Config >::get_obj()
{
    check_type( obj_type );

    return *boost::get< Object >( &v_ );
}

template< class Config >
typename Value_impl< Config >::Array& Value_impl< Config >::get_array()
{
    check_type( array_type );

    return *boost::get< Array >( &v_ );
}

template< class Config >
Pair_impl< Config >::Pair_impl( const String_type& name, const Value_type& value )
:   name_( name )
,   value_( value )
{
}

template< class Config >
bool Pair_impl< Config >::operator==( const Pair_impl< Config >& lhs ) const
{
    if( this == &lhs ) return true;

    return ( name_ == lhs.name_ ) && ( value_ == lhs.value_ );
}

// converts a C string, ie. 8 bit char array, to a string object
//
template < class String_type >
String_type to_str( const char* c_str )
{
    String_type result;

    for( const char* p = c_str; *p != 0; ++p )
    {
        result += *p;
    }

    return result;
}

//

namespace internal_
{
    template< typename T >
    struct Type_to_type
    {
    };

    template< class Value > 
    int get_value( const Value& value, Type_to_type< int > )
    {
        return value.get_int();
    }
   
    template< class Value > 
    boost::int64_t get_value( const Value& value, Type_to_type< boost::int64_t > )
    {
        return value.get_int64();
    }
   
    template< class Value > 
    boost::uint64_t get_value( const Value& value, Type_to_type< boost::uint64_t > )
    {
        return value.get_uint64();
    }
   
    template< class Value > 
    double get_value( const Value& value, Type_to_type< double > )
    {
        return value.get_real();
    }
   
    template< class Value > 
    typename Value::String_type get_value( const Value& value, Type_to_type< typename Value::String_type > )
    {
        return value.get_str();
    }
   
    template< class Value > 
    typename Value::Array get_value( const Value& value, Type_to_type< typename Value::Array > )
    {
        return value.get_array();
    }
   
    template< class Value > 
    typename Value::Object get_value( const Value& value, Type_to_type< typename Value::Object > )
    {
        return value.get_obj();
    }
   
    template< class Value > 
    bool get_value( const Value& value, Type_to_type< bool > )
    {
        return value.get_bool();
    }
}

template< class Config >
template< typename T > 
T Value_impl< Config >::get_value() const
{
    return internal_::get_value( *this, internal_::Type_to_type< T >() );
}
// An Error_position exception is thrown by the "read_or_throw" functions below on finding an error.
// Note the "read_or_throw" functions are around 3 times slower than the standard functions "read" 
// functions that return a bool.
//
struct Error_position
{
    Error_position();
    Error_position( unsigned int line, unsigned int column, const std::string& reason );
    bool operator==( const Error_position& lhs ) const;
    unsigned int line_;
    unsigned int column_;
    std::string reason_;
};

inline Error_position::Error_position()
:   line_( 0 )
,   column_( 0 )
{
}

inline Error_position::Error_position( unsigned int line, unsigned int column, const std::string& reason )
:   line_( line )
,   column_( column )
,   reason_( reason )
{
}

inline bool Error_position::operator==( const Error_position& lhs ) const
{
    if( this == &lhs ) return true;

    return ( reason_ == lhs.reason_ ) &&
           ( line_   == lhs.line_ ) &&
           ( column_ == lhs.column_ ); 
}

#ifdef JSON_SPIRIT_VALUE_ENABLED
bool read( const std::string& s, Value& value );
bool read( std::istream& is,     Value& value );
bool read( std::string::const_iterator& begin, std::string::const_iterator end, Value& value );

void read_or_throw( const std::string& s, Value& value );  
void read_or_throw( std::istream& is,     Value& value );
void read_or_throw( std::string::const_iterator& begin, std::string::const_iterator end, Value& value );
#endif

#if defined( JSON_SPIRIT_WVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
bool read( const std::wstring& s, wValue& value );
bool read( std::wistream&  is,    wValue& value );
bool read( std::wstring::const_iterator& begin, std::wstring::const_iterator end, wValue& value );    

void read_or_throw( const std::wstring& s, wValue& value );
void read_or_throw( std::wistream& is,     wValue& value );
void read_or_throw( std::wstring::const_iterator& begin, std::wstring::const_iterator end, wValue& value );
#endif

#ifdef JSON_SPIRIT_MVALUE_ENABLED
bool read( const std::string& s, mValue& value );
bool read( std::istream& is,     mValue& value );
bool read( std::string::const_iterator& begin, std::string::const_iterator end, mValue& value );

void read_or_throw( const std::string& s, mValue& value );  
void read_or_throw( std::istream& is,     mValue& value );
void read_or_throw( std::string::const_iterator& begin, std::string::const_iterator end, mValue& value );
#endif

#if defined( JSON_SPIRIT_WMVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
bool read( const std::wstring& s, wmValue& value );
bool read( std::wistream& is,     wmValue& value );
bool read( std::wstring::const_iterator& begin, std::wstring::const_iterator end, wmValue& value );    

void read_or_throw( const std::wstring& s, wmValue& value );
void read_or_throw( std::wistream& is,     wmValue& value );
void read_or_throw( std::wstring::const_iterator& begin, std::wstring::const_iterator end, wmValue& value );
#endif
template< class Obj_t, class Map_t >
void obj_to_map( const Obj_t& obj, Map_t& mp_obj )
{
    mp_obj.clear();

    for( typename Obj_t::const_iterator i = obj.begin(); i != obj.end(); ++i )
    {
        mp_obj[ i->name_ ] = i->value_;
    }
}

template< class Obj_t, class Map_t >
void map_to_obj( const Map_t& mp_obj, Obj_t& obj )
{
    obj.clear();

    for( typename Map_t::const_iterator i = mp_obj.begin(); i != mp_obj.end(); ++i )
    {
        obj.push_back( typename Obj_t::value_type( i->first, i->second ) );
    }
}

#ifdef JSON_SPIRIT_VALUE_ENABLED
typedef std::map< std::string, Value > Mapped_obj;
#endif

#if defined( JSON_SPIRIT_WVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
typedef std::map< std::wstring, wValue > wMapped_obj;
#endif

template< class Object_type, class String_type >
const typename Object_type::value_type::Value_type& find_value( const Object_type& obj, const String_type& name )
{
    for( typename Object_type::const_iterator i = obj.begin(); i != obj.end(); ++i )
    {
        if( i->name_ == name )
        {
            return i->value_;
        }
    }

    return Object_type::value_type::Value_type::null;
}

#ifdef JSON_SPIRIT_VALUE_ENABLED
void         write( const Value&  value, std::ostream&  os, unsigned int options = 0 );
std::string  write( const Value&  value, unsigned int options = 0 );
#endif

#ifdef JSON_SPIRIT_MVALUE_ENABLED
void         write( const mValue& value, std::ostream&  os, unsigned int options = 0 );
std::string  write( const mValue& value, unsigned int options = 0 );
#endif

#if defined( JSON_SPIRIT_WVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
void         write( const wValue&  value, std::wostream& os, unsigned int options = 0 );
std::wstring write( const wValue&  value, unsigned int options = 0 );
#endif

#if defined( JSON_SPIRIT_WMVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
void         write( const wmValue& value, std::wostream& os, unsigned int options = 0 );
std::wstring write( const wmValue& value, unsigned int options = 0 );
#endif

// these "formatted" versions of the "write" functions are the equivalent of the above functions
// with option "pretty_print"

#ifdef JSON_SPIRIT_VALUE_ENABLED
void         write_formatted( const Value& value, std::ostream&  os );
std::string  write_formatted( const Value& value );
#endif
#ifdef JSON_SPIRIT_MVALUE_ENABLED
void         write_formatted( const mValue& value, std::ostream&  os );
std::string  write_formatted( const mValue& value );
#endif

#if defined( JSON_SPIRIT_WVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
void         write_formatted( const wValue& value, std::wostream& os );
std::wstring write_formatted( const wValue& value );
#endif
#if defined( JSON_SPIRIT_WMVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
void         write_formatted( const wmValue& value, std::wostream& os );
std::wstring write_formatted( const wmValue& value );
#endif
enum Output_options{ pretty_print = 0x01,   // Add whitespace to format the output nicely.

                     raw_utf8 = 0x02,       // This prevents non-printable characters from being escapted using "\uNNNN" notation.
                                            // Note, this is an extension to the JSON standard. It disables the escaping of
                                            // non-printable characters allowing UTF-8 sequences held in 8 bit char strings
                                            // to pass through unaltered.

                     remove_trailing_zeros = 0x04,
                                            // outputs e.g. "1.200000000000000" as "1.2"
                     single_line_arrays = 0x08,
                                            // pretty printing except that arrays printed on single lines unless they contain
                                            // composite elements, i.e. objects or arrays
                   };
inline char to_hex_char( unsigned int c )
{
    assert( c <= 0xF );

    const char ch = static_cast< char >( c );

    if( ch < 10 ) return '0' + ch;

    return 'A' - 10 + ch;
}

template< class String_type >
String_type non_printable_to_string( unsigned int c )
{
    String_type result( 6, '\\' );

    result[1] = 'u';

    result[ 5 ] = to_hex_char( c & 0x000F ); c >>= 4;
    result[ 4 ] = to_hex_char( c & 0x000F ); c >>= 4;
    result[ 3 ] = to_hex_char( c & 0x000F ); c >>= 4;
    result[ 2 ] = to_hex_char( c & 0x000F );

    return result;
}

template< typename Char_type, class String_type >
bool add_esc_char( Char_type c, String_type& s )
{
    switch( c )
    {
        case '"':  s += to_str< String_type >( "\\\"" ); return true;
        case '\\': s += to_str< String_type >( "\\\\" ); return true;
        case '\b': s += to_str< String_type >( "\\b"  ); return true;
        case '\f': s += to_str< String_type >( "\\f"  ); return true;
        case '\n': s += to_str< String_type >( "\\n"  ); return true;
        case '\r': s += to_str< String_type >( "\\r"  ); return true;
        case '\t': s += to_str< String_type >( "\\t"  ); return true;
    }

    return false;
}

template< class String_type >
String_type add_esc_chars( const String_type& s, bool raw_utf8 )
{
    typedef typename String_type::const_iterator Iter_type;
    typedef typename String_type::value_type     Char_type;

    String_type result;

    const Iter_type end( s.end() );

    for( Iter_type i = s.begin(); i != end; ++i )
    {
        const Char_type c( *i );

        if( add_esc_char( c, result ) ) continue;

        if( raw_utf8 )
        {
            result += c;
        }
        else
        {
            const wint_t unsigned_c( ( c >= 0 ) ? c : 256 + c );

            if( iswprint( unsigned_c ) )
            {
                result += c;
            }
            else
            {
                result += non_printable_to_string< String_type >( unsigned_c );
            }
        }
    }

    return result;
}

template< class Ostream >
void append_double( Ostream& os, const double d, const int precision )
{
    os << std::showpoint << std::setprecision( precision ) << d;
}

template< class String_type >
void erase_and_extract_exponent( String_type& str, String_type& exp )
{
    const typename String_type::size_type exp_start= str.find( 'e' );

    if( exp_start != String_type::npos )
    {
        exp = str.substr( exp_start );
        str.erase( exp_start );
    }
}

template< class String_type >
typename String_type::size_type find_first_non_zero( const String_type& str )
{
    typename String_type::size_type result = str.size() - 1;

    for( ; result != 0; --result )
    {
        if( str[ result ] != '0' )
        {
            break;
        }
    }

    return result;
}

template< class String_type >
void remove_trailing( String_type& str )
{
    String_type exp;

    erase_and_extract_exponent( str, exp );

    const typename String_type::size_type first_non_zero = find_first_non_zero( str );

    if( first_non_zero != 0 )
    {
        const int offset = str[first_non_zero] == '.' ? 2 : 1;  // note zero digits following a decimal point is non standard
        str.erase( first_non_zero + offset );
    }

    str += exp;
}

// this class generates the JSON text,
// it keeps track of the indentation level etc.
//
template< class Value_type, class Ostream_type >
class Generator
{
    typedef typename Value_type::Config_type Config_type;
    typedef typename Config_type::String_type String_type;
    typedef typename Config_type::Object_type Object_type;
    typedef typename Config_type::Array_type Array_type;
    typedef typename String_type::value_type Char_type;
    typedef typename Object_type::value_type Obj_member_type;

public:

    Generator( const Value_type& value, Ostream_type& os, unsigned int options )
    :   os_( os )
    ,   indentation_level_( 0 )
    ,   pretty_( ( options & pretty_print ) != 0 || ( options & single_line_arrays ) != 0 )
    ,   raw_utf8_( ( options & raw_utf8 ) != 0 )
    ,   remove_trailing_zeros_( ( options & remove_trailing_zeros ) != 0 )
    ,   single_line_arrays_( ( options & single_line_arrays ) != 0 )
    ,   ios_saver_( os )
    {
        output( value );
    }

private:

    void output( const Value_type& value )
    {
        switch( value.type() )
        {
            case obj_type:   output( value.get_obj() );   break;
            case array_type: output( value.get_array() ); break;
            case str_type:   output( value.get_str() );   break;
            case bool_type:  output( value.get_bool() );  break;
            case real_type:  output( value.get_real() );  break;
            case int_type:   output_int( value );         break;
            case null_type:  os_ << "null";               break;
            default: assert( false );
        }
    }

    void output( const Object_type& obj )
    {
        output_array_or_obj( obj, '{', '}' );
    }

    void output( const Obj_member_type& member )
    {
        output( Config_type::get_name( member ) ); space(); 
        os_ << ':'; space(); 
        output( Config_type::get_value( member ) );
    }

    void output_int( const Value_type& value )
    {
        if( value.is_uint64() )
        {
            os_ << value.get_uint64();
        }
        else
        {
           os_ << value.get_int64();
        }
    }

    void output( const String_type& s )
    {
        os_ << '"' << add_esc_chars( s, raw_utf8_ ) << '"';
    }

    void output( bool b )
    {
        os_ << to_str< String_type >( b ? "true" : "false" );
    }

    void output( double d )
    {
        if( remove_trailing_zeros_ )
        {
            std::basic_ostringstream< Char_type > os;

            append_double( os, d, 16 );  // note precision is 16 so that we get some trailing space that we can remove,
                                         // otherwise, 0.1234 gets converted to "0.12399999..."

            String_type str = os.str();

            remove_trailing( str );

            os_ << str;
        }
        else
        {
            append_double( os_, d, 17 );
        }
    }

    static bool contains_composite_elements( const Array_type& arr )
    {
        for( typename Array_type::const_iterator i = arr.begin(); i != arr.end(); ++i )
        {
            const Value_type& val = *i;

            if( val.type() == obj_type ||
                val.type() == array_type )
            {
                return true;
            }
        }

        return false;
    }

    template< class Iter >
    void output_composite_item( Iter i, Iter last )
    {
        output( *i );

        if( ++i != last )
        {
            os_ << ',';
        }
    }

    void output( const Array_type& arr )
    {
        if( single_line_arrays_ && !contains_composite_elements( arr )  )
        {
            os_ << '['; space();
           
            for( typename Array_type::const_iterator i = arr.begin(); i != arr.end(); ++i )
            {
                output_composite_item( i, arr.end() );

                space();
            }

            os_ << ']';
        }
        else
        {
            output_array_or_obj( arr, '[', ']' );
        }
    }

    template< class T >
    void output_array_or_obj( const T& t, Char_type start_char, Char_type end_char )
    {
        os_ << start_char; new_line();

        ++indentation_level_;
        
        for( typename T::const_iterator i = t.begin(); i != t.end(); ++i )
        {
            indent();

            output_composite_item( i, t.end() );

            new_line();
        }

        --indentation_level_;

        indent(); os_ << end_char;
    }
    
    void indent()
    {
        if( !pretty_ ) return;

        for( int i = 0; i < indentation_level_; ++i )
        { 
            os_ << "    ";
        }
    }

    void space()
    {
        if( pretty_ ) os_ << ' ';
    }

    void new_line()
    {
        if( pretty_ ) os_ << '\n';
    }

    Generator& operator=( const Generator& ); // to prevent "assignment operator could not be generated" warning

    Ostream_type& os_;
    int indentation_level_;
    bool pretty_;
    bool raw_utf8_;
    bool remove_trailing_zeros_;
    bool single_line_arrays_;
    boost::io::basic_ios_all_saver< Char_type > ios_saver_;  // so that ostream state is reset after control is returned to the caller
};

// writes JSON Value to a stream, e.g.
//
// write_stream( value, os, pretty_print );
//
template< class Value_type, class Ostream_type >
void write_stream( const Value_type& value, Ostream_type& os, unsigned int options = 0 )
{
    os << std::dec;
    Generator< Value_type, Ostream_type >( value, os, options );
}

// writes JSON Value to a stream, e.g.
//
// const string json_str = write( value, pretty_print );
//
template< class Value_type >
typename Value_type::String_type write_string( const Value_type& value, unsigned int options = 0 )
{
    typedef typename Value_type::String_type::value_type Char_type;

    std::basic_ostringstream< Char_type > os;

    write_stream( value, os, options );

    return os.str();
}
} // json_spirit

#endif // JSON_SPIRIT
