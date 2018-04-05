/**
 * @file   rb_tree.h
 * @brief  This file contains the definition of the RbTree container.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2018-03-21
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#ifndef RB_TREE_H
#define RB_TREE_H

#include <cstdint>
#include <cstring>

#include "junk/memory/typed_mem_pool.h"
#include "junk/util/junk_assert.h"
#include "junk/util/util.h"

namespace junk {

/**
 * @brief A binary tree container implemented as a Red-Black Tree.
 *
 *
 *
 * @tparam NumNodes
 *         Maximum number of nodes that may be stored in the tree.
 * @tparam T
 *         The type stored in each node. This must be Comparable.
 */
template <size_t NumNodes, typename T>
class RbTree
{
public:
    /// Default constructor.
    RbTree() = default;
    /// Default destructor.
    /// @todo Destruct all remaining nodes before destructing container.
    ~RbTree() = default;

    /**
     * @brief Insert an array of items.
     *
     * Items will be inserted one at a time. If the array is too large to fit in the allocated or
     * remaining space, as many items will be inserted as will fit.
     *
     * @note Success is still returned if not all items will fit in the tree.
     *
     * @param[in]  items
     *             The array of items to add to the tree.
     * @tparam N
     *         The number of items in the array.
     * @return A boolean:
     *         - `true`:  As many items as will fit were successfully added.
     *         - `false`: A failure occurred while attempting to insert an item.
     */
    template <size_t N>
    bool insert(const T (&items)[N])
    {
        bool success = true;

        for (size_t i = 0; i < util::min(N, NumNodes); i++) {
            success = insert(items[i]);
            if (!success) {
                break;
            }
        }

        return success;
    }

    /**
     * @brief Inserts a single item via copying.
     *
     * A single item may be inserted into the tree using this function.
     *
     * @note Item is copied into the tree.
     *
     * @param[in]  item
     *             The item to insert.
     * @return A boolean:
     *         - `true`:  The item was successfully inserted into the tree.
     *         - `false`: Inserting the item failed.
     */
    bool insert(const T& item)
    {
        bool success = false;

        // Trivial case of empty tree
        if (m_root == nullptr) {
            m_root = m_mem_pool.emplace(item);
            success = repairTree(m_root);
            return (m_root != nullptr);
        }

        // Traverse the tree to find where to insert the new item
        Node* current = m_root;
        while(current != nullptr) {
            // If the new item is less than the current node, go left
            if (item < current->item) {
                // If we've reached a leaf, insert the item
                if (current->left == nullptr) {
                    current->left = m_mem_pool.emplace(item);
                    current->left->parent = current;
                    current = current->left;
                    success = repairTree(current);
                    break;
                } else {
                    current = current->left;
                }
            // If the new item is greater than or equal to the current node, go right
            } else {
                // If we've reached a leaf, insert the item
                if (current->right == nullptr) {
                    current->right = m_mem_pool.emplace(item);
                    current->right->parent = current;
                    current = current->right;
                    success = repairTree(current);
                    break;
                } else {
                    current = current->right;
                }
            }
        }

        return success;
    }

    /**
     * @brief Insert an item via moving.
     *
     * A single item may be inserted into the tree using this function.
     *
     * @note Item is moved into the tree, the existing item may be invalid after the move.
     *
     * @param[in]  item
     *             The item to move into the tree.
     * @return A boolean:
     *         - `true`:  The item was successfully inserted into the tree.
     *         - `false`: A failure occurred while inserting the item.
     */
    bool insert(T&& item)
    {
        bool success = false;

        // Trivial case of empty tree
        if (m_root == nullptr) {
            m_root = m_mem_pool.emplace(std::move(item));
            success = repairTree(m_root);
            return success;
        }

        // Traverse the tree to find where to insert the new item
        Node* current = m_root;
        while(current != nullptr) {
            // If the new item is less than the current item, go left
            if (item < current->item) {
                // If we've reached a leaf, insert the item
                if (current->left == nullptr) {
                    current->left = m_mem_pool.emplace(std::move(item));
                    current->left->parent = current;
                    current = current->left;
                    success = repairTree(current);
                    break;
                } else {
                    current = current->left;
                }
            // If the new item is greater than or equal to the current item, go right
            } else {
                // If we've reached a leaf, insert the item
                if (current->right == nullptr) {
                    current->right = m_mem_pool.emplace(std::move(item));
                    current->right->parent = current;
                    current = current->right;
                    success = repairTree(current);
                    break;
                } else {
                    current = current->right;
                }
            }
        }

        return success;
    }

