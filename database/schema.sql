-- database/schema.sql

CREATE TABLE users (
                       id INTEGER PRIMARY KEY AUTOINCREMENT,
                       username TEXT,
                       password TEXT,
                       role TEXT          -- customer / manager / admin
);

CREATE TABLE restaurants (
                             id INTEGER PRIMARY KEY AUTOINCREMENT,
                             name TEXT,
                             address TEXT,
                             phone TEXT,
                             description TEXT,
                             prep_time INTEGER,     -- زمان آماده سازی (دقیقه)
                             is_active INTEGER      -- 0 یا 1
);

CREATE TABLE menu_items (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            restaurant_id INTEGER,
                            name TEXT,
                            description TEXT,
                            price REAL,
                            type TEXT,             -- food / drink
                            extra INTEGER,         -- زمان پخت برای غذا یا حجم برای نوشیدنی
                            is_available INTEGER   -- 0 یا 1
);

CREATE TABLE orders (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        user_id INTEGER,
                        restaurant_id INTEGER,
                        status TEXT,           -- preparing / ready_to_send / delivered
                        total_price REAL
);

CREATE TABLE order_items (
                             id INTEGER PRIMARY KEY AUTOINCREMENT,
                             order_id INTEGER,
                             item_id INTEGER,
                             count INTEGER
);