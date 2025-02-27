#ifndef FORMPROFILE_HPP
#define FORMPROFILE_HPP

#include "FormProfile.hpp"
#include "MyContext.hpp"

constexpr auto FORMPROFILE_FILE = "Form Profile";

void readFormProfile() noexcept;

void writeFormProfile(std::shared_ptr<Core::Context>& context)noexcept;

#endif // !FORMPROFILE_HPP
