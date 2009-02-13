
#include "callstack.h"

    
Callstack* Callstack::instance()
{
    static Callstack *p = NULL;
    if (!p)
        p = new Callstack;
    return p;
}

void Callstack::push(const Callstack::MetaInfo& mi)
{
    if (m_stack.size() > CALLSTACK_MAX_SIZE)
        m_stack.pop_front();
    m_stack.push_back(mi);
}

const Callstack::Stack& Callstack::stack()
{
    return m_stack;
}

void Callstack::dump(FILE* f) const
{
    for (Stack::const_iterator it = m_stack.begin(); it != m_stack.end(); ++it)
        fprintf(f, "%s %s:%d %s\n", it->m_nick, it->m_file, it->m_line, it->m_value.c_str());
}

