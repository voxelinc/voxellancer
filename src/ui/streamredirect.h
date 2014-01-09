#pragma once

#include <iostream>
#include <streambuf>
#include <string>

#include "ui/hud.h"


class StreamRedirect : public std::basic_streambuf<char> {
public:
    StreamRedirect(std::ostream &stream, HUD *hud, bool copy = false);
    ~StreamRedirect();

protected:
    virtual int_type overflow(int_type v) override;
    virtual std::streamsize xsputn(const char *p, std::streamsize n) override;

private:
    std::ostream &m_stream;
    std::ostream *m_old_wrap;
    std::streambuf *m_old_buf;
    std::string m_string;
    bool m_copy;
    HUD* m_hud;
};