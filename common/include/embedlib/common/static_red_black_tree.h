
#ifndef STATIC_RED_BLACK_TREE_H
#define STATIC_RED_BLACK_TREE_H

#include <cstdint>

template <typename T, size_t Size>
class StaticRedBlackTree {
private:
    enum class NodeState {
        NIL,
        BLACK,
        RED
    };

    struct Node {
        NodeState state = NodeState::NIL;
        T item;
    };
};

#endif // STATIC_RED_BLACK_TREE_H
