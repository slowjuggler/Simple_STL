#ifndef NODE_H_
#define NODE_H_

namespace ns {

template <typename T>
struct ListNode {
  using value_type = T;
  using pointer = value_type*;
  using node_type = ListNode<value_type>;
  using node_pointer = node_type*;

  ListNode(value_type val) : value(val){};

  node_pointer next;
  node_pointer prev;
  value_type value;

  inline node_pointer forward() { return next; };
  inline node_pointer back() { return prev; };
};

using color_type = enum RBTnode_colors { RED, BLACK };

template <typename T>
struct RBTnode {
  using value_type = T;
  using pointer = value_type*;
  using node_type = RBTnode<value_type>;
  using node_pointer = node_type*;

  RBTnode(const value_type& val, const color_type& col = RED)
      : parent(nullptr),
        left(nullptr),
        right(nullptr),
        value(val),
        color(col){};
  RBTnode(const RBTnode& other) {
    parent = other.parent;
    left = other.left;
    right = other.right;
    value = other.value;
    color = other.color;
  };
  RBTnode(RBTnode&& other, const value_type& val, const color_type& col = RED)
      : parent(nullptr), left(nullptr), right(nullptr), value(val), color(col) {
    swap(other);
  };
  ~RBTnode(){};

  RBTnode& operator=(const RBTnode& other) {
    if (this == &other) return *this;
    parent = other.parent;
    left = other.left;
    right = other.right;
    value = other.value;
    color = other.color;
    return (*this);
  };

  RBTnode& operator=(RBTnode&& other) {
    if (this == &other) return *this;
    swap(other);
    return (*this);
  };

  node_pointer min() {
    if (left == nullptr) return this;
    node_pointer node = this;
    while (node->left != nullptr) node = node->left;
    return (node);
  };

  node_pointer max() {
    if (right == nullptr) return this;
    node_pointer node = this;
    while (node->right != nullptr) node = node->right;
    return (node);
  };

  node_pointer grandparent() {
    node_pointer node = this;
    return ((node != nullptr && node->parent != nullptr) ? node->parent->parent
                                                         : nullptr);
  };

  node_pointer uncle() {
    node_pointer node = grandparent();
    if (node == nullptr) return nullptr;
    return parent == node->left ? node->right : node->left;
  };

  node_pointer brother() {
    return (this == parent->left ? parent->right : parent->left);
  };

  inline node_pointer forward() {
    node_pointer curr = this;
    if (curr == nullptr) return nullptr;
    if (curr->right != nullptr) return curr->right->min();
    if (curr->is_left_child()) return curr->parent;
    while (curr->is_right_child() && curr != nullptr) {
      curr = curr->parent;
    }
    return ((curr->parent != nullptr) ? curr->parent : nullptr);
  }

  inline node_pointer back() {
    node_pointer curr = this;
    if (curr == nullptr) return nullptr;
    if (curr->left != nullptr) return curr->left->max();
    if (curr->is_right_child()) return curr->parent;
    while (curr->is_left_child() && curr != nullptr) {
      curr = curr->parent;
    }
    return ((curr != nullptr) ? curr->parent : nullptr);
  };

  inline bool is_node() const { return (parent != nullptr); };
  inline bool is_right_child() const {
    return (parent != nullptr && this == parent->right);
  };
  inline bool is_left_child() const {
    return (parent != nullptr && this == parent->left);
  };
  inline bool has_only_one_child() const {
    return ((left == nullptr && right != nullptr) ||
            (right == nullptr && left != nullptr));
  };
  bool operator==(const RBTnode& other) { return value == other.value; };
  bool operator!=(const RBTnode& other) { return value != other.value; };
  value_type& operator*() { return value; };

  void swap(RBTnode& other) {
    std::swap(parent, other.parent);
    std::swap(left, other.left);
    std::swap(right, other.right);
    std::swap(value, other.value);
    std::swap(color, other.color);
  };

  node_pointer parent;
  node_pointer left;
  node_pointer right;
  value_type value;
  color_type color;
};

template <typename T, typename Compare, typename Allocator>
class RBTree {
 public:
  using value_type = T;
  using pointer = value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using node_type = RBTnode<value_type>;
  using node_pointer = node_type*;
  using size_type = std::size_t;
  using compare_type = Compare;
  using iter = ns::BDIter<T, node_type>;
  using const_iter = ns::BDIter<const T, node_type>;
  using allocator_type = typename Allocator::template rebind<node_type>::other;

  RBTree(const allocator_type& alloc = allocator_type(),
         const compare_type& comp = compare_type())
      : alloc_(alloc), comp_(comp), root_(), size_(){};

