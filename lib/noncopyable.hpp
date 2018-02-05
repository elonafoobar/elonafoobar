#pragma once



namespace lib
{
class noncopyable
{
public:
    noncopyable() = default;
    virtual ~noncopyable() = default;

private:
    noncopyable(const noncopyable&) = delete;
    noncopyable(noncopyable&&) = delete;
    void operator=(const noncopyable&) = delete;
    void operator=(noncopyable&&) = delete;
};


} // namespace lib
