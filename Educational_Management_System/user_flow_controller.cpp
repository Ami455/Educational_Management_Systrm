

#include "helper.h"
#include "user_flow_controller.h"

namespace Faculty {

shared_ptr<UserFlowController> gUserFlowController (new UserFlowController());

void UserFlowController::ShowMainMenu()
{
    vector<string> menu{"Login", "Sign up", "Shutdown system"};
    while(true)
    {
        int option =Helper::RunMenu(menu);
        if(option == 1)
            DoLogin();
        else if(option == 2)
            DoSignUp();
        else if(option == 3)
            break;
        else
            assert(false);
    }

}
void UserFlowController::DoLogin()
{
    cout<<"\nPlease enter user name and password:\n";

    string username;
    string password;

    cout<<"User Name: ";
    cin>>username;

    cout<<"Password: ";
    cin>>password;

    if(gStudentFlowController->IsValidUser(username, password))
        gStudentFlowController->TakeControl(username, password);
    else if(gDoctorFlowController->IsValidUser(username, password))
        gDoctorFlowController->TakeControl(username, password);
    else
    {
        cout<<"ERROR: Invalid login data...Try again\n";
        DoLogin();
    }
}
void UserFlowController::DoSignUp()
{
    cout<<"Please enter user type: (1 - student), (2 - doctor):\n";
    int type = Helper::ReadInt(1, 2);

    if(type == 1)
    {
        gStudentFlowController->DoSignUp();
        gStudentFlowController->TakeControl(gStudentFlowController->current_student_->user_name_,gStudentFlowController->current_student_->password_);
    }
    else if(type == 2)
    {
        gDoctorFlowController->DoSignUp();
        gDoctorFlowController->TakeControl(gDoctorFlowController->current_doctor_->user_name_,gDoctorFlowController->current_doctor_->password_);
    }
    else
        assert(false);
}
}
