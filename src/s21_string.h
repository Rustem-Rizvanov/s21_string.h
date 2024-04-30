#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // s21_strspn

#define s21_NULL ((void *)0)

typedef long unsigned s21_size_t;



typedef struct Holder {
    int code;
    struct Holder *next;
} Holder;


#if defined(__APPLE__)
    #define MAX 106
    #define error {"Undefined error: 0", \
"Operation not permitted", \
"No such file or directory", \
"No such process", \
"Interrupted system call", \
"Input/output error", \
"Device not configured", \
"Argument list too long", \
"Exec format error", \
"Bad file descriptor", \
"No child processes", \
"Resource deadlock avoided", \
"Cannot allocate memory", \
"Permission denied", \
"Bad address", \
"Block device required", \
"Resource busy", \
"File exists", \
"Cross-device link", \
"Operation not supported by device", \
"Not a directory", \
"Is a directory", \
"Invalid argument", \
"Too many open files in system", \
"Too many open files", \
"Inappropriate ioctl for device", \
"Text file busy", \
"File too large", \
"No space left on device", \
"Illegal seek", \
"Read-only file system", \
"Too many links", \
"Broken pipe", \
"Numerical argument out of domain", \
"Result too large", \
"Resource temporarily unavailable", \
"Operation now in progress", \
"Operation already in progress", \
"Socket operation on non-socket", \
"Destination address required", \
"Message too long", \
"Protocol wrong type for socket", \
"Protocol not available", \
"Protocol not supported", \
"Socket type not supported", \
"Operation not supported", \
"Protocol family not supported", \
"Address family not supported by protocol family", \
"Address already in use", \
"Can't assign requested address", \
"Network is down", \
"Network is unreachable", \
"Network dropped connection on reset", \
"Software caused connection abort", \
"Connection reset by peer", \
"No buffer space available", \
"Socket is already connected", \
"Socket is not connected", \
"Can't send after socket shutdown", \
"Too many references: can't splice", \
"Operation timed out", \
"Connection refused", \
"Too many levels of symbolic links", \
"File name too long", \
"Host is down", \
"No route to host", \
"Directory not empty", \
"Too many processes", \
"Too many users", \
"Disc quota exceeded", \
"Stale NFS file handle", \
"Too many levels of remote in path", \
"RPC struct is bad", \
"RPC version wrong", \
"RPC prog. not avail", \
"Program version wrong", \
"Bad procedure for program", \
"No locks available", \
"Function not implemented", \
"Inappropriate file type or format", \
"Authentication error", \
"Need authenticator", \
"Device power is off", \
"Device error", \
"Value too large to be stored in data type", \
"Bad executable (or shared library)", \
"Bad CPU type in executable", \
"Shared library version mismatch", \
"Malformed Mach-o file", \
"Operation canceled", \
"Identifier removed", \
"No message of desired type", \
"Illegal byte sequence", \
"Attribute not found", \
"Bad message", \
"EMULTIHOP (Reserved)", \
"No message available on STREAM", \
"ENOLINK (Reserved)", \
"No STREAM resources", \
"Not a STREAM", \
"Protocol error", \
"STREAM ioctl timeout", \
"Operation not supported on socket", \
"Policy not found", \
"State not recoverable", \
"Previous owner died", \
"Interface output queue is full"}
#elif defined (__linux__)
    #define MAX 133
    #define error {"Success", \
"Operation not permitted", \
"No such file or directory", \
"No such process", \
"Interrupted system call", \
"I/O error", \
"No such device or address", \
"Argument list too long", \
"Exec format error", \
"Bad file descriptor", \
"No child process", \
"Resource temporarily unavailable", \
"Out of memory", \
"Permission denied", \
"Bad address", \
"Block device required", \
"Resource busy", \
"File exists", \
"Cross-device link", \
"No such device", \
"Not a directory", \
"Is a directory", \
"Invalid argument", \
"Too many open files in system", \
"No file descriptors available", \
"Not a tty", \
"Text file busy", \
"File too large", \
"No space left on device", \
"Invalid seek", \
"Read-only file system", \
"Too many links", \
"Broken pipe", \
"Domain error", \
"Result not representable", \
"Resource deadlock would occur", \
"Filename too long", \
"No locks available", \
"Function not implemented", \
"Directory not empty", \
"Symbolic link loop", \
"No error information", \
"No message of desired type", \
"Identifier removed", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"Device not a stream", \
"No data available", \
"Device timeout", \
"Out of streams resources", \
"No error information", \
"No error information", \
"No error information", \
"Link has been severed", \
"No error information", \
"No error information", \
"No error information", \
"Protocol error", \
"Multihop attempted", \
"No error information", \
"Bad message", \
"Value too large for data type", \
"No error information", \
"File descriptor in bad state", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"Illegal byte sequence", \
"No error information", \
"No error information", \
"No error information", \
"Not a socket", \
"Destination address required", \
"Message too large", \
"Protocol wrong type for socket", \
"Protocol not available", \
"Protocol not supported", \
"Socket type not supported", \
"Not supported", \
"Protocol family not supported", \
"Address family not supported by protocol", \
"Address in use", \
"Address not available", \
"Network is down", \
"Network unreachable", \
"Connection reset by network", \
"Connection aborted", \
"Connection reset by peer", \
"No buffer space available", \
"Socket is connected", \
"Socket not connected", \
"Cannot send after socket shutdown", \
"Too many references: cannot splice", \
"Connection timed out", \
"Connection refused", \
"Host is down", \
"No route to host", \
"Operation already in progress", \
"Operation now in progress", \
"Stale file handle", \
"Structure needs cleaning", \
"Not a XENIX named type file", \
"No XENIX semaphores available", \
"Is a named type file", \
"Remote I/O error", \
"Disk quota exceeded", \
"No medium found", \
"Wrong medium type", \
"Operation canceled", \
"Required key not available", \
"Key has expired", \
"Key has been revoked", \
"Key was rejected by service", \
"Owner died", \
"State not recoverable", \
"Operation not possible due to RF-kill", \
"Memory page has hardware error"}
#endif  // (__unix__)


#endif // SRC_S21_STRING_H_
