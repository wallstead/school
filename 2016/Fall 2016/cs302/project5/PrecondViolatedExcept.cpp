/**
 * @file PrecondViolatedExcept.cpp
 *
 * @brief Implementation file for the PrecondViolatedExcept class
 *
 * @author Someone at Pearson (I didn't code any of this)
 *
 * @details Specifies function of the class.
 *
 * @version 0.10
 *
 */
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include "PrecondViolatedExcept.h"

PrecondViolatedExcept::PrecondViolatedExcept(const std::string& message)
: std::logic_error("Precondition Violated Exception: " + message)
{
}  // end constructor
