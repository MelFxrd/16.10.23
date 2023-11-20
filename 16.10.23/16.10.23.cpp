#include <iostream>
#include <regex>

class AbstractUser {
protected:
    std::string login;
    std::string fullName;
    std::string password;
    std::string creationDate;

public:
    AbstractUser(const std::string& login, const std::string& fullName, const std::string& password)
        : login(login), fullName(fullName), password(password) {}

    virtual ~AbstractUser() {}

    const std::string& getLogin() const {
        return login;
    }

    bool isPasswordValid() const {
        std::regex uppercaseRegex("[A-Z]");
        std::regex digitRegex("[0-9]");
        std::regex specialCharRegex("[!@#$%^&*()_+\\-=\\[\\]{};':\",./<>?]");
        return std::regex_search(password, uppercaseRegex)
            && std::regex_search(password, digitRegex)
            && std::regex_search(password, specialCharRegex)
            && password.length() >= 8;
    }
};

class User : public AbstractUser {
private:
    std::string creationDate;
    std::string gender;
    double balance;

public:
    User(const std::string& login, const std::string& fullName, const std::string& password,
        const std::string& creationDate, const std::string& gender, double balance)
        : AbstractUser(login, fullName, password), creationDate(creationDate), gender(gender), balance(balance) {}

    void displayInfo() const {
        std::cout << "Логин: " << getLogin() << "\n"
            << "ФИО: " << fullName << "\n"
            << "Дата создания: " << creationDate << "\n"
            << "Пол: " << gender << "\n"
            << "Баланс: " << balance << "\n";
    }
};

class Admin : public AbstractUser {
private:
    bool isSuperAdmin;

public:
    Admin(const std::string& login, const std::string& fullName, const std::string& password, bool isSuperAdmin)
        : AbstractUser(login, fullName, password), isSuperAdmin(isSuperAdmin) {}

    void deleteUser(User& user) {
        std::cout << "Администратор " << getLogin() << " удалил пользователя: " << user.getLogin() << "\n";
    }
};

int main() {
    User regularUser("user123", "Иван Иванов", "Abc123!@#", "2023-11-20", "М", 100.0);
    Admin adminUser("admin", "Админ Админович", "AdminPass123!@#", true);

    if (regularUser.isPasswordValid()) {
        std::cout << "Пароль обычного пользователя действителен.\n";
    }
    else {
        std::cout << "Пароль обычного пользователя недействителен.\n";
    }

    regularUser.displayInfo();

    adminUser.deleteUser(regularUser);

    return 0;
}