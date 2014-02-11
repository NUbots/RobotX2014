/* 
 * File:   Utils.h
 * Author: Andrew
 *
 * Created on 20 December 2013, 2:05 PM
 */

#ifndef UTILS_H
#define	UTILS_H
#include <armadillo>
namespace duti { //Dabson UTIlity functions (stateless, no class needed)
const double PI = 4.0*atan(1.0);     //needed in Kalman.cpp
bool isMatrixValid(arma::mat m);
}
#endif	/* UTILS_H */
