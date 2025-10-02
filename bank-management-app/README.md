### YoBank – Educational Bank Management App

YoBank is a learning-oriented desktop application created to practice core Object-Oriented Programming (OOP) principles in the context of a simple banking system.

### Learning Focus
- **Encapsulation**: Domain data and behavior are grouped within models such as customer, account, and transaction.
- **Inheritance**: Banker roles (e.g., manager and officers) share common behavior while extending role-specific capabilities.
- **Polymorphism**: Controllers and role classes interact through shared interfaces/base types to enable flexible behavior.
- **Separation of concerns**: UI (views/controllers), domain models, and persistence are kept distinct to improve readability and maintainability.

### What It Demonstrates
- Basic authentication and role-based navigation
- Managing customers and accounts (create, view, update, delete)
- Recording and viewing transactions
- Simple configuration of account limits and interest settings

### Tech Stack
- Java 17
- JavaFX (FXML for views)
- SQLite (via sqlite-jdbc)
- Gradle (with OpenJFX plugin)

### How to Run
From the project root in a terminal:
```bash
./gradlew run
```
The app opens at the login screen. A local SQLite database file (`my_Database.db`) is used for storage. If empty, create seed data for an admin user before logging in.

### Notes
- This project prioritizes clarity of OOP concepts over production-grade concerns.
- External libraries are used only to support a minimal UI and local storage.

### Acknowledgements
Built as a study project using Java, JavaFX, and SQLite.