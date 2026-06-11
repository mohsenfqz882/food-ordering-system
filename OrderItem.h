#ifndef ORDERITEM_H
#define ORDERITEM_H

// یک قلم از سفارش - منطبق بر جدول order_items
class OrderItem {
public:
    int id;
    int orderId;
    int itemId;
    int count;

    OrderItem() : id(0), orderId(0), itemId(0), count(0) {}

    OrderItem(int id, int orderId, int itemId, int count)
        : id(id), orderId(orderId), itemId(itemId), count(count) {}
};

#endif