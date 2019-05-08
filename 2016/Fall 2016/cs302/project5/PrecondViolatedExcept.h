/**
 * @file PrecondViolatedExcept.h
 *
 * @brief Header file for the PrecondViolatedExcept class
 *
 * @author Someone at Pearson (I didn't code any of this)
 *
 * @details Specifies the members of the Node class and defines function parameters
 *
 * @version 0.10
 *
 */
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#ifndef PRECOND_VIOLATED_EXCEPT_
#define PRECOND_VIOLATED_EXCEPT_

#include <stdexcept>
#include <string>

class PrecondViolatedExcept : public std::logic_error
{
public:
    PrecondViolatedExcept(const std::string& message = "");
}; // end PrecondViolatedExcept
#endif
