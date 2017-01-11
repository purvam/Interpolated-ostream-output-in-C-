/*
 * Interpolate.hpp
 *
 *  Created on: May 14, 2016
 *      Author: Smurfette
 */
#ifndef INTERPOLATE_HPP_
#define INTERPOLATE_HPP_

#include <iostream>
#include <tuple>
#include <utility>
#include<exception>
#include<ios>

#include <typeinfo>
#include <locale>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <ctime>
#include <cstring>
// Needed by {set,get}rlimit().
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>


namespace cs540{

class WrongNumberOfArgs{

};

template <typename... Ts>
class Interpolate_helper{
public:
  const char *stmt;
  std::tuple<const Ts&...> tup;
  Interpolate_helper(const char *s,const Ts&...t):stmt(s),tup(t...) {}
  
  template<typename... Us>
  friend std::ostream &operator<<(std::ostream &os,Interpolate_helper<Us...> &ih);
  
//printing functions  
  std::ostream& print(std::ostream &os, const char *stmt) const{
    while(*(stmt)){
      if(*(stmt)=='\\' && *(stmt+1)=='%'){
        os<<stmt[1];
        stmt+=2;
      }
      else if(*(stmt)=='%'){
        throw WrongNumberOfArgs();
      }
      else{
        os<<stmt[0];
        stmt++;
      }
    }
    return os;
  }
    
  template<typename T,typename...U>
  typename std::enable_if<!std::is_same<decltype(std::setprecision(std::declval<int>())), typename std::decay<T>::type>::value &&
                          !std::is_same<decltype(std::setw(std::declval<int>())), typename std::decay<T>::type>::value &&
                          !std::is_same<decltype(std::resetiosflags(std::ios_base::hex)), typename std::decay<T>::type>::value && 
                          !std::is_same<decltype(std::setiosflags(std::ios_base::hex)), typename std::decay<T>::type>::value &&
                          !std::is_same<decltype(std::setbase(std::declval<int>())), typename std::decay<T>::type>::value &&
                          !std::is_same<decltype(std::setfill(std::declval<char>())), typename std::decay<T>::type>::value, std::ostream &>::type
  print(std::ostream &os,const T& t, const U&... rest) const{
    throw WrongNumberOfArgs();
  }
  
  template <typename...U>
  std::ostream& print(std::ostream& os, const char *stmt, std::ios_base&(*fp)(std::ios_base&), const U&...rest) const {
  	os<<fp;
  	print(os,stmt,rest...);
    return os;
  }
  
  
  
  template <typename T, typename...U>
  typename std::enable_if<std::is_same<decltype(std::setprecision(std::declval<int>())), typename std::decay<T>::type>::value, int>::type 
  print(std::ostream& os, const char *stmt, const T& t, const U&... rest) const {
  	os<<t;
  	print(os, stmt, rest...);
  }

  template <typename T, typename...U>
  typename std::enable_if<std::is_same<decltype(std::setw(std::declval<int>())), typename std::decay<T>::type>::value, int>::type 
  print(std::ostream& os, const char *stmt, const T& t, const U&... rest) const {
  	os<<t;
  	print(os, stmt, rest...);
  }
  template <typename T, typename...U>
  typename std::enable_if<std::is_same<decltype(std::setiosflags(std::ios_base::hex)), typename std::decay<T>::type>::value, int>::type 
  print(std::ostream& os, const char *stmt, const T& t, const U&... rest) const {
  	os<<t;
  	print(os, stmt, rest...);
  }
  template <typename T, typename...U>
  typename std::enable_if<std::is_same<decltype(std::resetiosflags(std::ios_base::hex)), typename std::decay<T>::type>::value, int>::type 
  print(std::ostream& os, const char *stmt, const T& t, const U&... rest) const {
  	os<<t;
  	print(os, stmt, rest...);
  }
  template <typename T, typename...U>
  typename std::enable_if<std::is_same<decltype(std::setbase(std::declval<int>())), typename std::decay<T>::type>::value, int>::type 
  print(std::ostream& os, const char *stmt, const T& t, const U&... rest) const {
  	os<<t;
  	print(os, stmt, rest...);
  }
  template <typename T, typename...U>
  typename std::enable_if<std::is_same<decltype(std::setfill(std::declval<char>())), typename std::decay<T>::type>::value, int>::type 
  print(std::ostream& os, const char *stmt, const T& t, const U&... rest) const {
  	os<<t;
  	print(os, stmt, rest...);
  }

  
  
