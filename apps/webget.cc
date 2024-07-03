#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  /*
    GET /hello HTTP/1.1
    HOST: cs144.keithw.org
    Connection: close
  */
  TCPSocket mysocket;
  /*
    host = cs144.keithw.org
    path = /hello
  */
  mysocket.connect(Address(host,"http"));
  mysocket.write("GET "+path+" HTTP/1.1"+"\r\n"); //系统输入的path自带第一个分割符/，不用自己加
  mysocket.write("Host: "+host+"\r\n");
  mysocket.write("Connection: close\r\n");
  mysocket.write("\r\n");
  mysocket.shutdown(SHUT_WR);

  while (!mysocket.eof()) {
      cout<<mysocket.read();
  }

  mysocket.close();//为什么不可以只关闭SHUT_RD来充当close?SHUT_WR已经关闭了
  cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
  cerr << "Warning: get_URL() has not been implemented yet.\n";
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
