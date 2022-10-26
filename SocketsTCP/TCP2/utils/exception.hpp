#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>

class Socket_exception: public std::exception{
public:
    Socket_exception(const char *_error): err_socket(_error) {  }

    Socket_exception(): err_socket("Unknown error") {  }

    ~Socket_exception() noexcept { }

    const char *what()const noexcept { return err_socket; }

private:
    const char * err_socket;
};

typedef Socket_exception err_socket;

#endif // EXCEPTION_HPP
