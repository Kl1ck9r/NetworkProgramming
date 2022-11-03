#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>

class socket_error{
public:
    virtual ~socket_error() noexcept { delete err_message; }

    socket_error() { err_message=" Unknow message ";}

    socket_error(const char *err_msg):err_message(err_msg) {  }

    const char *what()const { return err_message; }

private:
    const char *err_message;
};


#endif // EXCEPTION_HPP
