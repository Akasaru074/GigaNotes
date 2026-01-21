# Giga Notes (Qt Quick + C++)

Легковесный менеджер заметок с поддержкой Markdown и локальным хранилищем SQLite.

## 🚀 Особенности

* **Архитектура MVVM:** Четкое разделение бизнес-логики (C++) и интерфейса (QML).
* **Стек технологий:** Qt 6, QML, SQLite, C++17.
* **Хранение данных:** Локальная база данных SQLite (создается автоматически).
* **Markdown:** Поддержка форматирования при просмотре заметок.
* **Интерфейс:** Адаптивный UI на базе Material Design.

## 🛠 Сборка и запуск

### Требования
* Qt 6.2+ (Core, Quick, Sql)
* CMake 3.16+
* Компилятор с поддержкой C++17 (MSVC, GCC, Clang)

### Инструкция
1.  Клонируйте репозиторий:
    ```bash
    git clone [https://github.com/your-username/notes-manager.git](https://github.com/your-username/notes-manager.git)
    cd notes-manager
    ```
2.  Откройте `CMakeLists.txt` в Qt Creator ИЛИ соберите вручную:
    ```bash
    mkdir build && cd build
    cmake ..
    cmake --build .
    ```
3.  Запустите исполняемый файл `NotesManager`.

## 🏗 Архитектура проекта

Проект следует принципам Clean Architecture:

* **Entities (`src/entities`):** Простые структуры данных (`Note`).
* **Database Layer (`src/database`):** Singleton-класс `DatabaseManager` для прямых SQL-запросов. Использует `QSqlDatabase`.
* **Model Layer (`src/models`):** `NotesModel` (наследник `QAbstractListModel`). Служит мостом между БД и QML. Реализует методы `addNote`, `updateNote`, `removeNote`.
* **UI Layer (`resources/qml`):** Интерфейс на QML + QtQuick Controls 2 (Material Style).

## 📄 Git Flow

Ведется работа по методологии Git Flow:
* `main` — релизная ветка.
* `develop` — основная ветка разработки.
* `feature/*` — ветки для реализации функционала (UI, Database, Logic).

---
*Автор: Я*
