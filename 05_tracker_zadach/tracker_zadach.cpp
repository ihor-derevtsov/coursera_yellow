#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

TaskStatus GetNextStatus(const TaskStatus& status) {
    if (status == TaskStatus::NEW) { return TaskStatus::IN_PROGRESS; }
    if (status == TaskStatus::IN_PROGRESS) { return TaskStatus::TESTING; }
    if (status == TaskStatus::TESTING) { return TaskStatus::DONE; }
    else { return TaskStatus::NEW; }
}

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return tasks_of_person.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        ++tasks_of_person[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        if (tasks_of_person.count(person) == 0) { return {{}, {}};}

        int working_on_tasks{0};
        int counter_of_tasks{0};
        TasksInfo updated_tasks{}, untouched_tasks{};
        TasksInfo current_person = GetPersonTasksInfo(person);

        for (const auto& [status, value] : current_person) { if (status != TaskStatus::DONE) { working_on_tasks += value; } }
        if (task_count > working_on_tasks) { task_count = working_on_tasks; }
        for (const auto& pair : current_person) {
            if (pair.first != TaskStatus::DONE) {
                for (int i{0}; i < pair.second; ++i) {
                    if (counter_of_tasks < task_count) {
                        ++counter_of_tasks;
                        auto next_status = GetNextStatus(pair.first);
                        ++updated_tasks[next_status];

                        --tasks_of_person[person][pair.first];
                        ++tasks_of_person[person][next_status];
                    } else { ++untouched_tasks[pair.first]; }
                }
            }
        }
        remove_empty_pairs(updated_tasks);
        remove_empty_pairs(untouched_tasks);
        remove_empty_pairs(tasks_of_person[person]);
        return make_tuple(updated_tasks, untouched_tasks);
    }

    void remove_empty_pairs(TasksInfo& tasks) {
        for(auto it = tasks.begin(); it != tasks.end(); )
        if(it->second == 0) { it = tasks.erase(it); }
        else { ++it; }
    }

//     // Функция для удаления нулей из словаря
// void RemoveZeros(TasksInfo& tasks_info) {
//   // Соберём те статусы, которые нужно убрать из словаря
//   vector<TaskStatus> statuses_to_remove;
//   for (const auto& task_item : tasks_info) {
//     if (task_item.second == 0) {
//       statuses_to_remove.push_back(task_item.first);
//     }
//   }
//   for (const TaskStatus status : statuses_to_remove) {
//     tasks_info.erase(status);
//   }
// }

private:
    map<string, TasksInfo> tasks_of_person;
};




// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}


