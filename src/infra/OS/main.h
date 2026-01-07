#ifndef OS_MAIN_H
#define OS_MAIN_H

typedef enum {
    Linux,
    Windows,
    MacOS
} _OS_ENUM;

_OS_ENUM detectOS();

#endif