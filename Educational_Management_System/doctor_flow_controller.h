#ifndef DOCTOR_FLOW_CONTROLLER_H_INCLUDED
#define DOCTOR_FLOW_CONTROLLER_H_INCLUDED


namespace Faculty {

struct DoctorFlowController {

    bool IsValidUser(string user_name, string password);
    void DoSignUp();
    void TakeControl(string user_name, string password);
    void ShowMainMenu();
    void ListMyCourses();
    void CreateCourse();
    void ViewCourse();

    void ShowCourseOperationsMenu();
    void AddTAs();
    void ListAssignments();
    void CreateAssignment();
    void ViewAssignment();

    void ShowAssignmentsOperationsMenu();
    void ShowGradesReport();
    void ListSolutions();
    void ViewSolution();

    void ShowAssignmentsSolutionOperationsMenu();
    void ShowInfo();
    void SetGrade();
    void SetComment();


    shared_ptr<Doctor> current_doctor_;
    shared_ptr<Course> current_course_;
    shared_ptr<Assignment> current_assignment_;
    shared_ptr<AssignmentSolution>current_solution_;

};

extern shared_ptr<DoctorFlowController> gDoctorFlowController;
}
#endif // DOCTOR_FLOW_CONTROLLER_H_INCLUDED
