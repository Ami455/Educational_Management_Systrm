#ifndef ASSIGNMENT_SOLUTION_H_INCLUDED
#define ASSIGNMENT_SOLUTION_H_INCLUDED


namespace Faculty {

struct AssignmentSolution{
float grade_;
bool is_graded_;
string answer_;
string doctor_comments_;
shared_ptr <Student> student_;
shared_ptr <Assignment> assignment_;
};

}

#endif // ASSIGNMENT_SOLUTION_H_INCLUDED
