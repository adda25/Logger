/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 - Amedeo Setti
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _AS_LOGGER_HPP_
#define _AS_LOGGER_HPP_
#ifdef __cplusplus

#include <fstream>
#include <iostream>
#include <ostream>
#include <utility>
#include <iomanip>
#include <chrono>

namespace as 
{
    class Timer
    {
    public:
        Timer() {
            reset_start_time();
        };
        virtual ~Timer() {};

        void
        reset_start_time() {
            _start_time = get_current_time();
        }

        std::chrono::high_resolution_clock::time_point 
        get_current_time() {
            return std::chrono::high_resolution_clock::now();
        }

        // Seconds
        double 
        time() {
            return (_time() / 1000.0f);
        }

        // Milliseconds
        int 
        time_ms() {
            return static_cast<int>(_time());
        }

    private:
        std::chrono::high_resolution_clock::time_point _start_time;

        double
        _time() {
            auto t2 = std::chrono::high_resolution_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - _start_time);
            return time_span.count();
        }
    };

    class Logger
    {   
    public: 
        using CharType = std::string;
        CharType separator  = "\t";
        CharType start_line = "";
        CharType end_line   = "\n";
        int floating_point_digits = 3;
        Timer timer;
        
        Logger(std::ostream& stream) : _stream(stream) {}
        virtual ~Logger() {};
    
        template<class T, class... Args> Logger& 
        log(T t, Args... args) {
            const int n = sizeof...(Args);
            _args_size = n + 1;
            _args_size_init = _args_size;
            _print(t);
            _print(args...);
            return *this;
        }
    
        template<class T> Logger&
        log(T val) {
            _stream << start_line << val << end_line;   
            return *this;
        }

    private:
        std::ostream &_stream;
        int _args_size = 0;
        int _args_size_init = 0;

        template<class T, class... Args> void
        _print(T t, Args... args) {
            _print(t);
            _print(args...);
        }
    
        template<class T> void
        _print(T val) {
            --_args_size;
            if (_args_size == 0) {
                _stream << std::fixed << std::setprecision(floating_point_digits) << val << end_line;   
            } else if ((_args_size + 1) == (_args_size_init)) {
                _stream << std::fixed << std::setprecision(floating_point_digits) << start_line << val << separator;    
            } else {
                _stream << std::fixed << std::setprecision(floating_point_digits) << val << separator;
            }
        }

    }; // End Logger
}; // End namespace

#endif // __cplusplus
#endif // _AS_LOGGER_HPP_
