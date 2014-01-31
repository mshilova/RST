#include "countint.hpp"
#include <cstdlib>
#include <iostream>

/** Implementation of the countint class
 *  See: countint.hpp
 *  @author Paul Kube (c) 2013
 */

unsigned long countint::count = 0;  // define  static count variable

void countint::clearcount() {
  count = 0;
}

unsigned long countint::getcount() {
  return count;
}
  
int countint::getval() const {
  return i;
}

bool countint::operator<(countint const & o) const {
    count++;
    ///std::cout<<"COUNTER incremented"<<std::endl;
    return i < o.i;
}
//bool countint::operator>(countint const & o) const {
    //count++;
  //  return i >  o.i;
//}
//bool countint::operator==(countint const & o) const  {
  //  return i==o.i; 
//}
//bool countint::operator!=(countint const & o) const {
  //  return !(i!=o.i);
//}

std::ostream& operator<<(std::ostream& stm, const countint& i) {
    stm << i.getval();
    return stm;
}