  RBTree(const RBTree& other)
      : alloc_(other.alloc_), comp_(other.comp_), root_(), size_(0) {
    if (!other.size()) return;
    root_ = CopyTree(other.root_, nullptr);
    size_ = other.size_;
  };

  RBTree(RBTree&& other, const allocator_type& alloc = allocator_type(),
         const compare_type& comp = compare_type())
      : alloc_(alloc), comp_(comp), root_(), size_() {
    swap(other);
  };

  ~RBTree() { clear(); };

  RBTree& operator=(const RBTree& other) {
    if (this == &other) return *this;
    clear();
    if (!other.size()) return *this;
    RBTree tmp(other);
    swap(tmp);
    return (*this);
  }

  RBTree& operator=(RBTree&& other) {
    if (this != &other) {
      clear();
      swap(other);
    }
    return (*this);
  }

  void clear() {
    if (!size()) return;
    ClearTree(root_);
    size_ = 0;
    root_ = nullptr;
  }

  std::pair<iter, bool> build_root(const_reference val) {
    return std::make_pair(iter(root_ = NewNode(val, BLACK)), true);
  }

  iter start() const { return (root_ ? iter(root_->min()) : nullptr); }

  iter edge() const { return (root_ ? iter(root_->max()) : nullptr); }

  const_iter cstart() const {
    return (root_ ? const_iter(root_->min()) : nullptr);
  }
  const_iter cedge() const {
    return (root_ ? const_iter(root_->max()) : nullptr);
  }

  size_type const& size() const { return size_; }

  size_type max_size(void) const { return alloc_.max_size(); }

  std::pair<iter, bool> find(const_reference val) {
    node_pointer curr = root_;
    while (curr != nullptr) {
      if (comp_(val, curr->value))
        curr = curr->left;
      else if (comp_(curr->value, val))
        curr = curr->right;
      else
        return std::make_pair(iter(curr), true);
    }
    return (std::make_pair(iter(curr), false));
  }

  std::pair<iter, bool> insert(const_reference val) {
    if (!size()) return build_root(val);
    node_pointer curr = root_;
    while (curr != nullptr) {
      if (!comp_(val, curr->value) && !comp_(curr->value, val)) {
        return std::make_pair(iter(curr), false);
      } else if (comp_(val, curr->value)) {
        if (curr->left == nullptr) return insert_left(curr, val);
        curr = curr->left;
      } else {
        if (curr->right == nullptr) return insert_right(curr, val);
        curr = curr->right;
      }
    }
    return (std::make_pair(iter(curr), false));
  }

  std::pair<iter, bool> insert_all(const_reference val) {
    if (!size()) return build_root(val);
    node_pointer curr = root_;
    while (curr != nullptr) {
      if (comp_(val, curr->value)) {
        if (curr->left == nullptr) return insert_left(curr, val);
        curr = curr->left;
      } else {
        if (curr->right == nullptr) return insert_right(curr, val);
        curr = curr->right;
      }
    }
    return (std::make_pair(iter(curr), false));
  }

  std::pair<iter, bool> insert_or_assign(const_reference val) {
    if (!size()) return build_root(val);
    node_pointer curr = root_;
    while (curr != nullptr) {
      if (!comp_(val, curr->value) && !comp_(curr->value, val)) {
        curr->value = val;
        return std::make_pair(iter(curr), false);

      } else if (comp_(val, curr->value)) {
        if (curr->left == nullptr) return insert_left(curr, val);
        curr = curr->left;

      } else {
        if (curr->right == nullptr) return insert_right(curr, val);
        curr = curr->right;
      }
    }
    return (std::make_pair(iter(curr), false));
  }

  std::pair<iter, bool> insert_left(node_pointer ptr, const_reference val) {
    ptr->left = NewNode(val);
    ptr->left->parent = ptr;
    insert_case1(ptr->left);
    return (std::make_pair(iter(ptr->left), true));
  }

  std::pair<iter, bool> insert_right(node_pointer ptr, const_reference val) {
    ptr->right = NewNode(val);
    ptr->right->parent = ptr;
    insert_case1(ptr->right);
    return (std::make_pair(iter(ptr->right), true));
  }

  void insert_case1(node_pointer ptr) {
    if (ptr->parent == nullptr)
      ptr->color = BLACK;
    else
      insert_case2(ptr);
  }

  void insert_case2(node_pointer ptr) {
    if (ptr->parent->color == BLACK) return;
    insert_case3(ptr);
  }

