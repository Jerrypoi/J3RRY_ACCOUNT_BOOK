create table 'user'(
    id integer primary key AUTOINCREMENT not null ,
    name char(64) unique,
    password char(256),
    email_addr text
);

create table 'transaction_classes'(
    id integer primary key AUTOINCREMENT not null,
    class_name char(64)
);
create table 'transactions'(
    id integer primary key AUTOINCREMENT not null,
    type boolean not null,
    amount decimal(20,2) not null,
    class_id integer,
    user_id integer,
    transaction_date blob,
    FOREIGN KEY (class_id) references transaction_classes(id),
    foreign key (user_id) references user(id)
);