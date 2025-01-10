#ifndef STUDENT_FLOW_CONTROLLER_H_INCLUDED
#define STUDENT_FLOW_CONTROLLER_H_INCLUDED


namespace Faculty {

struct StudentFlowController {
    void DoSignUp();
    bool IsValidUser(string user_name, string password);

    void TakeControl(string user_name, string password);
    void ShowMainMenu();
    void ShowCourseMenu();
    void RegisterInCourse();
    void LinkStudentToCourse();
    void UnRegisterFromCourse();
    void SubmitCourseAssignment();
    void ListMyCourses();
    void ViewCourse();
    void LinkAssignmentSolution(shared_ptr<AssignmentSolution> addedSolution, int choice);
    void ShowGradesReport();

    shared_ptr<Student> current_student_;
    shared_ptr<Course> current_course_;
};

extern shared_ptr<StudentFlowController> gStudentFlowController;

}
#endif // STUDENT_FLOW_CONTROLLER_H_INCLUDED
