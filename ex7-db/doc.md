## Section 1 - Planning a web API application using C++:

I need help planning a web API application using C++20, and want your advice and suggestions. The app will consist of 3 parts: a data library for a SQLite database (`inventory.db`), a web API, and integration testing. I need the following information before moving on to the initial design:
- Provide a detailed explanation of how to set up the application, including any dependencies (e.g., Boost, SQLite3, or REST frameworks like Crow or Pistache) and configuration files needed.
- Describe and visually render the folder structure of the application and the purpose of each module.
- Include instructions for running the application locally (e.g., using `CMake` for building and running) and deploying it to a server.
- Provide examples of how to use the web API, including sample requests and responses (e.g., using `curl` or Postman).
- Include any additional information that would be helpful for someone looking to understand and work with the application.
- Provide a detailed explanation of how to set up the application, including any dependencies and configuration files needed.


## Section 2 - High-level design and implementation details:

1. **Data Library**: Define a data management layer for a SQLite inventory database with an ORM-like abstraction. Use  `sqlite_modern_cpp` to handle database interactions. The database `SQLite/inventory.db` consists of three tables: `suppliers`, `categories`, and `products`, and a single view: `product_list`.
Requirements:
    - Implement a class `Database` that manages the connection to the SQLite database.
   - Support basic CRUD operations (Create, Read, Update, Delete) on inventory items.
   - Implement a caching mechanism to improve performance for frequently accessed data.

2. **Web API**: Define a web API using a lightweight C++ REST framework such as Crow, Pistache, or Restinio. The API should:
   - Provide REST endpoints over HTTP for GET and POST requests.
   - Implement input validation for incoming requests.
   - Handle errors gracefully, returning meaningful error messages and appropriate HTTP status codes.
   - Log requests and responses using a logging library like `spdlog`.
   - Include a health check endpoint that returns a `200 OK` status code and a message indicating that the service is running.

3. **Integration Testing**: Define a testing framework for integration testing using a C++ testing library like `Catch2` or `Doctest`. The tests should:
   - Use an in-memory SQLite database for mocking (`:memory:`).
   - Cover all API endpoints to ensure input validation and error handling work as expected.
   - Test rate limiting and Cross-Origin Resource Sharing (CORS) handling.
   - Validate the caching mechanism for the data library.

## Section 3 - Additional Considerations:

- Use `CMake` as the build system to manage dependencies and build configurations.
- Ensure the project is cross-platform (Windows, Linux, macOS) by avoiding platform-specific code where possible.
- Include a `README.md` file with setup instructions, examples, and troubleshooting tips.
- Follow modern C++ best practices, including the use of smart pointers, RAII, and the rule of five/zero.
- Ensure the code is well-documented with Doxygen comments for all public classes and functions.



