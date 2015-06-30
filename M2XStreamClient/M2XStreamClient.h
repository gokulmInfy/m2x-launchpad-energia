#ifndef M2XStreamClient_h
#define M2XStreamClient_h

#define MIN(a, b) (((a) > (b))?(b):(a))

#define ENERGIA_PLATFORM

#ifdef ENERGIA_PLATFORM
#include "Energia.h"
#define USER_AGENT "User-Agent: M2X Energia Client/2.1.0"
#endif

#ifdef ARDUINO_PLATFORM
#include "Arduino.h"
#define USER_AGENT "User-Agent: M2X Arduino Client/0.1"
#endif

#ifdef MBED_PLATFORM
#include "mbed.h"

#define USER_AGENT "User-Agent: M2X Mbed Client/0.1"
#endif

#include "Client.h"
#include "NullPrint.h"

#ifdef DEBUG
#if defined(ARDUINO_PLATFORM) || defined(ENERGIA_PLATFORM)
#define DBG(fmt_, data_) Serial.print(data_)
#define DBGLN(fmt_, data_) Serial.println(data_)
#define DBGLNEND Serial.println()
#endif  // ARDUINO_PLATFORM || ENERGIA_PLATFORM

#ifdef MBED_PLATFORM
#define DBG(fmt_, data_) printf((fmt_), (data_))
#define DBGLN(fmt_, data_) printf((fmt_), (data_)); printf("\n")
#define DBGLNEND printf("\n")
#endif  // MBED_PLATFORM
#else
#define DBG(fmt_, data_)
#define DBGLN(fmt_, data_)
#define DBGLNEND
#endif  // DEBUG

#define TO_HEX(t_) ((char) (((t_) > 9) ? ((t_) - 10 + 'A') : ((t_) + '0')))
#define MAX_DOUBLE_DIGITS 7

static const int E_OK = 0;
static const int E_NOCONNECTION = -1;
static const int E_DISCONNECTED = -2;
static const int E_NOTREACHABLE = -3;
static const int E_INVALID = -4;
static const int E_JSON_INVALID = -5;
static const int E_BUFFER_TOO_SMALL = -6;
static const int E_TIMESTAMP_ERROR = -8;

static inline bool m2x_status_is_success(int status) {
  return (status == E_OK) || (status >= 200 && status <= 299);
}

static inline bool m2x_status_is_client_error(int status) {
  return status >= 400 && status <= 499;
}

static inline bool m2x_status_is_server_error(int status) {
  return status >= 500 && status <= 599;
}

static inline bool m2x_status_is_error(int status) {
  return m2x_status_is_client_error(status) ||
      m2x_status_is_server_error(status);
}

class M2XStreamClient {
public:
  static const char* kDefaultM2XHost;
  static const int kDefaultM2XPort = 80;

  M2XStreamClient(Client* client,
                  const char* key,
                  int case_insensitive = 1,
                  const char* host = kDefaultM2XHost,
                  int port = kDefaultM2XPort);

  // Push data stream value using PUT request, returns the HTTP status code
  template <class T>
  int updateStreamValue(const char* deviceId, const char* streamName, T value);

  // Post multiple values to M2X all at once.
  // +deviceId+ - id of the device to post values
  // +streamNum+ - Number of streams to post
  // +names+ - Array of stream names, the length of the array should
  // be exactly +streamNum+
  // +counts+ - Array of +streamNum+ length, each item in this array
  // containing the number of values we want to post for each stream
  // +ats+ - Timestamps for each value, the length of this array should
  // be the some of all values in +counts+, for the first +counts[0]+
  // items, the values belong to the first stream, for the following
  // +counts[1]+ number of items, the values belong to the second stream,
  // etc. Note timestamps are optional, if a value does not havee timestamp,
  // we can simply put NULL here, or we can put NULl for +ats+, meaning
  // none of the values has a timestamp
  // +values+ - Values to post. This works the same way as +ats+, the
  // first +counts[0]+ number of items contain values to post to the first
  // stream, the succeeding +counts[1]+ number of items contain values
  // for the second stream, etc. The length of this array should be
  // the sum of all values in +counts+ array.
  template <class T>
  int postDeviceUpdates(const char* deviceId, int streamNum,
                        const char* names[], const int counts[],
                        const char* ats[], T values[]);

  // Fetch values for a particular data stream. Since memory is
  // very limited on a board, we cannot parse and get all the
  // data points in memory. Instead, we use callbacks here: whenever
  // a new data point is parsed, we call the callback using the values,
  // after that, the values will be thrown away to make space for new
  // values.
  // Note that you can also pass in a user-specified context in this
  // function, this context will be passed to the callback function
  // each time we get a data point.
  // For each data point, the callback will be called once. The HTTP
  // status code will be returned. And the content is only parsed when
  // the status code is 200.
  int listStreamValues(const char* deviceId, const char* streamName,
                       const char* query,
                       aJsonObject **out);

