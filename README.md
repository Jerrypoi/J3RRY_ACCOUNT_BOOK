# J3RRY ACCOUNT BOOK
## 杰瑞记账本

### 开发说明
- J3RRY_ACCOUNT_BOOK 文件夹为源代码文件夹。
- J3RRY_ACCOUNT_BOOK_TEST 为单元测试文件夹。
- 所有模块文件都应有 .c 源文件与 .h 头文件组成。头文件中放函数，变量定义，源文件中放实现。
- 在本解决方案 (Solution) 中共有三个项目 (Project): 
    - J3RRY_ACCOUNT_BOOK 用于存放项目源文件。
    - J3RRY_ACCOUNT_BOOK_TEST 用于存放测试文件。
    - sqlite 用于存放 SQLite 可执行文件。
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

下一步要实现的功能（可以在[这里](./J3RRY_ACCOUNT_BOOK/暂未实现的功能.h) 看到）：

```cpp
/**
* @return 返回值为用户的 id，若登录失败返回 -1,
* @param user_name 用户名，要求用户名具有唯一性，在注册时检测用户名是否唯一
* @param password 用户密码
*/
int login(char* user_name, char* password);
/**
* @return 返回注册好的用户 id，这样在注册完用户不用再登录一次。若注册失败返回 -1
* @param username 用户输入的用户名，在数据库中用户名应当保持唯一性，这里在创建数据库的时候已经约束好了，所以只需要判断插入表是否成功即可（不成功说明用户名重复）
* @param password 用户输入的密码。
* @param password_confirm 用户第二次输入的密码，两次输入密码应当一致
* @param email_address 用户邮箱地址
*/
int sign_up(char* username, char* password, char* password_confirm, char* email_address);

/**
* @return 返回输入的交易类别的 id，如果不存在则返回 -1 
* @param transaction_class 交易类别
*/
int find_transaction_class(char* transaction_class);
/**
* @return 创建交易类别，若创建成功返回创建好的 id，若失败返回 -1
* @param transaction_class 交易类别
*/
int create_transaction_class(char* transaction_class);
/**
* @return 记录是否成功
* @param type 收入还是支出，0 收入，1 支出
* @param amount 交易金额
* @param transaction_class_id 交易类别 id，调用这个函数前要调用 find_transaction_class 获取交易的 id
* @param transaction_date 交易日期，如果为 NULL 则为系统时间的
*/
bool record_transaction(int type, double amount, int transaction_class_id, char* transaction_date);

/**
* 导出用户的交易记录，注意交易记录包括交易记录表与交易类别表。
* 同时导出的交易记录只能导出当前已经登录的用户的交易记录，不能导出别人的
* @return 成功返回 true，失败 false
* @param filename 用户输入的导出文件名
*/
bool export_data(char* filename);

/**
* 导入用户给的交易记录
* @return 成功返回 true，失败 false
*/
bool import_data(char* filename);

```