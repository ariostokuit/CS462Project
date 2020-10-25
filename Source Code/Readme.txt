Compile and run code using GitBash and MinGW:
1. Go to source folder and open GitBash
2. Type and enter "g++ -o main.exe main.cpp -I. UI/SimpleUI.cpp UI/SystemDriverUI.cpp UI/UserInterfaceHandler.cpp Domain/Session/Session.cpp Domain/Session/SessionHandler.cpp TechnicalServices/Logging/LoggerHandler.cpp TechnicalServices/Persistence/PersistenceHandler.cpp TechnicalServices/Persistence/SimpleDB.cpp -std=c++17"  into GitBash console to compile
3. Type and enter "./main" into GitBash to run code

   Username Password Roles
1. James    Vu       Customer
2. Jakob    Patino   Store Employee
3. Ariosto  Kuit     IT Employee
4.                   Customer, Store Employee, IT Employee, Corporate Employee
