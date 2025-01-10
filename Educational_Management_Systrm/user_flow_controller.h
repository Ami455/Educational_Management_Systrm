#ifndef USER_FLOW_CONTROLLER_H_INCLUDED
#define USER_FLOW_CONTROLLER_H_INCLUDED

namespace Faculty {

struct UserFlowController {
    /***
    * Major function to run the application
    ***/
    void ShowMainMenu();
    void DoLogin();
    void DoSignUp();

};

extern shared_ptr<UserFlowController> gUserFlowController;
}
#endif // USER_FLOW_CONTROLLER_H_INCLUDED