  template<typename...U>
  std::ostream& print(std::ostream& os, const char *stmt, std::basic_ostream<char, std::char_traits<char> >&(*fp)(std::basic_ostream<char, std::char_traits<char> >&), const U&...rest) const {
    std::basic_ostream<char, std::char_traits<char> >&(*flushPtr)(std::basic_ostream<char, std::char_traits<char> >&)=std::flush;
    std::basic_ostream<char, std::char_traits<char> >&(*endlPtr)(std::basic_ostream<char, std::char_traits<char> >&)=std::endl;
    std::basic_ostream<char, std::char_traits<char> >&(*endsPtr)(std::basic_ostream<char, std::char_traits<char> >&)=std::ends;
    
    if(fp==flushPtr){  //doesn't take %
      os<<fp;
      print(os,stmt,rest...);
      return os;
    }
    //takes %
    //if stmt empty
    if(!*(stmt))
      return print(os,fp,rest...);
    
    while(*(stmt)){
      if(*(stmt)=='%'){
        os<<fp;
        stmt++;
        return print(os,stmt,rest...);
      }
      else if(*(stmt)=='\\' && *(stmt+1)=='%'){
        os<<stmt[1];
        stmt+=2;
      }
      else{
        os<<stmt[0];
        stmt++;
      }

    }
  }

  
  template<typename T,typename...U>
  typename std::enable_if<!std::is_same<decltype(std::setprecision(std::declval<int>())), typename std::decay<T>::type>::value &&
                          !std::is_same<decltype(std::setw(std::declval<int>())), typename std::decay<T>::type>::value &&
                          !std::is_same<decltype(std::resetiosflags(std::ios_base::hex)), typename std::decay<T>::type>::value && 
                          !std::is_same<decltype(std::setiosflags(std::ios_base::hex)), typename std::decay<T>::type>::value &&
                          !std::is_same<decltype(std::setbase(std::declval<int>())), typename std::decay<T>::type>::value &&
                          !std::is_same<decltype(std::setfill(std::declval<char>())), typename std::decay<T>::type>::value, std::ostream &>::type
  print(std::ostream &os,const char *stmt, const T& t, const U&...rest) const{
    if(!*(stmt))
      print(os,t,rest...);
    
    while(*(stmt)){
      if(*(stmt)=='\\' && *(stmt+1)=='%'){
        os<<stmt[1];
        stmt+=2;
      }
      else if(*(stmt)=='%'){
        stmt++;
        os<<t;
        print(os,stmt, rest...);
        return os;
      } 
      else{
        os<<stmt[0];
        stmt++;
      }
    }
    return os;
  }
  
  template<std::size_t... indices>
  std::ostream& helper2(std::ostream &os,const char*stmt, std::index_sequence<indices...>) const{
    print(os,stmt, std::get<indices>(this->tup)...);
    return os;
  }
};

template<typename... Ts>
std::ostream &operator<<(std::ostream &os,const Interpolate_helper<Ts...> &ih){
  return ih.helper2(os, ih.stmt, std::make_index_sequence<std::tuple_size<decltype(ih.tup)>::value>{});
}


template<typename... Ts>
Interpolate_helper<Ts...> Interpolate(const char *s,const Ts&...t){
  Interpolate_helper<Ts...> ih(s,t...);
  return ih;
}

auto ffr(std::basic_ostream<char, std::char_traits<char>>& (*fp)(std::basic_ostream<char, std::char_traits<char>>&)){
	return fp;
}


}  //name space
#endif /* INTERPOLATE_HPP_ */
