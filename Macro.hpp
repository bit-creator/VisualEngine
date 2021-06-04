/**
 * @file profiling.hpp
 * @author Abernikhin Ilia (lliepjiokandxojimc@gmail.com)
 * @brief debug macroses
 * @version 0.0.1
 * @date 2021-02-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __MACRO_HPP__
#define __MACRO_HPP__

#ifdef DEBUG	/* enable all */
#	define CHECK_GL_ERROR
#	define CONSOLE_MESSAGES
#	define CONSOLE_ERRORS
#endif // DEBUG 
#ifdef RELEASE	/* disable all */
#	undef  CHECK_GL_ERROR
#	undef  CONSOLE_MESSAGES
#	undef  CONSOLE_ERRORS
#endif // RELEASE
#ifndef CHECK_GL_ERROR
#   define HANDLE_GL_ERROR() {  }
#else
#	ifndef _GLIBCXX_CSIGNAL
# 		include <csignal>
#	endif // CSIGLAL
#	ifndef __glew_h__
#   	include <GL/glew.h>
#	endif // __GLEW_H__
#   define HANDLE_GL_ERROR() {	 								\
    	if (auto res = glGetError( ); res != GL_NO_ERROR) {		\
        	std::cout << "| GL_ERROR | "      					\
    		      	  << "file | " << __FILE__					\
    	    	  	  << " | method | " << __PRETTY_FUNCTION__	\
    	    	  	  << " | line | " << __LINE__   			\
    	    	  	  << " | " << glewGetErrorString(res)		\
    	    	  	  << std::endl;								\
			std::raise(SIGTERM);								\
     	} else {												\
     															\
     	}														\
    } // HANDLE_GL_ERROR
#endif // CHECK_GL_ERROR
#if defined(CONSOLE_MESSAGES) || defined(CONSOLE_ERRORS)
#	ifndef _GLIBCXX_IOSTREAM
#		include <iostream>
#	endif // IOSTREAM
#	ifndef _GLIBCXX_STRING
#		include <string>
#	endif // STRING
#endif // IOSTREAM_INCLUDE
#ifndef CONSOLE_MESSAGES
#	define MESSAGE (msg) { #msg }
#else
#	define MESSAGE(msg) {	         \
		std::cout << "|   INFO   | " \
				  << msg		     \
				   << std::endl;     \
	}
#	define DEEP_MESSAGE(msg) {	     						\
        std::cout << "|   INFO   | "    					\
    	      	  << "file | " << __FILE__					\
    		  	  << " | method | " << __PRETTY_FUNCTION__	\
    		  	  << " | line | " << __LINE__   			\
    		  	  << " | " << msg 							\
    		  	  << std::endl;								\
	}
#endif // CONSOLE_MESSAGES
#ifndef CONSOLE_ERRORS
#	define ERROR (msg) { #msg }
#else
#	define ERROR(msg) {	             						\
		std::cout << "|  ERRORS  | " 						\
    		      << "file | " << __FILE__					\
    	    	  << " | method | " << __PRETTY_FUNCTION__	\
    	    	  << " | line | " << __LINE__   			\
    	    	  << " | " << msg 							\
    	    	  << std::endl;								\
    	/*std::raise(SIGTERM);*/								\
	}
#endif // CONSOLE_ERRORS

#endif // __MACRO_HPP__
