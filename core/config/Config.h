/**
 * Read configuration file
 *
 * @brief This class is mainly used for reading configuration file,
 * originally written by David_xtd (which is available from
 * https://blog.csdn.net/david_xtd/article/details/9320549)
 *
 * @author David_xtd
 *
 * Improvements and optimizations have been added by:
 * @author Yiting Zhang & Yuxuan Long
 *
 * @date 06/12/2019
 *
 * \file Config.h
 *
 */

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#pragma once  
  
#include <string>  
#include <map>  
#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <utility>

class Config {
// Data  
protected:  
    std::string m_Delimiter;  //!< separator between key and value  
    std::string m_Comment;    //!< separator between value and comments  
    std::map<std::string,std::string> m_Contents;  //!< extracted keys and values  
  
    typedef std::map<std::string,std::string>::iterator mapi;  
    typedef std::map<std::string,std::string>::const_iterator mapci;  
    // Methods  
public:  
  
    explicit Config( const std::string& filename,std::string delimiter = "=",std::string comment = "#" );
    Config();  
    template<class T> T Read( const std::string& in_key ) const;  //!<Search for key and read value or optional default value, call as read<T>  
    template<class T> T Read( const std::string& in_key, const T& in_value ) const;  
    template<class T> bool ReadInto( T& out_var, const std::string& in_key ) const;  
    template<class T>  
    bool ReadInto( T& out_var, const std::string& in_key, const T& in_value ) const;  
    static bool FileExist(const std::string& filename);
    void ReadFile(const std::string& filename,std::string delimiter = "=",std::string comment = "#" );
  
    // Check whether key exists in configuration  
    bool KeyExists( const std::string& in_key ) const;  
  
    // Modify keys and values  
    template<class T> void Add( const std::string& in_key, const T& in_value );  
    void Remove( const std::string& in_key );  
  
    // Check or change configuration syntax  
    std::string GetDelimiter() const { return m_Delimiter; }  
    std::string GetComment() const { return m_Comment; }  
    std::string SetDelimiter( const std::string& in_s )  
    { std::string old = m_Delimiter;  m_Delimiter = in_s;  return old; }    
    std::string SetComment( const std::string& in_s )  
    { std::string old = m_Comment;  m_Comment =  in_s;  return old; }  
  
    // Write or read configuration  
    friend std::ostream& operator<<( std::ostream& os, const Config& cf );  
    friend std::istream& operator>>( std::istream& is, Config& cf );  
  
protected:  
    template<class T> static std::string T_as_string( const T& t );  
    template<class T> static T string_as_T( const std::string& s );  
    static void Trim( std::string& inout_s );  
  
  
    // Exception types  
public:  
    struct File_not_found {  
        std::string filename;  
        explicit File_not_found( std::string  filename_ = std::string() )
            : filename(std::move(filename_)) {} };
        struct Key_not_found {  // thrown only by T read(key) variant of read()  
            std::string key;  
            explicit Key_not_found( std::string  key_ = std::string() )
                : key(std::move(key_)) {} };
};  
  
  
/* static */  
template<class T>  
std::string Config::T_as_string( const T& t )  
{  
    // Convert from a T to a string  
    // Type T must support << operator  
    std::ostringstream ost;  
    ost << t;  
    return ost.str();  
}  
  
  
/* static */  
template<class T>  
T Config::string_as_T( const std::string& s )  
{  
    // Convert from a string to a T  
    // Type T must support >> operator  
    T t;  
    std::istringstream ist(s);  
    ist >> t;  
    return t;  
}  
  
  
/* static */  
template<>  
inline std::string Config::string_as_T<std::string>( const std::string& s )  
{  
    // Convert from a string to a string  
    // In other words, do nothing  
    return s;  
}  
  
  
/* static */  
template<>  
inline bool Config::string_as_T<bool>( const std::string& s )  
{  
    // Convert from a string to a bool  
    // Interpret "false", "F", "no", "n", "0" as false  
    // Interpret "true", "T", "yes", "y", "1", "-1", or anything else as true  
    bool b = true;  
    std::string sup = s;  
    for( std::string::iterator p = sup.begin(); p != sup.end(); ++p )
        *p = toupper(*p);  // make string all caps
    if( sup==std::string("FALSE") || sup==std::string("F") ||  
        sup==std::string("NO") || sup==std::string("N") ||  
        sup==std::string("0") || sup==std::string("NONE") )  
        b = false;  
    return b;  
}  
  
  
template<class T>  
T Config::Read( const std::string& key ) const  
{  
    // Read the value corresponding to key  
    auto p = m_Contents.find(key);
    if( p == m_Contents.end() ) throw Key_not_found(key);  
    return string_as_T<T>( p->second );  
}  
  
  
template<class T>  
T Config::Read( const std::string& key, const T& value ) const  
{  
    // Return the value corresponding to key or given default value  
    // if key is not found  
    auto p = m_Contents.find(key);
    if( p == m_Contents.end() ) return value;  
    return string_as_T<T>( p->second );  
}  
  
  
template<class T>  
bool Config::ReadInto( T& var, const std::string& key ) const  
{  
    // Get the value corresponding to key and store in var  
    // Return true if key is found  
    // Otherwise leave var untouched  
    auto p = m_Contents.find(key);
    bool found = ( p != m_Contents.end() );  
    if( found ) var = string_as_T<T>( p->second );  
    return found;  
}  
  
  
template<class T>  
bool Config::ReadInto( T& var, const std::string& key, const T& value ) const  
{  
    // Get the value corresponding to key and store in var  
    // Return true if key is found  
    // Otherwise set var to given default  
    auto p = m_Contents.find(key);
    bool found = ( p != m_Contents.end() );  
    if( found )  
        var = string_as_T<T>( p->second );  
    else  
        var = value;  
    return found;  
}  
  
  
template<class T>  
void Config::Add( const std::string& in_key, const T& value )  
{  
    // Add a key with given value  
    std::string v = T_as_string( value );  
    std::string key=in_key;  
    Trim(key);
    Trim(v);
    m_Contents[key] = v;  
}


#endif //PROJECT_CONFIG_H
