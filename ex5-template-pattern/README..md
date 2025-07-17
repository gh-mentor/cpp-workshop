# Template Method Pattern Exercise

In this exercise, you will implement and enhance an application that uses the Template Method Pattern. The goal is to understand the pattern, refactor the project to follow best practices, and adhere to SOLID design principles.

## Objectives

1. **Understand the Template Method Pattern**: Learn how the pattern works and its use cases.
2. **Refactor Project Structure**: Organize the project to follow best practices.
3. **Adhere to RAII Principles**: Refactor the code to ensure it adheres to RAII principles.
4. **Unit Testing**: Write unit tests to validate the functionality of the application.

## Instructions

1. **Refactor Project Structure**:
   - Organize the project into a well-structured hierarchy.
   - Separate interfaces into their own modules.

2. **Apply RAII Principles**:
   - **R**esponsibility: Ensure each class has a single responsibility.
   - **A**bstract: Use interfaces to define contracts for classes.
   - **A**ggregate: Group related classes and interfaces together.
   - **I**nterface: Use interfaces to decouple implementation from contracts.

3. **Write Unit Tests**:
   - Write unit tests for all public classes and functions.

4. **Documentation**:
   - Create documentation to explain the Template Method Pattern and how it is used in the application.

## Sample Prompts for Copilot Assistance

Here are some sample prompts you can use with Copilot to guide you through the refactoring and testing phases of this exercise:

### Refactoring Phase

1. **Scaffolding**:
   - Help me create a basic structure for a report generation application using the Template Method Pattern. The file main.cpp is contains the monolithic code that needs to be refactored.

2. **RAII**:
   - "Refactor the code to apply RAAI principles: Responsibility, Abstract, Aggregate, Interface."

### Testing Phase
1. **Unit Tests**:
   - "Write a test case to verify that the `CompanyReport` class generates a report correctly."
   - "Generate a test to check that the header and footer methods are called in the correct order."

### Documentation Phase
1. **Explain the Pattern**:
   - "Create a section in the README to explain the Template Method Pattern with examples."
   - "Add a diagram to illustrate the flow of the Template Method Pattern."
   - "Write a section to clarify the benefits of using the Template Method Pattern in software design."

By following these instructions and using the provided prompts, you can refactor the project to adhere to best practices and ensure it is well-documented and testable. Happy coding!