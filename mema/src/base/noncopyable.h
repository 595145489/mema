#pragma once

namespace mema{

class noncopyable
{
protected:
    noncopyable() = default;
    ~noncopyable() = default;
private:
    noncopyable(const noncopyable&) = delete;
    const noncopyable& operator=(const noncopyable&) = delete;
};

}// end namespace