  void insert_case3(node_pointer ptr) {
    node_pointer u = ptr->uncle();
    node_pointer g = ptr->grandparent();
    if (u != nullptr && u->color == RED) {
      ptr->parent->color = BLACK;
      u->color = BLACK;
      g->color = RED;
      insert_case1(g);
    } else {
      insert_case4(ptr);
    }
  }

  void insert_case4(node_pointer ptr) {
    node_pointer g = ptr->grandparent();
    if (ptr == ptr->parent->right && ptr->parent == g->left) {
      rotate_left(ptr->parent);
      ptr = ptr->left;
    } else if (ptr == ptr->left && ptr->parent == g->right) {
      rotate_right(ptr->parent);
      ptr = ptr->right;
    }
    insert_case5(ptr);
  }

  void insert_case5(node_pointer ptr) {
    node_pointer g = ptr->grandparent();
    ptr->parent->color = BLACK;
    g->color = RED;
    if (ptr == ptr->parent->left && ptr->parent == g->left)
      rotate_right(g);
    else
      rotate_left(g);
  }

  void rotate_left(node_pointer ptr) {
    node_pointer pivot = ptr->right;
    pivot->parent = ptr->parent;
    if (ptr->parent != nullptr) {
      if (ptr->parent->left == ptr)
        ptr->parent->left = pivot;
      else
        ptr->parent->right = pivot;
    }
    ptr->right = pivot->left;
    if (pivot->left != nullptr) pivot->left->parent = ptr;
    ptr->parent = pivot;
    pivot->left = ptr;
    if (root_->parent != nullptr) root_ = root_->parent;
  }

  void rotate_right(node_pointer ptr) {
    node_pointer pivot = ptr->left;
    pivot->parent = ptr->parent;
    if (ptr->parent != nullptr) {
      if (ptr->parent->left == ptr)
        ptr->parent->left = pivot;
      else
        ptr->parent->right = pivot;
    }
    ptr->left = pivot->right;
    if (pivot->right != nullptr) pivot->right->parent = ptr;
    ptr->parent = pivot;
    pivot->right = ptr;
    if (root_->parent != nullptr) root_ = root_->parent;
  }

  void erase(iter pos) {
    if (size_ == 1) {
      clear();
      return;
    }
    replace(pos.operator->());
  }

  void replace(node_pointer ptr) {
    if (ptr == nullptr) return;
    node_pointer to_delete = ptr;
    if (ptr->right != nullptr && ptr->left != nullptr) {
      std::swap(ptr->value, ptr->right->min()->value);
      to_delete = ptr->right->min();
    }
    if (to_delete->has_only_one_child()) {
      delete_one_child(to_delete);
    } else {
      if (to_delete->color == BLACK) {
        if (to_delete->parent->color == RED) {
          to_delete->parent->color = BLACK;
        } else {
          delete_case1(to_delete);
        }
      }
      if (to_delete->is_left_child())
        to_delete->parent->left = nullptr;
      else
        to_delete->parent->right = nullptr;
    }
    DelNode(to_delete);
  }

  void replace_node(node_pointer ptr, node_pointer child) {
    if (ptr->parent != nullptr) {
      child->parent = ptr->parent;
      if (ptr->is_left_child())
        ptr->parent->left = child;
      else
        ptr->parent->right = child;
    } else {
      child->parent = nullptr;
      root_ = child;
    }
  }

  void delete_one_child(node_pointer ptr) {
    if (!ptr->right && !ptr->left) {
      replace_node(ptr, nullptr);
      if (ptr->color == BLACK) delete_case1(ptr->parent);
    } else {
      node_pointer child = ptr->right ? ptr->right : ptr->left;
      replace_node(ptr, child);
      if (ptr->color == BLACK) {
        if (child->color == RED)
          child->color = BLACK;
        else
          delete_case1(child);
      }
    }
  }

  void delete_case1(node_pointer ptr) {
    if (ptr->parent) delete_case2(ptr);
  }

  void delete_case2(node_pointer ptr) {
    node_pointer b = ptr->brother();
    if (b->color == RED) {
      ptr->parent->color = RED;
      b->color = BLACK;
      if (ptr->is_left_child()) {
        rotate_left(ptr->parent);
      } else {
        rotate_right(ptr->parent);
      }
    }
    delete_case3(ptr);
  }

  void delete_case3(node_pointer ptr) {
    node_pointer b = ptr->brother();
    if (!b->has_only_one_child() &&
        (ptr->parent->color == BLACK && b->color == BLACK) &&
        ((b->left == nullptr && b->right == nullptr) ||
         (b->left->color == BLACK && b->right->color == BLACK))) {
      b->color = RED;
      delete_case1(ptr->parent);
    } else {
      delete_case4(ptr);
    }
  }

