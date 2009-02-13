#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>

#define TRACE std::cout << __FILE__ << ":" << __LINE__ << std::endl
#define TRACE1(x) std::cout << #x << ": [" << x << "]" << std::endl
#define TRACE2(x, y) std::cout << x << ": [" << y << "]" << std::endl

#endif /* COMMON_H_ */