  // Update datasource location
  // NOTE: On an Arduino Uno and other ATMEGA based boards, double has
  // 4-byte (32 bits) precision, which is the same as float. So there's
  // no natural double-precision floating number on these boards. With
  // a float value, we have a precision of roughly 7 digits, that means
  // either 5 or 6 digits after the floating point. According to wikipedia,
  // a difference of 0.00001 will give us ~1.1132m distance. If this
  // precision is good for you, you can use the double-version we provided
  // here. Otherwise, you may need to use the string-version and do the
  // actual conversion by yourselves.
  // However, with an Arduino Due board, double has 8-bytes (64 bits)
  // precision, which means you are free to use the double-version only
  // without any precision problems.
  // Returned value is the http status code.
  template <class T>
  int updateLocation(const char* deviceId, const char* name,
                     T latitude, T longitude, T elevation);

  // Read location information for a device. Also used callback to process
  // data points for memory reasons. The HTTP status code is returned,
  // response is only parsed when the HTTP status code is 200
  int readLocation(const char* deviceId, aJsonObject **out);

  // Delete values from a data stream
  // You will need to provide from and end date/time strings in the ISO8601 
  // format "yyyy-mm-ddTHH:MM:SS.SSSZ" where
  //   yyyy: the year
  //   mm: the month
  //   dd: the day
  //   HH: the hour (24 hour format)
  //   MM: the minute
  //   SS.SSS: the seconds (to the millisecond)
  // NOTE: the time is given in Zulu (GMT)
  // M2X will delete all values within the from to end date/time range.
  // The status code is 204 on success and 400 on a bad request (e.g. the
  // timestamp is not in ISO8601 format or the from timestamp is not less than
  // or equal to the end timestamp.
  int deleteValues(const char* deviceId, const char* streamName, 
                   const char* from, const char* end);

  // Fetches current timestamp in seconds from M2X server. Since we
  // are using signed 32-bit integer as return value, this will only
  // return valid results before 03:14:07 UTC on 19 January 2038. If
  // the device is supposed to work after that, this function should
  // not be used.
  //
  // The returned value will contain the status code(positive values)
  // or the error code(negative values).
  // In case of success, the current timestamp will be filled in the
  // +ts+ pointer passed in as argument.
  //
  // NOTE: although returning uint32_t can give us a larger space,
  // we prefer to cope with the unix convention here.
  int getTimestamp32(int32_t* ts);

  // Fetches current timestamp in seconds from M2X server.
  // This function will return the timestamp as an integer literal
  // in the provided buffer. Hence there's no problem working after
  // 03:14:07 UTC on 19 January 2038. The drawback part here, is that
  // you will have to work with 64-bit integer, which is not available
  // on certain platform(such as Arduino), a bignum library or alike
  // is needed in this case.
  //
  // Notice +bufferLength+ is supposed to contain the length of the
  // buffer when calling this function. It is also the caller's
  // responsibility to ensure the buffer is big enough, otherwise
  // the library will return an error indicating the buffer is too
  // small.
  // While this is not accurate all the time, one trick here is to
  // pass in 0 as the bufferLength, in which case we will always return
  // the buffer-too-small error. However, the correct buffer length
  // can be found this way so a secound execution is most likely to work
  // (unless we are at the edge of the buffer length increasing, for
  // example, when the timestamp jumps from 9999999999 to 10000000000,
  // which is highly unlikely to happend). However, given that the
  // maximum 64-bit integer can be stored in 19 bytes, there's not
  // much need to use this trick.)
  //
  // The returned value will contain the status code(positive values)
  // or the error code(negative values).
  // In case of success, the current timestamp will be filled in the
  // passed +buffer+ pointer, and the actual used buffer length will
  // be returned in +bufferLength+ pointer.
  // NOTE: as long as we can read the returned buffer length, it will
  // be used to fill in the +bufferLength+ variable even though other
  // errors occur(buffer is not enough, network is shutdown before
  // reading the whole buffer, etc.)
  int getTimestamp(char* buffer, int* bufferLength);
private:
  Client* _client;
  const char* _key;
  int _case_insensitive;
  const char* _host;
  int _port;
  NullPrint _null_print;

  // Writes the HTTP header part for updating a stream value
  void writePutHeader(const char* deviceId,
                      const char* streamName,
                      int contentLength);
  // Writes the HTTP header part for deleting stream values
  void writeDeleteHeader(const char* deviceId,
                         const char* streamName,
                         int contentLength);
  // Writes HTTP header lines including M2X API Key, host, content
  // type and content length(if the body exists)
  void writeHttpHeader(int contentLength);
  // Parses HTTP response header and return the content length.
  // Note that this function does not parse all http headers, as long
  // as the content length is found, this function will return
  int readContentLength();
  // Skips all HTTP response header part. Return minus value in case
  // the connection is closed before we got all headers
  int skipHttpHeader();
  // Parses and returns the HTTP status code, note this function will
  // return immediately once it gets the status code
  int readStatusCode(bool closeClient);
  // Waits for a certain string pattern in the HTTP header, and returns
  // once the pattern is found. In the pattern, you can use '*' to denote
  // any character
  int waitForString(const char* str);
  // Closes the connection
  void close();
  // Parses JSON response
  int parseJsonBody(aJsonObject **out);
};

#include "M2XStreamClient_template.h"
#include "TimeService.h"

#endif  /* M2XStreamClient_h */