  void delete_case4(node_pointer ptr) {
    node_pointer b = ptr->brother();
    if (!b->has_only_one_child() && ptr->parent->color == RED &&
        b->color == BLACK &&
        ((b->left == nullptr && b->right == nullptr) ||
         (b->left->color == BLACK && b->right->color == BLACK))) {
      b->color = RED;
      ptr->parent->color = BLACK;
    } else {
      delete_case5(ptr);
    }
  }

  void delete_case5(node_pointer ptr) {
    node_pointer b = ptr->brother();
    if (!b->has_only_one_child() && b->color == BLACK) {
      if (ptr->is_left_child() && b->right->color == BLACK &&
          b->left->color == RED) {
        b->color = RED;
        b->left->color = BLACK;
        rotate_right(b);
      } else if (ptr->is_right_child() && b->left->color == BLACK &&
                 b->right->color == RED) {
        b->color = RED;
        b->right->color = BLACK;
        rotate_left(b);
      }
    }
    delete_case6(ptr);
  }

  void delete_case6(node_pointer ptr) {
    node_pointer b = ptr->brother();
    b->color = ptr->parent->color;
    ptr->parent->color = BLACK;
    if (ptr->is_left_child()) {
      b->right->color = BLACK;
      rotate_left(ptr->parent);
    } else {
      b->left->color = BLACK;
      rotate_right(ptr->parent);
    }
  }

  void swap(RBTree& other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
    std::swap(alloc_, other.alloc_);
  }

  void print() {
    iter first = iter(start());
    iter last = iter(edge());
    for (size_type i = 0; i < size_; ++i) {
      std::cout << "key: " << (*first).first << " value: " << (*first).second
                << " color: " << first.operator->()->color << std::endl;
      ++first;
    }
  }

  void print_mult() {
    iter first = iter(start());
    iter last = iter(edge());
    for (size_type i = 0; i < size_; ++i) {
      std::cout << "value: " << *first
                << " color: " << first.operator->()->color << std::endl;
      ++first;
    }
  }

  bool is_balanced() {
    int maxh, minh;
    return IsBalancedUtil(root_, maxh, minh);
  }

  iter lower_bound(const_reference val) {
    node_pointer curr = root_;
    node_pointer result = nullptr;
    while (curr != nullptr) {
      if (!comp_(curr->value, val)) {
        result = curr;
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return (result ? iter(result) : edge());
  }

  iter upper_bound(const_reference val) {
    node_pointer curr = root_;
    node_pointer result = nullptr;
    while (curr != nullptr) {
      if (comp_(val, curr->value)) {
        result = curr;
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return (result ? iter(result) : edge());
  }

  std::pair<iter, iter> equal_range(const_reference val) {
    iter lower = lower_bound(val);
    iter upper = upper_bound(val);
    return std::make_pair(lower, upper);
  }

 private:
  allocator_type alloc_;
  compare_type comp_;
  node_pointer root_;
  size_type size_;

  node_pointer NewNode(value_type const& val, color_type const& color = RED) {
    node_pointer ptr = alloc_.allocate(1);
    alloc_.construct(ptr, node_type(val, color));
    ++size_;
    return ptr;
  };

  void DelNode(node_pointer ptr) {
    alloc_.destroy(ptr);
    alloc_.deallocate(ptr, 1);
    --size_;
  };

  void ClearTree(node_pointer ptr) {
    if (ptr == nullptr) return;
    ClearTree(ptr->left);
    ClearTree(ptr->right);
    alloc_.destroy(ptr);
    alloc_.deallocate(ptr, 1);
  };

  bool IsBalancedUtil(node_pointer n, int& maxh, int& minh) {
    if (n == nullptr) {
      maxh = minh = 0;
      return true;
    }
    int lmxh, lmnh;
    int rmxh, rmnh;

    if (IsBalancedUtil(n->left, lmxh, lmnh) == false) return false;

    if (IsBalancedUtil(n->right, rmxh, rmnh) == false) return false;

    maxh = fmax(lmxh, rmxh) + 1;
    minh = fmin(lmnh, rmnh) + 1;

    if (maxh <= 2 * minh) return true;

    return false;
  };

  node_pointer CopyTree(node_pointer src_node, node_pointer parent) {
    if (src_node == nullptr) return nullptr;
    node_pointer new_node = NewNode(src_node->value, src_node->color);
    new_node->parent = parent;
    new_node->left = CopyTree(src_node->left, new_node);
    new_node->right = CopyTree(src_node->right, new_node);
    return new_node;
  };
};

}  // namespace ns

#endif  // NODE_H_
