
#include "helper.h"

#include "students_manager.h"
#include "doctors_manager.h"
#include "courses_manager.h"



using Faculty::gCoursesManager;

void GenerateRandomData()
{
    // Generate system users
    Faculty::gStudentsManager->AddDummyData();
    Faculty::gDoctorsManager->AddDummyData();
    gCoursesManager->AddDummyData();

    // Connect the objects
    gCoursesManager->AddDummyDataRelationships();
}
int main()
{
    GenerateRandomData();

    Faculty::gStudentsManager->ShowStudents();
	Faculty::gDoctorsManager->ShowDoctors();
	Faculty::gCoursesManager->ShowCourses();

    Faculty::gUserFlowController->ShowMainMenu();

    return 0;
}





