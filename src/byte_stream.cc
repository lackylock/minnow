#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), closed_(false), bytes_pushed_cnt_(0), bytes_popped_cnt_(0) {}

bool Writer::is_closed() const
{
  return closed_;
}

void Writer::push( string data )
{
  if ( is_closed() || has_error() )
    return;
  const size_t len = min( data.size(), available_capacity() );
  buf_.append(data.substr(0, len));
  bytes_pushed_cnt_ += len;
}

void Writer::close()
{
  closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - bytes_pushed_cnt_ + bytes_popped_cnt_;
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_cnt_;
}

bool Reader::is_finished() const
{
  return closed_ && bytes_buffered() == 0;
}

uint64_t Reader::bytes_popped() const
{
  return bytes_popped_cnt_;
}

string_view Reader::peek() const
{
  return this->buf_;
}

void Reader::pop( uint64_t len )
{
  if (bytes_buffered() == 0)
    return;
  int len = min( bytes_buffered(), len );
  buf_.erase(0, len);
  bytes_popped_cnt_ += len;
}

uint64_t Reader::bytes_buffered() const
{
  return bytes_pushed_cnt_ - bytes_popped_cnt_;
}
