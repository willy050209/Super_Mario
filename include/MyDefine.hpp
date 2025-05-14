#pragma once

#ifndef MYDEFINE_HPP
#define MYDEFINE_HPP

#define CANNOTCREATE(ClassType)\
	ClassType() = delete;\
	ClassType(const ClassType&) = delete;\
	ClassType(ClassType&&) = delete;\
	ClassType& operator=(const ClassType&) = delete;\
	ClassType& operator=(ClassType&&) = delete;\
	~ClassType() = delete

#endif