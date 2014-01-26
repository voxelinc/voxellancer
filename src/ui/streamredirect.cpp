#include "streamredirect.h"


StreamRedirect::StreamRedirect(std::ostream &stream, HUD *hud, bool copy) :
    m_stream(stream)
{
    m_hud = hud;
    m_old_buf = stream.rdbuf();
    m_old_wrap = new std::ostream(m_old_buf);
    m_copy = copy;
    stream.rdbuf(this);
}

StreamRedirect::~StreamRedirect() {
    // output anything that is left
    if (!m_string.empty()) {
//        m_hud->printLine(m_string);
    }
    delete m_old_wrap;
    m_stream.rdbuf(m_old_buf);
}

std::basic_streambuf<char>::int_type StreamRedirect::overflow(int_type v) {

    if (v == '\n') {
 //       m_hud->printLine(m_string);
        if (m_copy) {
            *m_old_wrap << m_string << std::endl;
        }
        m_string.erase(m_string.begin(), m_string.end());
    } else {
        m_string += v;
    }

    return v;
}

std::streamsize StreamRedirect::xsputn(const char *p, std::streamsize n) {

    m_string.append(p, p + n);

    size_t pos = 0;
    while (pos != std::string::npos) {
        pos = m_string.find('\n');
        if (pos != std::string::npos) {
            std::string tmp(m_string.begin(), m_string.begin() + pos);
 //          m_hud->printLine(tmp);
            if (m_copy) {
                *m_old_wrap << tmp << std::endl;
            }
            m_string.erase(m_string.begin(), m_string.begin() + pos + 1);
        }
    }

    return n;
}

