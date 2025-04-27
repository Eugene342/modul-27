#include <iostream>
#include <string> 
#include <vector>
#include <cstdlib>
#include <ctime> 
#include <algorithm>
class Employee // базовый класс для всех сотрудников
{
public:
    std::string name; // имя
    bool isBusy; // состояние (занят или нет)
    Employee(std::string name): name(name), isBusy(false) // конструктор
    {
    }
    virtual void receiveTask(int taskId) = 0;
};
class Worker: public Employee // производный класс для рабочих
{
public:
    Worker(std::string name) : Employee(name) // конструктор
    {
    }
    void receiveTask(int taskId) override // получение рабочим задачи
    {
        isBusy = true;
        std::cout << "Worker " << name << " received the task " << taskId << std::endl;
    }
};
class Manager : public Employee // производный класс для менеджеров
{
public:
    std::vector<Worker*> workers;
    Manager(std::string name): Employee(name) // конструктор
    {
    }
    void addWorker(Worker* worker)
    {
        workers.push_back(worker);
    }
    void receiveTask(int taskId) override // получение рабочим задачи
    {
        int hash = taskId + 1; // Пример хеширования
        std::srand(hash);
        int taskCount = rand() % (workers.size() + 1);
        std::cout << "Manager " << name << " breaks the task into " << taskCount << " subtasks" << std::endl; // деление менеджером задачи на несколько подзадач
        std::vector<int> availableWorkers;
        for (int i = 0; i < workers.size(); ++i)
        {
            if (!workers[i]->isBusy)
            {
                availableWorkers.push_back(i);
            }
        }
        random_shuffle(availableWorkers.begin(), availableWorkers.end());
        for (int i = 0; i < taskCount && i < availableWorkers.size(); ++i)
        {
            workers[availableWorkers[i]]->receiveTask(taskId + i);
        }
    }
};
class Team // класс для команды
{
public:
    Manager* manager;
    std::vector<Worker*> workers;
    Team(Manager* manager) : manager(manager)
    {
    }
    void addWorker(Worker* worker)
    {
        workers.push_back(worker);
    }
    void assignTask(int taskId)
    {
        manager->receiveTask(taskId);
    }
};
class Company // класс для компании
{
public:
    std::vector<Team*> teams;
    void addTeam(Team* team)
    {
        teams.push_back(team);
    }
    void issueCommand(int commandId)
    {
        for (auto& team : teams)
        {
            team->assignTask(commandId);
        }
    }
};
int main()
{
    int numTeams, numWorkersPerTeam;
    std::cout << "Enter the count of the teams and the count of the workers in each team: ";
    std::cin >> numTeams >> numWorkersPerTeam;
    Company company;
    for (int i = 0; i < numTeams; ++i)
    {
        std::string managerName = "Manager_" + std::to_string(i + 1);
        Manager* manager = new Manager(managerName);
        Team* team = new Team(manager);
        for (int j = 0; j < numWorkersPerTeam; ++j)
        {
            std::string workerName = "Worker_" + std::to_string(i + 1) + "_" + std::to_string(j + 1);
            Worker* worker = new Worker(workerName);
            team->addWorker(worker);
            manager->addWorker(worker);
        }
        company.addTeam(team);
    }
    std::cout << "Enter integer numbers for the instructions of the head of the company (0 for exit): " << std::endl;
    int commandId;
    while (std::cin >> commandId && commandId != 0)
    {
        company.issueCommand(commandId);
    }
    return 0;
}

