

#include "helper.h"
#include "doctors_manager.h"
#include "courses_manager.h"

namespace Faculty {

shared_ptr<DoctorFlowController> gDoctorFlowController(new DoctorFlowController());

bool DoctorFlowController::IsValidUser(string user_name, string password)
{
    return gDoctorsManager->GetUser(user_name,password) != nullptr;
}
void DoctorFlowController::DoSignUp()
{
    shared_ptr<Doctor> doctor(new Doctor());

    while (true) {

        cout << "Enter user name: ";
        cin >> doctor->user_name_;

        cout << "Enter password: ";
        cin >> doctor->password_;

        if (IsValidUser(doctor->user_name_, doctor->password_))
        cout << "\nERROR: User already exist...Try again\n\n";
        else
        break;
    }

    cout << "Enter Full Name: ";
    // getline reads last \n
    do {
    getline(cin, doctor->name_);
    } while (doctor->name_.size() == 0);

    cout << "Enter Doctor ID: ";
    cin >> doctor->id_;

    cout << "Enter Email: ";
    cin >> doctor->email_;

    gDoctorsManager->doctors_list_.push_back(doctor);
    cout<<"Signed up successfully!\n";
    current_doctor_=doctor;

}

void DoctorFlowController::TakeControl(string user_name, string password)
{
    current_doctor_ = gDoctorsManager->GetUser(user_name,password);
    printf("\n\nWelcom Dr.%s . Your are logged in\n", current_doctor_->name_.c_str());
    ShowMainMenu();
}
void DoctorFlowController::ShowMainMenu()
{
    vector<string> menu = { "List Courses", "Create Course", "View Course", "Log out" };

    while(true)
    {
        int choice = Helper:: RunMenu(menu);

        if (choice == 1)
        {
            ListMyCourses();
        }
        else if (choice == 2)
        {
            CreateCourse();
        }
        else if (choice == 3)
           ViewCourse();

        else
          break;  // log out
    }
}

void DoctorFlowController::ListMyCourses()
{
    if(current_doctor_->teaching_courses_.size()==0)
    {
        cout << "No Teaching Courses\n";
        return;
    }
    cout << "\n\nMy Courses list: \n";

    int pos = 1;

    for (auto course : current_doctor_->teaching_courses_)
        printf("%d) Course %s - Code %s\n", pos++, course->name_.c_str(), course->code_.c_str());

}
void DoctorFlowController::CreateCourse()
{
    shared_ptr<Course> course(new Course());
    course = gCoursesManager->AddCourse();
    //link course doctor
    course->doctor_=current_doctor_;
    //link doctor course
    current_doctor_->teaching_courses_.push_back(course);

    printf("Course %s - code %s is added successfully\n",course->name_.c_str(),course->code_.c_str());

}
void DoctorFlowController::ViewCourse()
{
    if(current_doctor_->teaching_courses_.size()==0)
    {
        cout << "No Teaching Courses\n";
        return;
    }
    ListMyCourses();
    printf("\nWhich ith [1 - %d] course to view? ", (int) current_doctor_->teaching_courses_.size());

    int choice = Helper::ReadInt(1, current_doctor_->teaching_courses_.size())-1;
    current_course_=current_doctor_->teaching_courses_[choice];
    //print course summary
    printf("\nCourse %s with Code %s - ", current_course_->name_.c_str(), current_course_->code_.c_str());
    printf("Number of Registered Students: %d\n",(int)current_course_->registered_students_.size());
    printf("Course has %d assignment\n", (int) current_course_->assignments_.size());

    ShowCourseOperationsMenu();
}


void DoctorFlowController::ShowCourseOperationsMenu()
{
    vector<string> menu = { "Add TAs", "List Assignments", "Create Assignment", "View Assignment", "Back" };

    while(true)
    {
        int choice = Helper:: RunMenu(menu);

        if (choice == 1)
        {
            AddTAs();
        }
        else if (choice == 2)
        {
            ListAssignments();
        }
        else if (choice == 3)
        {
            CreateAssignment();
        }
        else if (choice == 4)
        {
            ViewAssignment();
        }
        else
          break;  // return
    }
}


void DoctorFlowController::AddTAs()
{

}
void DoctorFlowController::ListAssignments()
{
    if(current_course_->assignments_.size()==0)
    {
        printf("No Assignment for %s course\n",current_course_->name_.c_str());
        return;
    }
    printf("\n\nCourse %s has %d Assignments: \n",current_course_->name_.c_str(),(int)current_course_->assignments_.size());

    int pos = 1;

    for (auto assignment : current_course_->assignments_)
        printf("%d) Assignment Content: %s - Max grade: %d - number of submissions: %d\n", pos++, assignment->content_.c_str(), assignment->max_grade_,(int) assignment->assignment_solutions_.size());

}
void DoctorFlowController::CreateAssignment()
{
    shared_ptr<Assignment> assignment(new Assignment());
    cout<<"Add Assignmet content: ";
    cin>>assignment->content_;

    cout<<"Add Assignmet max grade: ";
    cin>>assignment->max_grade_;

    //link Course - Assignment
    current_course_->assignments_.push_back( assignment);
    //link Assignment - Courses
    assignment->course_=current_course_;

    cout<<"Assignment is added successfully\n";

}
void DoctorFlowController::ViewAssignment()
{
    if(current_course_->assignments_.size()==0)
    {
        printf("No Assignment for %s course\n",current_course_->name_.c_str());
        return;
    }
    ListAssignments();
    printf("\nWhich ith [1 - %d] Assignment to view? ", (int) current_course_->assignments_.size());

    int choice = Helper::ReadInt(1, current_course_->assignments_.size())-1;
    current_assignment_=current_course_->assignments_[choice];
    //print assignment summary

    printf("\Assignment content %-15s ", current_assignment_->content_.c_str());
    printf("Max grade %d\n", current_assignment_->max_grade_);

    printf("Number of submitted solutions: %d\n",(int)current_assignment_->assignment_solutions_.size());

    ShowAssignmentsOperationsMenu();

}


void DoctorFlowController::ShowAssignmentsOperationsMenu()
{
    vector<string> menu = { "Show Grades Report", "List Solutions", "View Solution", "Back" };

    while(true)
    {
        int choice = Helper:: RunMenu(menu);

        if (choice == 1)
        {
            ShowGradesReport();
        }
        else if (choice == 2)
        {
            ListSolutions();
        }
        else if (choice == 3)
        {
            ViewSolution();
        }
        else
          break;  // return
    }
}
void DoctorFlowController::ShowGradesReport()
{
    int pos=0;
    for(auto course : current_doctor_->teaching_courses_)
    {
       printf("%d) Course %-15s - Code %s , Total assignments grades: %d \n", ++pos,course->name_.c_str(),course->code_.c_str(),course->GetTotalAssignmentsGradesSum());
    }
    pos=0;
    cout<<"\nDetails:\n\n";
    for(auto course : current_doctor_->teaching_courses_)
    {
        printf("%d) Course %-15s - Code %s :", ++pos,course->name_.c_str(),course->code_.c_str());
        printf("\tTotal Assignments : %d\n",(int) course->assignments_.size());

        int pos2=0;
        //cout<<"\nloop on students\n"

        for(auto student : course->registered_students_)
        {
            vector<tuple<string, int, float,int>> reports_vec = student->ComputeGradesStatics();

            for(auto tuple_data : reports_vec)
            {
                if(get<0>(tuple_data)==course->code_)
                {
                    printf("\t%d)student : %-15s Course Grade: %d / %d\n",++pos2, student->full_name_.c_str(), (float)get<2>(tuple_data),(int)get<3>(tuple_data));
                    break;
                }
            }

        }

    }
}
void DoctorFlowController::ListSolutions()
{
    if(current_assignment_->assignment_solutions_.size()==0)
    {
        printf("No Solutions for Assignment\n");
        return;
    }
   printf("\nAssignments has %d Solutions: \n",(int)current_assignment_->assignment_solutions_.size());

    int pos = 0;

    for (auto solution : current_assignment_->assignment_solutions_)
    {
        printf("\nstudent %-15s - Id: %s    submitted the solution %d", solution->student_->full_name_.c_str(),solution->student_->id_.c_str(),++pos);
        cout<<"\tSolution status: ";
        solution->is_graded_ == true ?cout<<"graded": cout<<"not graded";
    }
}
void DoctorFlowController::ViewSolution()
{
    if(current_assignment_->assignment_solutions_.size()==0)
    {
        printf("No Solutions for Assignment\n");
        return;
    }
    ListSolutions();
    printf("\n\nWhich ith [1 - %d] Solutions to view? \n", (int) current_assignment_->assignment_solutions_.size());

    int choice = Helper::ReadInt(1, current_assignment_->assignment_solutions_.size())-1;
    current_solution_=current_assignment_->assignment_solutions_[choice];

    //print solution summary
    printf("student submitted the solution: %s - Id: %s", current_solution_->student_->full_name_.c_str(),current_solution_->student_->id_.c_str());
    cout<<"\nSolution status: ";
    (current_solution_->is_graded_ == true)?cout<<"graded": cout<<"not graded";

    printf("\ngrade: %0.1f \n", current_solution_->grade_);
    printf("Doctor Comment: %s \n", current_solution_->doctor_comments_.c_str());


    ShowAssignmentsSolutionOperationsMenu();

}
void DoctorFlowController::ShowAssignmentsSolutionOperationsMenu()
{
    vector<string> menu = { "Show Info", "Set Grade", "Set a Comment", "Back" };

    while(true)
    {
        int choice = Helper:: RunMenu(menu);

        if (choice == 1)
        {
            ShowInfo();
        }
        else if (choice == 2)
        {
            SetGrade();
        }
        else if (choice == 3)
        {
            SetComment();
        }
        else
          break;  // return
    }
}
void DoctorFlowController::ShowInfo()
{
    printf("\nanswer %s \ngrade = %0.1f\nComment: %s", current_solution_->answer_.c_str(),current_solution_->grade_,current_solution_->doctor_comments_.c_str());
}
void DoctorFlowController::SetGrade()
{
    cout<<"\nSet a grade ";
    cin>>current_solution_->grade_;
    cout<< "\ngrade set to "<<current_solution_->grade_;
    current_solution_->is_graded_=true;
}
void DoctorFlowController::SetComment()
{
    cout<<"\nWrite your comment: ";
    current_solution_->doctor_comments_="";//erase old comment
    do{
    getline(cin,current_solution_->doctor_comments_);
    }while(current_solution_->doctor_comments_.size()==0);

}


}
