#ifndef output_hpp
#define output_hpp

#include <vector>
#include <string>
#include <sstream>

namespace logging {

using std::string;
using std::stringstream;
using std::vector;


/**
 * convert a list of arguments to a string
 * @param args the arguments
 */
template<typename... T>
string text(T...args);

/**
 * create a string from a formatstring and some arguments
 *
 * unlike printf() this will accept any type with %s as identifier
 *
 * The formatstring will be printed as is, unless a '%' appears. In
 * this case the next character will be used to decide, what to do:
 *
 * If it is another '%', only one of them will be added to the returnstring
 * and the function will return back to its normal path.
 * 
 * If it is a 's', a counter will be increased and the string-representation of
 * args[counter] will be added to the string.
 * 
 * In all other cases the substring that terminates before the first following
 * 's' will be taken and converted to a int. This int will be used as index to 
 * which arg from args shall be inserted. Note that in this case arg[0] is the
 * formatstring itself.
 *
 * @param formatstring the formatstring
 * @param args the other arguments
 */
template<typename...T>
string textf(const string& formatstring,T...args);


/**
 * set the logfile
 *
 * @param filename logfile; if empty, logging will be disabled
 */
void set_logfile(const string& filename);

#ifdef DEBUG

/**
 * print a debugmessage; this won't do anything in release-builds
 * @param level debuglevel (lower means less important)
 * @param others parameters that will be converted to a string and printed
 */
#define debug(level, ...) _debug( __FILE__, __LINE__, (level), text(__VA_ARGS__) )

/**
 * print a debugmessage; this won't do anything in release-builds
 * @param level debuglevel (lower means less important)
 * @param others the first parameter is a formatstring that will, 
 *               together with the rest, create the message
 */
#define debugf(level, ...) _debug( __FILE__, __LINE__, (level), textf(__VA_ARGS__) )

/**
 * set the debug-level: only debug-messages with a level higher that it will be processed.
 * @param level the new debuglevel
 */
void set_debug_level(int level);


#else // not DEBUG-mode
// these declarations are just here to enable compilation
#define debug(level, ...)
#define debugf(level, ...)
#define set_debug_level(level)
#endif


/**
 * set the verbosity level: only notes with a level <= @param v will be
 * printed
 */
void set_verbose_level(int v);


/**
 * print a note with the given urgency-level 
 * @param level urgency-level ot the message
 * @param args the args that will be converted to a string and then concatenated to 
 *             form the message, that will be printed
 */
template<typename... T>
void note(int level, T...args);


/**
 * print a note with the given urgency-level 
 * @param level urgency-level ot the message
 * @param formatstring a string that describes how the message should be build and 
 *                     uses the other args to build the final text.
 * @param args the args that will be converted to a string
 */
template<typename... T>
void notef(int level, const string& formatstring, T...args);


/**
 * print a warning to stderr and log it, if a logfile is set.
 * @param args the args that will be converted to a string and then concatenated to 
 *             form the message, that will be printed
 */
template<typename... T>
void warn(T... args);

/**
 * print a warning to stderr and log it, if a logfile is set.
 * @param formatstring a string that describes how the message should be build and 
 *                     uses the other args to build the final text.
 * @param args the args that will be converted to a string
 */
template<typename... T>
void warn(const string& formatstring, T... args);


/**
 * print an error to stderr and log it, if a logfile is set.
 * @param args the args that will be converted to a string and then concatenated to 
 *             form the message, that will be printed
 */
template<typename... T>
void error(T... args);

/**
 * print an error to stderr and log it, if a logfile is set.
 * @param formatstring a string that describes how the message should be build and 
 *                     uses the other args to build the final text.
 * @param args the args that will be converted to a string
 */
template<typename... T>
void errorf(const string& formatstring, T... args);

/**
 * print a fatal error. This will throw a private exception to terminate the
 * program. You may want to ensure that the destructors are executed by encapsulating
 * your main with a catch(...){return 1;} block.
 *
 * @param args the args that will be converted to a string and then concatenated to 
 *             form the message, that will be printed
 */
template<typename... T>
void fatal(T... args);

/**
 * print a fatal error. This will throw a private exception to terminate the
 * program. You may want to ensure that the destructors are executed by encapsulating
 * your main with a catch(...){return 1;} block.
 *
 * @param formatstring a string that describes how the message should be build and 
 *                     uses the other args to build the final text.
 * @param args the args that will be converted to a string
 */
template<typename... T>
void fatalf(const string& formatstring, T... args);

/**
 * get the current time
 */
string get_timestamp();


/**
 * write a message to stdout or stderr and to the log
 * 
 * @param msg the message that will be printed
 * @param normal whether the message is normal behaviour and should be 
 * printed to stdout or an error to be printed to stderr
 */
void print_and_log(const string& msg, bool normal = true);

} //logging namespace

#include "output.tcc"

#endif
