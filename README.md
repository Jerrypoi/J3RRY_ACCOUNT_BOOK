# J3RRY ACCOUNT BOOK
## 杰瑞记账本

### 开发说明
- J3RRY_ACCOUNT_BOOK 文件夹为源代码文件夹。
- J3RRY_ACCOUNT_BOOK_TEST 为单元测试文件夹。
- 所有模块文件都应有 .c 源文件与 .h 头文件组成。头文件中放函数，变量定义，源文件中放实现。
- 在本解决方案 (Solution) 中共有三个项目 (Project): 
    - J3RRY_ACCOUNT_BOOK 用于存放项目源文件。
    - J3RRY_ACCOUNT_BOOK_TEST 用于存放测试文件。
    - sqlite 用于存放 SQlite 可执行文件。
- 要切换启动执行哪个项目：在解决方案资源管理器中右键点击项目名称 -> 设为启动项目
- 单元测试采用 Google 单元测试框架 gtest。但由于 gtest 是使用 C++ 编写完成的，所以在项目部分源代码中要有 C -> C++ 的支持。具体参见 [model.h](J3RRY_ACCOUNT_BOOK/model.h) 中的首部和尾部代码：
    ```cpp
    #ifdef __cplusplus
    extern "C" {
    #endif
    // 这里是 C 代码
    #ifdef __cplusplus
    }
    #endif
    ```
- 使用 Visual Studio 进行开发的时候，在单元测试前，需要将要被测试的模块连接到单元测试项目中。具体操作为：右键点击 J3RRY_ACCOUNT_BOOK_TEST -> 属性 -> 连接器 -> 输入 -> 附加依赖项 -> 编辑 然后将要测试的文件名放进去，此处的文件名不含后缀。
- 记账本数据后端使用 SQLite 作为数据支持，需要使用定义在 [db_connect.h](./J3RRY_ACCOUNT_BOOK/db_connect.h) 中的 sqlite* db 变量进行访问。同时项目基础代码部分也实现了一些数据库的交互操作。如果不习惯使用数据库也可以使用 getAllUser 等函数将数据库数据存入链表进行访问。
- 要使用 SQL 命令直接访问数据库，可以执行 sqlite 项目，这会启动一个 SQLite 控制台，输入 “.open 数据库文件路径” 即可打开数据库，并执行 SQL 命令。