    /**
     * @brief Search for the given key in the tree.
     *
     * Searches the tree for the matching key. Key must be Comparable to the items stored in the
     * tree. If no match is found `nullptr` is returned.
     *
     * @note If there are multiple matches in the tree the first found is returned. This depends on
     *       the order in which items are added to the tree.
     *
     * @tparam K
     *         Key type. May be the same as the item type stored by the tree or may be any other
     *         type that is Comparable to the item type.
     * @param[in]  key
     *             The key to search for within the tree.
     *
     * @return A pointer to the item found, or if no match is found `nullptr`.
     */
    template <typename K>
    T* search(const K& key)
    {
        // Trivial case of empty tree
        if (m_root == nullptr) {
            return nullptr;
        }

        // Traverse the tree trying to find a match with key
        T* presult = nullptr;
        Node* current = m_root;
        while(current != nullptr) {
            // If the key is equal to the current item, return a pointer to that item
            if (key == current->item) {
                presult = &(current->item);
                break;
            // If the key is less than the current item, go left
            } else if (key < current->item) {
                if (current->left == nullptr) {
                    // We're at a leaf, no match was found
                    break;
                } else {
                    current = current->left;
                }
            // If the key is greater than the current item, go right
            } else {
                if (current->right == nullptr) {
                    // We're at a leaf, no match was found
                    break;
                } else {
                    current = current->right;
                }
            }
        }

        return presult;
    }

    /**
     * @brief Const overload of search().
     * @overload
     *
     * @param[in]  key
     *             The key to search for in the tree.
     * @return A pointer to the item found, or if no match is found `nullptr`.
     */
    template <typename K>
    const T* search(const K& key) const
    {
        // Trivial case of empty tree
        if (m_root == nullptr) {
            return nullptr;
        }

        // Traverse the tree trying to find a match with key
        T* presult = nullptr;
        Node* current = m_root;
        while(current != nullptr) {
            // If the key is equal to the current item, return a pointer to that item
            if (key == current->item) {
                presult = &(current->item);
                break;
            // If the key is less than the current item, go left
            } else if (key < current->item) {
                if (current->left == nullptr) {
                    // We're at a leaf, no match was found
                    break;
                } else {
                    current = current->left;
                }
            // If the key is greater than the current item, go right
            } else {
                if (current->right == nullptr) {
                    // We're at a leaf, no match was found
                    break;
                } else {
                    current = current->right;
                }
            }
        }

        return presult;
    }

private:
    /**
     * @brief The node object which makes up the tree.
     *
     * Stores left, right, and parent pointers as well as the color and the actual item. Provides
     * both copy and move constructors for the item.
     */
    struct Node
    {
        /**
         * @brief The red/black color each node may be painted.
         */
        enum class Color
        {
            kRed,  ///< This node is painted red.
            kBlack ///< This node is painted black.
        };

        /**
         * @brief Constructor which copies the item into the node.
         *
         * @param[in]  i
         *             The item to store.
         */
        explicit Node(const T& i) : item(i) {};

        /**
         * @brief Constructor which moves the item into the node.
         *
         * @param[in]  i
         *             The item to store.
         */
        explicit Node(T&& i) : item(std::move(i)) {};

        /// The item stored by this node.
        T item;
        /// The parent node in the tree.
        Node* parent = nullptr;
        /// The left child node in the tree.
        Node* left = nullptr;
        /// The right child node in the tree.
        Node* right = nullptr;
        /// The color that this node is painted.
        Color color = Color::kRed;
    };

    /**
     * @brief Get the parent of the given node.
     *
     * @param[in]  node
     *             The node to find the parent of.
     * @return A pointer to the parent of the given node. Or `nullptr` if `node` is `nullptr`.
     */
    static Node* parent(Node* node)
    {
        if (node == nullptr) {
            return nullptr;
        } else {
            return node->parent;
        }
    }

    /**
     * @brief Get the grandparent of the given node.
     *
     * @param[in]  node
     *             The node to find the grandparent of.
     * @return A pointer to the grandparent of the given node. If `node` is `nullptr` or if node
     *         doesn't have a grandparent, returns `nullptr`.
     */
    static Node* grandparent(Node* node)
    {
        return parent(parent(node));
    }

    /**
     * @brief Get the uncle of the given node.
     *
     * The uncle is the other child of the node's grandparent.
     *
     * @param[in]  node
     *             The node to find the uncle of.
     * @return A pointer to the uncle of the given node. If `node` is `nullptr`, the node doesn't
     *         have a grandparent, or the grandparent doesn't have a second child, the function
     *         returns `nullptr`.
     */
    static Node* uncle(Node* node)
    {
        Node* p_grandparent = grandparent(node);
        Node* p_uncle = nullptr;

        // Trivial case of no grandparent
        if (p_grandparent == nullptr) {
            return nullptr;
        }

        // If the left of the grandparent is our parent, then right is our uncle
        if (p_grandparent->left == parent(node)) {
            p_uncle = p_grandparent->right;
        } else {
            p_uncle = p_grandparent->left;
        }

        return p_uncle;
    }

