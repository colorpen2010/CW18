#include <iostream>
#include <string>
#include <limits>
#define NOMINMAX
#include <windows.h>

using namespace std;

class Student
{
private:
    string name;
    int age;

public:
    Student()
    {
        name = "";
        age = 0;
    }

    Student(string studentName, int studentAge)
    {
        name = studentName;
        age = studentAge;
    }

    string getName()
    {
        return name;
    }

    int getAge()
    {
        return age;
    }

    void setName(string studentName)
    {
        name = studentName;
    }

    void setAge(int studentAge)
    {
        age = studentAge;
    }
};

class Group
{
private:
    string name;
    Student* students;
    int count;

public:
    Group()
    {
        name = "Без названия";
        students = nullptr;
        count = 0;
    }

    Group(string groupName)
    {
        name = groupName;
        students = nullptr;
        count = 0;
    }

    ~Group()
    {
        delete[] students;
    }

    string getName()
    {
        return name;
    }

    void setName(string groupName)
    {
        name = groupName;
    }

    int getStudentCount()
    {
        return count;
    }

    void addStudent(string studentName, int age)
    {
        Student* newStudents = new Student[count + 1];

        for (int i = 0; i < count; i++)
        {
            newStudents[i] = students[i];
        }

        newStudents[count] = Student(studentName, age);
        delete[] students;
        students = newStudents;
        count++;

        cout << "Студент добавлен.\n";
    }

    void removeStudent(int number)
    {
        if (number < 1 || number > count)
        {
            cout << "Нет студента с таким номером.\n";
            return;
        }

        Student* newStudents = nullptr;
        if (count > 1)
        {
            newStudents = new Student[count - 1];
        }

        int newIndex = 0;
        for (int i = 0; i < count; i++)
        {
            if (i != number - 1)
            {
                newStudents[newIndex] = students[i];
                newIndex++;
            }
        }

        delete[] students;
        students = newStudents;
        count--;

        cout << "Студент удалён.\n";
    }

    void showStudents()
    {
        cout << "\nГруппа: " << name << '\n';

        if (count == 0)
        {
            cout << "В группе пока нет студентов.\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            cout << i + 1 << ". " << students[i].getName()
                 << ", возраст: " << students[i].getAge() << '\n';
        }
    }
};

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Group* group = nullptr;
    int choice;

    do
    {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Создать новую группу\n";
        cout << "2. Добавить студента\n";
        cout << "3. Удалить студента\n";
        cout << "4. Показать студентов\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите число из меню.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
        {
            string groupName;
            cout << "Введите название группы: ";
            getline(cin, groupName);

            delete group;
            group = new Group(groupName);
            cout << "Группа создана.\n";
        }
        else if (choice == 2)
        {
            if (group == nullptr)
            {
                cout << "Сначала создайте группу.\n";
                continue;
            }

            string studentName;
            int age;
            cout << "Введите имя студента: ";
            getline(cin, studentName);
            cout << "Введите возраст: ";

            if (!(cin >> age) || age < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Возраст должен быть неотрицательным числом.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            group->addStudent(studentName, age);
        }
        else if (choice == 3)
        {
            if (group == nullptr)
            {
                cout << "Сначала создайте группу.\n";
                continue;
            }

            group->showStudents();
            if (group->getStudentCount() > 0)
            {
                int number;
                cout << "Введите номер студента для удаления: ";
                if (!(cin >> number))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Введите число.\n";
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                group->removeStudent(number);
            }
        }
        else if (choice == 4)
        {
            if (group == nullptr)
            {
                cout << "Сначала создайте группу.\n";
            }
            else
            {
                group->showStudents();
            }
        }
        else if (choice != 0)
        {
            cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);

    delete group;
    cout << "Программа завершена.\n";
    return 0;
}
