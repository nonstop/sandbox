#ifndef CALLSTACK_H
#define CALLSTACK_H

#include <list>
#include <string>
#include <sstream>
#include <stdio.h>

#ifndef CALLSTACK_MAX_SIZE
///< if not previously defines maximum stack size
#define CALLSTACK_MAX_SIZE 10
#endif // CALLSTACK_MAX_SIZE

/**
 * class Callstack
 * @brief saves temporary stack of defined size
 * Class for saving temporary debug messages. Messages are stored in
 * limited by CALLSTACK_MAX_SIZE value stack. Stores last CALLSTACK_MAX_SIZE messages
 *
 * */
class Callstack
{
public:
    /**
     * struct MetaInfo
     * Information about functions and variables, their values and positions in source file.
     * */
    struct MetaInfo
    {
        const char* m_file;
        int m_line;
        const char* m_nick;
        std::string m_value;
        MetaInfo(const char *file, int line, const char *nick, const std::string& value)
            : m_file(file), m_line(line), m_nick(nick), m_value(value)
        {}
        template<typename T>
        MetaInfo(const char *file, int line, const char *nick, const char* varName, const T& value)
            : m_file(file), m_line(line), m_nick(nick)
        {
            std::stringstream ss;
            ss << varName << "[" << value << "]";
            m_value = ss.str();
        }
    };
    typedef std::list<MetaInfo> Stack;

    /**
     * the only access to Callstack  */
    static Callstack* instance();
    /**
     * @param mi MetaInfo
     * adds MetaInfo to stack */
    void push(const MetaInfo& mi);
    /**
     * @return current stack */
    const Stack& stack();
    /**
     * dumps stack into file f */
    void dump(FILE* f) const;
private:
    Callstack()
    {}
    Stack m_stack;
};
///< adds function declaration to stack
#define F_STACK Callstack::instance()->push(Callstack::MetaInfo(__FILE__, __LINE__, NICKNAME, __FUNCTION__))
///< adds variable name and value to stack
#define VAR_STACK(x) Callstack::instance()->push(Callstack::MetaInfo(__FILE__, __LINE__, NICKNAME, #x, x))



#endif /* CALLSTACK_H */

