

#include "helper.h"
#include "students_manager.h"
#include "courses_manager.h"

namespace Faculty {

shared_ptr<StudentFlowController> gStudentFlowController(new StudentFlowController());


bool StudentFlowController::IsValidUser(string user_name, string password)
{
   return gStudentsManager->GetUser(user_name, password) != nullptr;
}

void StudentFlowController::DoSignUp()
{
    shared_ptr<Student> student(new Student());
    while (true)
    {
        cout << "Enter user name: ";
        cin >> student->user_name_;

        cout << "Enter password: ";
        cin >> student->password_;
        if(IsValidUser(student->user_name_, student->password_))
        {
            cout << "\nERROR: User already exist...Try again\n\n";
        }
        else
        {
            break;
        }

    }
    cout << "Enter Full Name: ";
    // getline reads last \n
    do {
    getline(cin, student->full_name_);
    } while (student->full_name_.size() == 0);

    cout << "Enter Student ID: ";
    cin >> student->id_;

    cout << "Enter Email: ";
    cin >> student->email_;
    gStudentsManager->students_list_.push_back(student);

    cout<<"Signed up successfully!\n";
    current_student_=student;

}

/***
*If logged in correctly take control until user logout
***/
void StudentFlowController::TakeControl(string user_name, string password)
{
    current_student_ = gStudentsManager->GetUser(user_name, password);

    cout<<"\n\nWelcome "<< current_student_->full_name_ << ". You are logged in\n";
    ShowMainMenu();
}
void StudentFlowController::ShowMainMenu()
{
    vector <string> menu = { "Register in Course", "List My Courses", "View Course", "Grades Report", "Log out" };
    while(true)
    {
        int choice = Helper:: RunMenu(menu);

        if (choice == 1)
          RegisterInCourse();
        else if (choice == 2)
          ListMyCourses();
        else if (choice == 3)
          ViewCourse();
        else if (choice == 4)
          ShowGradesReport();
        else
          break;  // log out
    }

}

void StudentFlowController::RegisterInCourse()
{
    vector<shared_ptr<Course>> unregisteredCourses = gCoursesManager->GetUnregisteredCourses(current_student_->registered_courses_);
    int pos = 0;
    for(auto course : unregisteredCourses)
    {
        printf("%d) Course %s - Code %s\n",++pos, course->name_.c_str(), course->code_.c_str());
    }
    printf("Which ith [1 - %d] course to register? ", pos);
    int choice = Helper::ReadInt(1,pos)-1;
    current_course_ = unregisteredCourses[choice];

    /*link course - student*/
    LinkStudentToCourse();

    cout<<"\nRegistered Successfully\n";
}

void StudentFlowController::LinkStudentToCourse()
{
   current_student_->registered_courses_.push_back(current_course_);
   current_course_-> registered_students_.push_back(current_student_);

}

void StudentFlowController::ListMyCourses()
{
    if(current_student_->registered_courses_.size()==0)
    {
        cout << "No registered courses\n";
        return;
    }

    int num=1;
    for(auto course : current_student_->registered_courses_)
    {
        printf("%d) Course %s - Code %s Total Assignments: %d - ",num++,course->name_.c_str(),course->code_.c_str(),(int)course->assignments_.size());

        printf("submitted %d\n",current_student_->StudentSubmissionsForCourse(course));
    }

}

void StudentFlowController::ViewCourse()
{
    if(current_student_->registered_courses_.size()==0)
    {
        cout << "No registered courses\n";
        return;
    }
    ListMyCourses();
    printf("\nWhich ith [1 - %d] course to view? ", (int) current_student_->registered_courses_.size());
    int choice = Helper::ReadInt(1,current_student_->registered_courses_.size())-1;
    current_course_ = current_student_->registered_courses_[choice];

    /*print course summary*/
    printf("\nCourse %s with Code %s - ", current_course_->name_.c_str(), current_course_->code_.c_str());
    printf("taught by Doctor %s\n", current_course_->doctor_->name_.c_str());
    printf("Course has %d assignment\n", (int) current_course_->assignments_.size());

    int pos = 0;
    for(auto assignment: current_course_->assignments_)
    {
       cout << "Assignment " << ++pos << " ";
       shared_ptr<AssignmentSolution> solution=current_student_->GetAssignmentSolution(assignment);
       if(solution == nullptr)
       {
           cout << "NOT submitted - NA";
       }
       else
       {
           cout << "submitted - ";
           if(solution->is_graded_)
           {
               cout << solution->grade_;
           }
           else
           {
               cout << "NA";
           }

       }
       cout << " / " << assignment->max_grade_ << "\n";

    }
    ShowCourseMenu();
}

void StudentFlowController::ShowGradesReport()
{
    vector<tuple<string, int, float,int>> reports_vec = current_student_->ComputeGradesStatics();
    cout<<"\n";
    cout<<"number of submitted courses "<<reports_vec.size();
    cout<<" - number of submissions "<<current_student_->assignments_solutions_.size()<<endl;
    int pos=0;
    for(auto tuple_data : reports_vec)
    {
       printf("%d) code %s - Total submitted %d assignments - Grade %0.1f / %d\n",++pos, get<0>(tuple_data).c_str(),(int)get<1>(tuple_data),(float)get<2>(tuple_data),(int)get<3>(tuple_data));
    }
}

void StudentFlowController::SubmitCourseAssignment()
{
    if(current_course_->assignments_.size()==0)
    {
        cout<<"No Assignments";
        return ;
    }
    printf("Which ith [1 - %d] assignmet to submit?",(int) current_course_->assignments_.size());

    int choice= Helper::ReadInt(1,current_course_->assignments_.size())-1;

    shared_ptr<AssignmentSolution> addedSolution(new AssignmentSolution());

    cout << "Enter the solution (no space)\n";
    cin>>addedSolution->answer_;

    //if there is an old solution remove it
    //create a reference to the assign sol instead of using large name
    vector<shared_ptr<AssignmentSolution>> &oldSolution= current_student_->assignments_solutions_;
    for(int i =0; i< (int)oldSolution.size() ;i++)
    {
        if(oldSolution[i]->assignment_ == current_course_->assignments_[choice])
        {
            //remove old solution from course and student
            vector<shared_ptr<AssignmentSolution>> &oldSolution2= current_course_->assignments_[choice]->assignment_solutions_;
            for(int j =0; j< (int)oldSolution2.size() ;j++)
            {
                if(oldSolution2[j]->assignment_ == oldSolution[i]->assignment_)
                {
                    oldSolution2.erase(oldSolution2.begin()+i);
                    break;
                }
            }

            oldSolution.erase(oldSolution.begin()+i);
            break;
        }
    }

    /*link assignment solution to student,course and assignment*/
    LinkAssignmentSolution(addedSolution, choice);
}
void StudentFlowController::LinkAssignmentSolution(shared_ptr<AssignmentSolution> addedSolution, int choice)
{
    addedSolution->is_graded_=false;
    addedSolution->doctor_comments_="No comments";
    addedSolution->student_=current_student_;
    addedSolution->assignment_=current_course_->assignments_[choice];
    current_student_->assignments_solutions_.push_back(addedSolution);
    current_course_->assignments_[choice]->assignment_solutions_.push_back(addedSolution);

}

void StudentFlowController::ShowCourseMenu()
{
    vector<string> menu = { "UnRegister from Course", "Submit solution", "Back" };

    while (true)
    {
        int choice = Helper::RunMenu(menu);

        if (choice == 1) {
          UnRegisterFromCourse();
          break;
        }
        else if (choice == 2)
          SubmitCourseAssignment();
        else
          break;  // go to the previous menu
    }
}

void StudentFlowController::UnRegisterFromCourse()
{
    //Remove course from 2 sides
    Helper::RemoveElement(current_course_->registered_students_, current_student_);
    Helper::RemoveElement(current_student_->registered_courses_, current_course_);
    printf("\n Unregister from Course %s with Code %s succsesfully!\n", current_course_->name_.c_str(),current_course_->code_.c_str() );
}

}





