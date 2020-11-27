#include <stdio.h>
#include "cond.h"

#ifdef _WIN32
#elif __linux__
#include "condunix.h"
#else 
# error "Unknown Compiler"
#endif

namespace utils {

CCond::CCond() {
    m_cond = NULL;
#ifdef _WIN32
#elif __linux__
    m_cond = new utils::CCondUnix;
#else 
# error "Unknown Compiler"
#endif 
}

CCond::~CCond() {
    if (m_cond != NULL) {
        delete m_cond;
        m_cond = NULL;
    }
}

int CCond::wait(int milliseconds) {
    return m_cond->wait(milliseconds);
}

int CCond::signal() {
    return m_cond->signal();
}

int CCond::broadcast() {
    return m_cond->broadcast();
}

int CCond::lock() {
    return m_cond->acquire();
}

int CCond::unlock() {
    return m_cond->release();
}

}