    /**
     * @brief Rotate the given tree to the right.
     *
     * Rotates the tree rooted at `node` to the right. Also, updates the parents of the nodes.
     *
     * @see https://en.wikipedia.org/wiki/Tree_rotation
     *
     * @param[in]  node
     *             A pointer to the root of the tree to rotate.
     */
    static void rotateRight(Node* node)
    {
        // Handle nullptr
        if (node == nullptr) {
            return;
        }

        // Trivial case where left is empty
        if (node->left == nullptr) {
            return;
        }

        Node* p_parent = parent(node);
        Node* left = node->left;

        // The node's new left child becomes the previous left's right child
        node->left = left->right;
        // Update the parent of the node's new left child only if it exists
        if (node->left != nullptr) {
            node->left->parent = node;
        }
        // The node's previous left becomes its new parent
        left->right = node;
        node->parent = left;
        // If parent is nullptr, then the node was root. Either way update left's parent.
        left->parent = p_parent;

        // Update the original node's parent to point to the new "root"
        if (p_parent != nullptr) {
            if (p_parent->left == node) {
                p_parent->left = left;
            } else {
                p_parent->right = left;
            }
        }
    }

    /**
     * @brief Rotate the given tree to the left.
     *
     * Rotates the tree rooted at `node` to the left. Also, updates the parents of the nodes.
     *
     * @see https://en.wikipedia.org/wiki/Tree_rotation
     *
     * @param[in]  node
     *             A pointer to the root of the tree to rotate.
     */
    static void rotateLeft(Node* node)
    {
        // Handle nullptr
        if (node == nullptr) {
            return;
        }

        // Trivial case where right is empty
        if (node->right == nullptr) {
            return;
        }

        Node* p_parent = parent(node);
        Node* right = node->right;

        // The node's new right child becomes the previous right's left child
        node->right = right->left;
        // Update the parent of the node's new right child only if it exists
        if (node->right != nullptr) {
            node->right->parent = node;
        }
        // The node's previous right becomes its new parent
        right->left = node;
        node->parent = right;
        // If parent is nullptr, then the node was root. Either way update right's parent.
        right->parent = p_parent;

        // Update the original node's parent to point to the new "root"
        if (p_parent != nullptr) {
            if (p_parent->right == node) {
                p_parent->right = right;
            } else {
                p_parent->left = right;
            }
        }
    }

    /**
     * @brief Repair the tree according to red-black tree rules.
     *
     * This function must be called each time a node is inserted or deleted. It re-paints and
     * rotates the tree to ensure it adheres to red-black tree rules.
     *
     * @see https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
     *
     * @param[in]  node
     *             A pointer to the node to start the repair at.
     * @return A boolean:
     *         - `true`:  Repair succeeded. The tree adheres to red-black tree rules.
     *         - `false`: The starting node was invalid.
     */
    bool repairTree(Node* node)
    {
        // Handle a nullptr
        if (node == nullptr) {
            return false;
        }

        Node* current = node;
        while (current != nullptr) {
            if (parent(current) == nullptr) {
                // Case of root node
                current->color = Node::Color::kBlack;
                break;

            } else if (parent(current)->color == Node::Color::kBlack) {
                // Case of parent being black
                break;
            } else if ((uncle(current) != nullptr) && (uncle(current)->color == Node::Color::kRed)) {
                // Case of parent and uncle being red (uncle == nullptr means it's black)
                parent(current)->color = Node::Color::kBlack;
                uncle(current)->color = Node::Color::kBlack;
                grandparent(current)->color = Node::Color::kRed;
                current = grandparent(current);
            } else {
                // Otherwise, parent is red and uncle is black
                if ((grandparent(current)->left != nullptr) && (grandparent(current)->left->right == current)) {
                    rotateLeft(parent(current));
                    current = current->left;
                } else if ((grandparent(current)->right != nullptr) && (grandparent(current)->right->left == current)) {
                    rotateRight(parent(current));
                    current = current->right;
                } else {
                    // Do nothing
                }

                Node* old_parent = parent(current);
                Node* old_grandparent = grandparent(current);
                if (current == parent(current)->left) {
                    rotateRight(grandparent(current));
                } else {
                    rotateLeft(grandparent(current));
                }

                old_parent->color = Node::Color::kBlack;
                old_grandparent->color = Node::Color::kRed;
                break;
            }
        }

        // Update root node
        while(parent(current) != nullptr) {
            current = parent(current);
        }
        m_root = current;

        return true;
    }

    /// A pointer to the root node of the tree.
    Node* m_root = nullptr;
    /// The memory pool used to store all the nodes in the tree.
    TypedMemPool<Node, NumNodes> m_mem_pool;
};

} // namespace junk

#endif // RB_TREE_H
