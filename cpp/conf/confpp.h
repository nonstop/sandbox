#ifndef CONFPP_H_
#define CONFPP_H_

#include <string>
#include <map>
#include <stdexcept>
#include <sstream>
#include <fstream>

#include <iostream>
#define TRACE(x) std::cout << __FILE__ << ":" << __LINE__ << " [" << x << "] " << std::endl
#define TRACE2(x, y) std::cout << __FILE__ << ":" << __LINE__ << " " << x << ": [" << y << "] " << std::endl


namespace confpp
{

void operator<<(int &val, const std::string &str)
{
    val = atoi(str.c_str());
}

void operator<<(double &val, const std::string &str)
{
    val = atof(str.c_str());
}

void operator<<(std::string &val, const std::string &str)
{
    val = str;
}

const int confLineSize = 128;

class ConfException
    : public std::logic_error
{
public:
    ConfException(const std::string & msg)
        : std::logic_error(msg)
    {}
    virtual ~ConfException() throw()
    {}
};

class ConfigFile
{
    typedef std::map<std::string, std::string> ConfValues;
    typedef ConfValues::iterator ConfValuesIter;
    typedef ConfValues::const_iterator ConfValuesConstIter;
public:
    ConfigFile(const std::string & fileName)
    {
        std::ifstream str(fileName.c_str());
        if (!str.is_open())
        {
            std::string msg("can't open file: ");
            msg += fileName;
            throw ConfException(msg);
        }

        while (!str.eof())
        {
            char buff[confLineSize + 1];
            str.getline(buff, confLineSize);
            std::string pair(buff);
            trimLeft(pair);
            processLine(pair);
        }
    }
    
    template<typename T>
    T toType(const std::string &str)
    {
        T tmp;
        tmp << str;
        return tmp;
    }
    template<typename T>
    T get(const std::string &str)
    {
        ConfValuesIter it = values.find(str);
        if (it == values.end())
            return T();
        
        return toType<T>(it->second);
    }
    template<typename T>
    void get(const std::string & name, T & vector)
    {
        std::string& value = values[name];
        TRACE(value);
        
        std::string::size_type pos = 0;
        std::string tmp;
        
        // States
        const int ready = 0;
        const int reading = 1;
        const int finished = 2;
        const int readingInQuotes = 3;
        int state = 0;
        char currentQuoteChar = 0;
        while (state != finished)
        {
            char c = value[pos++];
            TRACE2("status :", state);
            TRACE2("c :", c);
            if (state == ready)
            {
                if (c == 0)
                {
                    state = finished;
                    continue;
                }
                if ( (c == '"') || (c == '\'') )
                {
                    currentQuoteChar = c;
                    TRACE2("currentQuoteChar :", c);
                    state = readingInQuotes;
                }
                else if (c == ' ')
                {
                }
                else
                {
                    tmp = c;
                    state = reading;
                }
            }
            else if (state == reading)
            {
                if (c == ' ')
                {
                    if (tmp.length())
                    {
                        vector.push_back(toType<typename T::value_type>(tmp));
                        tmp = "";
                    }
                    state = ready;
                }
                else
                {
                    tmp += c;
                }
            }
            else if (state == readingInQuotes)
            {
                if (c == currentQuoteChar)
                {
                    if (tmp.length())
                    {
                        vector.push_back(toType<typename T::value_type>(tmp));
                        tmp = "";
                    }
                    state = ready;
                }
                else
                {
                    tmp += c;
                }
            }
            else
                throw ConfException("bad value");
            if (pos > value.length())
            {
                if (tmp.length())
                {
                    TRACE2("added: ", tmp.length());
                    vector.push_back(toType<typename T::value_type>(tmp));
                }
                tmp = "";
                state = finished;
            }


            TRACE2("tmp :", tmp);
        }
        TRACE2("vector.size :", vector.size());

    }
    template<typename T>
    void set(const std::string & name, const T & value)
    {
        std::stringstream str;
        str << value;
        values[name] = str.str();
    }
    void processLine(const std::string &str)
    {
        std::string tmp(str);
        trimLeft(tmp);
        if (!str.length())
            return;
        if (str[0] == '#')
            return;
        std::string::size_type pos = str.find("=", 0);
        if (!pos)
            return;
        if (pos == std::string::npos)
            return;
        std::string name, value;
        name.assign(str, 0, pos);
        trim(name);
        std::string::size_type valueLength = str.length() - pos;
        std::string::size_type posComments = str.find("#", pos);
        if (pos != std::string::npos)
            valueLength = posComments - pos - 1;
        value.assign(str, pos + 1, valueLength);
        trim(value);

/*        TRACE(name);
        TRACE(value);*/
        values[name] = value;
    }

    void printMap()
    {
        for (ConfValuesConstIter it = values.begin(); it != values.end(); it++)
            TRACE2(it->first, it->second);
    }
private:
    ConfValues values;

    void trim(std::string &str)
    {
        trimLeft(str);
        trimRight(str);
    }
    void trimLeft(std::string &str)
    {
        while (str[0] == ' ')
            str.replace(0, 1, "");
    }
    void trimRight(std::string &str)
    {
        while (str[str.length() - 1] == ' ')
            str.replace(str.length() - 1, 1, "");
    }
};


} // confpp

#endif // CONFPP_H_

